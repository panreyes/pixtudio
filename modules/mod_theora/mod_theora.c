/*  Theora module for PixTudio
 *
 *  Originally written by Joseba Garci­a Etxebarria <joseba.gar@gmail.com>
 *  based on the simplesdl.c example included with theoraplay
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include <SDL.h>
#include <theoraplay.h>
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

/* PixTudio stuff */
#include <bgddl.h>
#include <xstrings.h>
#include <libgrbase.h>
#include <g_video.h>

#ifndef __MONOLITHIC__
#include "mod_theora_symbols.h"
#endif

struct ctx {
    GRAPH *graph;
    const THEORAPLAY_VideoFrame *frame;
    const THEORAPLAY_AudioPacket *audio;
    THEORAPLAY_Decoder *decoder;
    Uint32 baseticks;
    Uint32 framems;
    ALuint audio_source;
};

ALCdevice *audio_device;
ALCcontext *audio_context;

struct ctx video;

char playing_video = 0;

static void queue_audio(const THEORAPLAY_AudioPacket *audio) {
    ALuint audio_buffer;
    ALuint error;
    ALint status;
    ALenum format;
    ALsizei size, freq;
    static int nbuffers = 0;

    if (audio_context != NULL) {
        // Generate an audio buffer (if needed) or reuse an already-processed one
        if (nbuffers <= 10) {
            alGenBuffers(1, &audio_buffer);
            nbuffers++;
        } else {
            alSourceUnqueueBuffers(video.audio_source, 1, &audio_buffer);
            if ((error = alGetError()) != AL_NO_ERROR) {
                alGenBuffers(1, &audio_buffer);
                nbuffers++;
            }
        }

        // If we could get a valid audio_buffer, process the audio data and queue it
        if ((error = alGetError()) == AL_NO_ERROR) {
            size = (ALsizei)(audio->frames * audio->channels * 4); // 4 == sizeof(float32)
            if (audio->channels == 1) {
                format = alGetEnumValue("AL_FORMAT_MONO_FLOAT32");
                freq = (ALsizei)audio->freq;
            } else if (audio->channels == 2) {
                format = alGetEnumValue("AL_FORMAT_STEREO_FLOAT32");
                freq   = (ALsizei)audio->freq;
            } else {
                // HACK, HACK, HACK!!
                format = alGetEnumValue("AL_FORMAT_MONO_FLOAT32");
                freq = (ALsizei)audio->freq * audio->channels;
                fprintf(stderr, "Cannot play audio with %d channels, expect weirdness\n",
                        audio->channels);
            }
            alBufferData(audio_buffer, format, audio->samples, size, freq);
            if ((error = alGetError()) != AL_NO_ERROR) {
                fprintf(stderr, "Audio buffer data copying failed: %s\n", alGetString(error));
            } else {
                // Queue the audio buffer for playback
                alSourceQueueBuffers(video.audio_source, 1, &audio_buffer);

                // If the source runs out of buffers to play, it stops
                // so we remove processed buffers from the queue and
                // restart playback
                alGetSourcei(video.audio_source, AL_SOURCE_STATE, &status);
                if (status == AL_STOPPED) {
                    // We could probably do this all at once
                    ALuint processed_buffer;
                    alSourceUnqueueBuffers(video.audio_source, 1, &processed_buffer);
                    while ((error = alGetError()) == AL_NO_ERROR) {
                        alDeleteBuffers(1, &processed_buffer);
                        alSourceUnqueueBuffers(video.audio_source, 1, &processed_buffer);
                    }

                    // Tell OpenAL to resume playback
                    alSourcePlay(video.audio_source);
                }
            }
        }
    }

    // Free the Vorbis audio packet
    THEORAPLAY_freeAudio(audio);
} // queue_audio

// Paint the current video frame onscreen, skipping those that we already missed
void refresh_video() {
    if (!playing_video) {
        return;
    }

    void *pixels;
    int pitch;

    const Uint32 now = SDL_GetTicks() - video.baseticks;

    if (!video.frame) {
        video.frame = THEORAPLAY_getVideo(video.decoder);
    }

    // Play video frames when it's time.
    if (video.frame && (video.frame->playms <= now)) {
        if (video.framems && ((now - video.frame->playms) >= video.framems)) {
            // Skip frames to catch up, but keep track of the last one
            // in case we catch up to a series of dupe frames, which
            // means we'd have to draw that final frame and then wait for
            // more.
            const THEORAPLAY_VideoFrame *last = video.frame;
            while ((video.frame = THEORAPLAY_getVideo(video.decoder)) != NULL) {
                THEORAPLAY_freeVideo(last);
                last = video.frame;
                if ((now - video.frame->playms) < video.framems)
                    break;
            } // while

            if (!video.frame) {
                video.frame = last;
            }
        } // if

        // do nothing; we're far behind and out of options.
        if (!video.frame) {
            static int warned = 0;
            if (!warned) {
                warned = 1;
                SDL_Log("WARNING: Video playback can't keep up, skipping frames!\n");
            } // if
        } else {
            if (SDL_LockTexture(video.graph->texture, NULL, &pixels, &pitch) < 0) {
                SDL_Log("Error updating texture: %s", SDL_GetError());
            } else {
                memcpy(pixels, video.frame->pixels, video.graph->height * pitch * 1.5);
                SDL_UnlockTexture(video.graph->texture);

                // Mark the video GRAPH as dirty so that BennuGD redraws it
                video.graph->modified = 1;
                video.graph->info_flags &= ~GI_CLEAN;
            }
        }
        THEORAPLAY_freeVideo(video.frame);
        video.frame = NULL;
    }

    // TODO: We're doing nothing to determine if we skipped some frames and need to catch up!
    if (audio_context != NULL) {
        while ((video.audio = THEORAPLAY_getAudio(video.decoder)) != NULL) {
            queue_audio(video.audio);
        }
    }

    return;
}

/* Checks wether the current video is being played */
int video_is_playing() {
    return playing_video;
}

int video_play(INSTANCE *my, int *params) {
    int bpp, graphid;
    const int MAX_FRAMES = 30;
    void *pixels;
    int pitch;

    bpp = screen->format->BitsPerPixel;

    if (playing_video == 1) {
        return -1;
    }

    if (!scr_initialized) {
        return (-1);
    }

    /* Start the decoding, we want to use a YUV format to reduce CPU usage */
    video.decoder =
        THEORAPLAY_startDecodeFile(string_get(params[0]), MAX_FRAMES, THEORAPLAY_VIDFMT_IYUV);
    string_discard(params[0]);

    if (!video.decoder) {
        SDL_Log("Failed to start decoding '%s'!\n", string_get(params[0]));
        string_discard(params[0]);
        return -1;
    }

    // Wait until the decoder has parsed out some basic truths from the
    //  file. In a video game, you could choose not to block on this, and
    //  instead do something else until the file is ready.
    while (!THEORAPLAY_isInitialized(video.decoder)) {
        SDL_Delay(10);
    }

    if (!THEORAPLAY_hasVideoStream(video.decoder)) {
        THEORAPLAY_stopDecode(video.decoder);
        return -1;
    }

    if (!THEORAPLAY_hasAudioStream(video.decoder)) {
        THEORAPLAY_stopDecode(video.decoder);
        return -1;
    }

    while (!video.frame || !video.audio) {
        if (!video.frame)
            video.frame = THEORAPLAY_getVideo(video.decoder);
        if (!video.audio)
            video.audio = THEORAPLAY_getAudio(video.decoder);
        SDL_Delay(10);
    }

    video.framems = (video.frame->fps == 0.0) ? 0 : ((Uint32)(1000.0 / video.frame->fps));

    // Generate the audio source
    alGenSources((ALuint)1, &video.audio_source);
    if (alGetError() != AL_NO_ERROR) {
        fprintf(stderr, "Audio source creation failed\n");
        alcCloseDevice(audio_device);
        THEORAPLAY_stopDecode(video.decoder);
        return -1;
    }
    // Set the source properties (probably not strictly required)
    alSourcef(video.audio_source, AL_PITCH, 1);
    alSourcef(video.audio_source, AL_GAIN, 1);
    alSource3f(video.audio_source, AL_POSITION, 0., 0., 0.);
    alSource3f(video.audio_source, AL_VELOCITY, 0., 0., 0.);
    alSourcei(video.audio_source, AL_LOOPING, AL_FALSE);

    while (video.audio) {
        queue_audio(video.audio);
        video.audio = THEORAPLAY_getAudio(video.decoder);
    } // while

    video.baseticks = SDL_GetTicks();

    // Create the graph holding the video surface
    graphid     = bitmap_next_code();
    video.graph = bitmap_new_streaming(graphid, video.frame->width, video.frame->height, bpp);
    if (!video.graph) {
        THEORAPLAY_stopDecode(video.decoder);
        video.decoder = NULL;
        THEORAPLAY_stopDecode(video.decoder);
        return -1;
    }

    // Blank the GRAPH texture before showing it, otherwise junk will be shown
    if (SDL_LockTexture(video.graph->texture, NULL, &pixels, &pitch) < 0) {
        SDL_Log("Error updating texture: %s", SDL_GetError());
    } else {
        memcpy(pixels, video.frame->pixels, video.graph->height * pitch * 1.5);
        SDL_UnlockTexture(video.graph->texture);
    }

    grlib_add_map(0, video.graph);
    THEORAPLAY_freeVideo(video.frame);
    video.frame = NULL;

    alSourcePlay(video.audio_source);

    playing_video = 1;

    return video.graph->code;
}

/* Stop the currently being played video and release theoraplay stuff */
int video_stop(INSTANCE *my, int *params) {
    ALuint error;
    ALuint audio_buffer;

    if (!playing_video) {
        return 0;
    }
    // Stop the video playback lock
    playing_video = 0;

    // Immediately stop audio playback
    alSourceStop(video.audio_source);

    if (video.graph) {
        grlib_unload_map(0, video.graph->code);
        video.graph = NULL;
    }

    if (video.decoder) {
        THEORAPLAY_stopDecode(video.decoder);
        video.decoder = NULL;
    }

    // Unqueue & delete all the buffers associated with a source
    alSourceUnqueueBuffers(video.audio_source, 1, &audio_buffer);
    while ((error = alGetError()) == AL_NO_ERROR) {
        alDeleteBuffers(1, &audio_buffer);
        alSourceUnqueueBuffers(video.audio_source, 1, &audio_buffer);
    }

    // Once the source has no more queued buffers, it can be deleted
    alDeleteSources(1, &video.audio_source);
    if ((error = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "OpenAL error deleting source: %x, %s\n", error, alGetString(error));
    }

    return 0;
}

/* TODO: Pause the currently playing video */
int video_pause() {
    return 0;
}

/* Set the volume of the video.
   Input must be an integer 0-255.
   Returns 0 on success and -1 on error
*/
int video_set_volume(INSTANCE *my, int *params) {
    ALuint error;

    float new_volume = (float)params[0] / 255.0;
    alSourcef(video.audio_source, AL_GAIN, new_volume);
    if ((error = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "OpenAL error setting volume: %x, %s\n", error, alGetString(error));
        return -1;
    }

    return 0;
}

void __bgdexport(mod_theora, module_initialize)() {
    // Initialize OpenAL
    alGetError();                       // clear error stack
    audio_device = alcOpenDevice(NULL); // open default device
    if (audio_device == NULL) {
        fprintf(stderr, "Audio initialization failed!\n");
    }

    audio_context = alcCreateContext(audio_device, NULL); // create context
    if (audio_context == NULL) {
        fprintf(stderr, "Audio context creation failed\n");
        alcCloseDevice(audio_device);
    }
    alcMakeContextCurrent(audio_context); // set active context

    printf("OpenAL info:\n");
    printf("============\n");
    printf("\tVersion: %s\n", alGetString(AL_VERSION));
    printf("\tVendor: %s\n", alGetString(AL_VENDOR));
    printf("\tRenderer: %s\n", alGetString(AL_RENDERER));
    /*printf("\tAL Extensions: %s\n", alGetString(AL_EXTENSIONS));
    printf("\tALC Extensions: %s\n", alcGetString(audio_device, ALC_EXTENSIONS));*/

    // Since audio in the Theora videos is float32, load that extension
    // TODO: This'll fail, since we're doing nothing to prevent
    if (!alIsExtensionPresent("AL_EXT_FLOAT32")) {
        fprintf(stderr, "OpenAL Extension AL_EXT_FLOAT32 not present, refusing to initialise\n");
        alcMakeContextCurrent(NULL);
        alcDestroyContext(audio_context);
        audio_context = NULL;
    }
}

void __bgdexport(mod_theora, module_finalize)() {
    video_stop(NULL, NULL);

    if (audio_context) {
        if (alcMakeContextCurrent(NULL) == ALC_FALSE) {
            fprintf(stderr, "OpenAL error resetting default context\n");
        }
        alcDestroyContext(audio_context);
    }
    audio_context = NULL;

    if (audio_device) {
        if (alcCloseDevice(audio_device) == ALC_FALSE) {
            fprintf(stderr, "OpenAL error closing audio device\n");
        }
    }
    audio_device = NULL;
}

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

#include <theoraplay.h>
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#include <SDL.h>

/* PixTudio stuff */
#include <bgddl.h>
#include <xstrings.h>
#include <libgrbase.h>
#include <g_video.h>
#include <mod_sound.h>

struct ctx
{
    GRAPH *graph;
    SDL_AudioCVT cvt;
    const THEORAPLAY_VideoFrame *frame;
    const THEORAPLAY_AudioPacket *audio;
    THEORAPLAY_Decoder *decoder;
    Uint32 baseticks;
    Uint32 framems;
    ALuint audio_source;
    ALuint audio_buffers[10];
};

ALCdevice *audio_device;
ALCcontext *audio_context;

struct ctx video;

char playing_video = 0;


// TODO: Get the first available audiobuffer
// We need this so that we can reuse the audio buffers
int get_free_audiobuffer() {
}

static void queue_audio(const THEORAPLAY_AudioPacket *audio) {
    ALuint buffer;
    ALuint error;
    ALsizei size;

    // Generate the audio buffer that we'll fill with audio
    alGenBuffers((ALuint)1, &buffer);
    if((error = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "Audio buffer creation failed: %s\n", alGetString(error));
        alDeleteSources(1, &video.audio_source);
        THEORAPLAY_stopDecode(video.decoder);
    }

    size = (ALsizei)(audio->frames * audio->channels * 4); // 4 == sizeof(float32)
    alBufferData(buffer, alGetEnumValue("AL_FORMAT_STEREO_FLOAT32"), audio->samples, size, audio->freq);
    if((error = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "Audio buffer data copying failed: %s\n", alGetString(error));
    } else {
        // Queue the audio buffer for playback
        alSourceQueueBuffers(video.audio_source, 1, &buffer);
    }

    // Free the audio packet
    THEORAPLAY_freeAudio(audio);
} // queue_audio

// Paint the current video frame onscreen, skipping those that we already missed
void refresh_video() {
    if(! playing_video) {
        return;
    }

    void *pixels;
    int pitch;

    const Uint32 now = SDL_GetTicks() - video.baseticks;

    if (!video.frame) {
        video.frame = THEORAPLAY_getVideo(video.decoder);
    }

    // Play video frames when it's time.
    if (video.frame && (video.frame->playms <= now))
    {
        if ( video.framems && ((now - video.frame->playms) >= video.framems) )
        {
            // Skip frames to catch up, but keep track of the last one
            // in case we catch up to a series of dupe frames, which
            // means we'd have to draw that final frame and then wait for
            // more.
            const THEORAPLAY_VideoFrame *last = video.frame;
            while ((video.frame = THEORAPLAY_getVideo(video.decoder)) != NULL)
            {
                THEORAPLAY_freeVideo(last);
                last = video.frame;
                if ((now - video.frame->playms) < video.framems)
                    break;
            } // while

            if (!video.frame)
                video.frame = last;
        } // if

        // do nothing; we're far behind and out of options.
        if (!video.frame) {
            static int warned = 0;
            if (!warned) {
                warned = 1;
                SDL_Log("WARNING: Video playback can't keep up, skipping frames!\n");
            } // if
        } else {
            if(SDL_LockTexture(video.graph->texture, NULL, &pixels, &pitch) < 0) {
                SDL_Log("Error updating texture: %s", SDL_GetError());
            } else {
                memcpy(pixels, video.frame->pixels, video.graph->height * pitch*1.5);
                SDL_UnlockTexture(video.graph->texture);

                // Mark the video GRAPH as dirty so that BennuGD redraws it
                video.graph->modified = 1;
                video.graph->info_flags &=~GI_CLEAN;
            }
        }
        THEORAPLAY_freeVideo(video.frame);
        video.frame = NULL;
    }

    while ((video.audio = THEORAPLAY_getAudio(video.decoder)) != NULL) {
        queue_audio(video.audio);
    }

    return;
}

/* Checks wether the current video is being played */
static int video_is_playing() {
    return playing_video;
}

static int video_play(INSTANCE *my, int * params) {
    int bpp, graphid;
    const int MAX_FRAMES = 30;
    void *pixels;
    int pitch;

    bpp = screen->format->BitsPerPixel;

    if(playing_video == 1) {
        return -1;
    }

    if(! scr_initialized) {
        return (-1);
    }

    /* Start the decoding, we want to use a YUV format to reduce CPU usage */
    video.decoder = THEORAPLAY_startDecodeFile(string_get(params[0]), MAX_FRAMES, THEORAPLAY_VIDFMT_IYUV);
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

    if(! THEORAPLAY_hasVideoStream(video.decoder)) {
        THEORAPLAY_stopDecode(video.decoder);
        return -1;
    }

    if(! THEORAPLAY_hasAudioStream(video.decoder)) {
        THEORAPLAY_stopDecode(video.decoder);
        return -1;
    }

    while (!video.frame || !video.audio) {
        if (!video.frame) video.frame = THEORAPLAY_getVideo(video.decoder);
        if (!video.audio) video.audio = THEORAPLAY_getAudio(video.decoder);
        SDL_Delay(10);
    }

    video.framems = (video.frame->fps == 0.0) ? 0 : ((Uint32) (1000.0 / video.frame->fps));

    // Generate the audio source
    alGenSources((ALuint)1, &video.audio_source);
    if(alGetError() != AL_NO_ERROR) {
        fprintf(stderr, "Audio source creation failed\n");
        alcCloseDevice(audio_device);
        THEORAPLAY_stopDecode(video.decoder);
        return -1;
    }
    // Set the source properties (probably not strictly required)
    alSourcef(video.audio_source, AL_PITCH, 1);
    alSourcef(video.audio_source, AL_GAIN, 1);
    alSource3f(video.audio_source, AL_POSITION, 0, 0, 0);
    alSource3f(video.audio_source, AL_VELOCITY, 0, 0, 0);
    alSourcei(video.audio_source, AL_LOOPING, AL_FALSE);

    while (video.audio) {
        queue_audio(video.audio);
        video.audio = THEORAPLAY_getAudio(video.decoder);
    } // while

    video.baseticks = SDL_GetTicks();

    // Create the graph holding the video surface
    graphid = bitmap_next_code();
    video.graph = bitmap_new_streaming(graphid, video.frame->width, video.frame->height, bpp);
    if(! video.graph) {
        THEORAPLAY_stopDecode(video.decoder);
        video.decoder = NULL;
        //alDeleteSources(1, &video.audio_source);
        THEORAPLAY_stopDecode(video.decoder);
        return -1;
    }

    // Blank the GRAPH texture before showing it, otherwise junk will be shown
    if(SDL_LockTexture(video.graph->texture, NULL, &pixels, &pitch) < 0) {
        SDL_Log("Error updating texture: %s", SDL_GetError());
    } else {
        memcpy(pixels, video.frame->pixels, video.graph->height * pitch*1.5);
        SDL_UnlockTexture(video.graph->texture);
    }

    grlib_add_map( 0, video.graph ) ;
    THEORAPLAY_freeVideo(video.frame);
    video.frame = NULL;

    alSourcePlay(video.audio_source);

    playing_video = 1;

    return video.graph->code;
}

/* Stop the currently being played video and release theoraplay stuff */
static int video_stop(INSTANCE *my, int * params) {
    ALuint error;

    if(! playing_video) {
        return 0;
    }

    // Immediately stop audio playback
    alSourceStop(video.audio_source);

    /* Release the video playback lock */
    playing_video = 0;

    if(video.graph) {
        grlib_unload_map(0, video.graph->code);
        video.graph = NULL;
    }

    if(video.decoder) {
        THEORAPLAY_stopDecode(video.decoder);
        video.decoder = NULL;
    }

    alDeleteSources(1, &video.audio_source);
    if((error = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "OpenAL error deleting source: %x, %s\n", error, alGetString(error));
    }

    return 0;
}

/* TODO: Pause the currently playing video */
static int video_pause() {
    return 0;
}

DLSYSFUNCS __bgdexport( mod_theora, functions_exports )[] = {
	{"VIDEO_PLAY"                  , "S"    , TYPE_DWORD , video_play       },
	{"VIDEO_STOP"                  , ""     , TYPE_DWORD , video_stop       },
    {"VIDEO_PAUSE"                 , ""     , TYPE_DWORD , video_pause      },
	{"VIDEO_IS_PLAYING"            , ""     , TYPE_DWORD , video_is_playing },
	{ NULL        , NULL , 0         , NULL              }
};

char * __bgdexport( mod_theora, modules_dependency )[] = {
	"libgrbase",
	"libvideo",
    "mod_sound",
	NULL
};

void __bgdexport( mod_theora, module_initialize )() {
    // Initialize OpenAL
    alGetError();  // clear error stack
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
    printf("WARNING!!! mod_theora will leak like hell right now!\n");
    /*printf("\tAL Extensions: %s\n", alGetString(AL_EXTENSIONS));
    printf("\tALC Extensions: %s\n", alcGetString(audio_device, ALC_EXTENSIONS));*/

    // Since audio in the Theora videos is float32, load that extension
    if(! alIsExtensionPresent("AL_EXT_FLOAT32")) {
        fprintf(stderr, "OpenAL Extension AL_EXT_FLOAT32 not present, refusing to initialise\n");
        alcMakeContextCurrent(NULL);
        alcDestroyContext(audio_context);
        alcCloseDevice(audio_device);
    }
}

void __bgdexport( mod_theora, module_finalize )() {
    ALuint error;

    video_stop(NULL, NULL);

    if(audio_context) {
        alcMakeContextCurrent(NULL);
        if((error=alGetError()) != AL_NO_ERROR) {
            fprintf(stderr, "OpenAL error resetting default context: 0x%x, %s\n", error, alGetString(error));
        }
        alcDestroyContext(audio_context);
        if((error=alGetError()) != AL_NO_ERROR) {
            fprintf(stderr, "OpenAL error deleting context: 0x%x, %s\n", error, alGetString(error));
        }
    }

    if(audio_device) {
        alcCloseDevice(audio_device);
        if((error=alGetError()) != AL_NO_ERROR) {
            fprintf(stderr, "OpenAL error closing audio device: 0x%x\n", error);
        }
    }
}

/* ----------------------------------------------------------------- */

/* Bigest priority first execute
 Lowest priority last execute */

HOOK __bgdexport( mod_theora, handler_hooks )[] = {
    { 3000, refresh_video                     },
    {    0, NULL                              }
} ;

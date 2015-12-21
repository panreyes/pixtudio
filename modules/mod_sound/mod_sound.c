/*
 *  Copyright (C) 2014-2015 Joseba García Etxebarria <joseba.gar@gmail.com>
 *  Copyright (C) 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright (C) 2002-2006 Fenix Team (Fenix)
 *  Copyright (C) 1999-2002 José Luis Cebrián Pagüe (Fenix)
 *
 *  This file is part of PixTudio
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
 *
 */

#ifdef _MSC_VER
#pragma comment (lib, "SDL_mixer")
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgddl.h"

#include <SDL.h>
#include <stretchy_buffer.h>

#include "mod_sound.h"

#include <SDL_mixer.h>

#include "files.h"
#include "xstrings.h"

#include "dlvaracc.h"

#include "bgload.h"

#ifndef __MONOLITHIC__
#include "mod_sound_symbols.h"
#else
extern DLVARFIXUP  __bgdexport( mod_sound, globals_fixup )[];
#endif

/* --------------------------------------------------------------------------- */

static Mix_Music **loaded_songs = NULL;
static Mix_Chunk **loaded_sounds = NULL;

/* ------------------------------------- */
/* Interfaz SDL_RWops Bennu              */
/* ------------------------------------- */

static Sint64 SDLCALL __modsound_seek_cb( SDL_RWops *context, Sint64 offset, int whence ) {
    if ( file_seek( context->hidden.unknown.data1, offset, whence ) < 0 ) {
        return ( -1 );
    }

    return( file_pos( context->hidden.unknown.data1 ) );
}

static size_t SDLCALL __modsound_read_cb( SDL_RWops *context, void *ptr, size_t size, size_t maxnum ) {
    int ret = file_read( context->hidden.unknown.data1, ptr, size * maxnum );
    if ( ret > 0 ) {
        ret /= size;
    }

    return( ret );
}

static size_t SDLCALL __modsound_write_cb( SDL_RWops *context, const void *ptr, size_t size, size_t num ) {
    int ret = file_write( context->hidden.unknown.data1, ( void * )ptr, size * num );
    if ( ret > 0 ) ret /= size;
    return( ret );
}

static int SDLCALL __modsound_close_cb( SDL_RWops *context ) {
    if ( context ) {
        file_close( context->hidden.unknown.data1 );
        SDL_FreeRW( context );
    }

    return( 0 );
}

static SDL_RWops *SDL_RWFromBGDFP( file *fp ) {
    SDL_RWops *rwops = SDL_AllocRW();
    if ( rwops != NULL ) {
        rwops->seek = __modsound_seek_cb;
        rwops->read = __modsound_read_cb;
        rwops->write = __modsound_write_cb;
        rwops->close = __modsound_close_cb;
        rwops->hidden.unknown.data1 = fp;
    }

    return( rwops );
}

/* --------------------------------------------------------------------------- */

/*
 *  FUNCTION : find_free_musicID
 *
 *  Find a free music spot in given array.
 *  If no spots are available, increment the size of the given array
 *  and return the index of the last element.
 *
 *  PARAMS:
 *      array to find free spot in
 *
 *  RETURN VALUE:
 *
 *      an integer with the position index, or -1 if an error occurred
 *
 */

static int find_free_musicID(Mix_Music **where) {
    int32_t i = 0, len = 0;

    // Try to find an empty spot (the pointer should be NULL there)
    len = sb_count(where);
    for(i=0; i<len; i++) {
        if(where[i] == NULL) {
            return i+1;
        }
    }

    // None available => return -1
    return -1;
}

/*
 *  FUNCTION : find_free_chunkID
 *
 *  Find a free chunk spot in given array.
 *  If no spots are available, increment the size of the given array
 *  and return the index of the last element.
 *
 *  PARAMS:
 *      array to find free spot in
 *
 *  RETURN VALUE:
 *
 *      an integer with the position index, or -1 if an error occurred
 *
 */

static int find_free_chunkID(Mix_Chunk **where) {
    int32_t i = 0, len = 0;

    // Try to find an empty spot (the pointer should be NULL there)
    len = sb_count(where);
    for(i=0; i<len; i++) {
        if(where[i] == NULL) {
            return i+1;
        }
    }

    // None available => return -1
    return -1;
}

/* --------------------------------------------------------------------------- */

/*
 *  FUNCTION : sound_init
 *
 *  Set the SDL_Mixer library
 *
 *  PARAMS:
 *      no params
 *
 *  RETURN VALUE:
 *
 *  no return
 *
 */

int sound_init() {
    int audio_rate;
    Uint16 audio_format;
    int audio_channels;
    int audio_buffers;
    int audio_mix_channels;

    if ( !audio_initialized ) {
        /* Initialize variables: but limit quality to some fixed options */

        audio_rate = GLODWORD( mod_sound, SOUND_FREQ );

        if ( audio_rate > 22050 )
            audio_rate = 44100;
        else if ( audio_rate > 11025 )
            audio_rate = 22050;
        else
            audio_rate = 11025;

        audio_format = AUDIO_S16;
        audio_channels = GLODWORD( mod_sound, SOUND_MODE ) + 1;
        audio_buffers = 1024 * audio_rate / 22050;

        /* Open the audio device */
        if ( Mix_OpenAudio( audio_rate, audio_format, audio_channels, audio_buffers ) >= 0 )
        {
            GLODWORD( mod_sound, SOUND_CHANNELS ) <= 32 ? Mix_AllocateChannels( GLODWORD( mod_sound, SOUND_CHANNELS ) ) : Mix_AllocateChannels( 32 ) ;
            Mix_QuerySpec( &audio_rate, &audio_format, &audio_channels );
            audio_mix_channels = Mix_AllocateChannels( -1 ) ;
            GLODWORD( mod_sound, SOUND_CHANNELS ) = audio_mix_channels ;

            audio_initialized = 1;
            return 0;
        }
    }

    fprintf( stderr, "[SOUND] Couldn't initialize sound: %s\n", SDL_GetError() ) ;
    audio_initialized = 0;
    return -1 ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : sound_close
 *
 *  Close all the audio set
 *
 *  PARAMS:
 *      no params
 *
 *  RETURN VALUE:
 *
 *  no return
 *
 */

static void sound_close() {
    if ( !audio_initialized ) {
        return;
    }

    // We should be checking if everything's unloaded

    Mix_CloseAudio();

    audio_initialized = 0;
}


/* ------------------ */
/* Sonido MOD y OGG   */
/* ------------------ */

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : load_song
 *
 *  Load a MOD/OGG from a file
 *
 *  PARAMS:
 *      file name
 *
 *  RETURN VALUE:
 *
 *  mod pointer
 *
 */

static int32_t load_song( const char * filename ) {
    Mix_Music *music = NULL;
    int32_t    id;
    file      *fp;

    if ( !audio_initialized && sound_init() ) {
        return ( 0 );
    }

    if ( !( fp = file_open( filename, "rb0" ) ) ) {
        return ( 0 );
    }

    if ( !( music = Mix_LoadMUS_RW( SDL_RWFromBGDFP( fp ), 0 ) ) ) {
        file_close( fp );
        fprintf( stderr, "Couldn't load %s: %s\n", filename, SDL_GetError() );
        return( 0 );
    }

    id = find_free_musicID(loaded_songs);
    if (id == -1 ) {
        sb_push(loaded_songs, music);
        id = sb_count(loaded_songs);
    } else {
        loaded_songs[id-1] = music;
    }

    return ( id );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : play_song
 *
 *  Play a MOD/OGG
 *
 *  PARAMS:
 *      mod pointer
 *      number of loops (-1 infinite loops)
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int play_song( int32_t id, int loops ) {
    id--;

    if ( audio_initialized ) {
        if ( id >= 0 && id < sb_count(loaded_songs) && loaded_songs[id] ) {
            int result = Mix_PlayMusic(loaded_songs[id], loops );
            if ( result == -1 ) {
                fprintf( stderr, "%s", Mix_GetError() );
            }
            return result;
        }
    }

    fprintf( stderr, "Play song called with invalid handle\n" );
    return( -1 );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : fade_music_in
 *
 *  Play a MOD/OGG fading in it
 *
 *  PARAMS:
 *      mod pointer
 *      number of loops (-1 infinite loops)
 *      ms  microsends of fadding
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int fade_music_in( int32_t id, int loops, int ms ) {
    id--;

    if ( audio_initialized ) {
        if ( id >= 0 && id < sb_count(loaded_songs) && loaded_songs[id] ) {
            return( Mix_FadeInMusic(loaded_songs[id], loops, ms ) );
        }
    }

    return( -1 );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : fade_music_out
 *
 *  Stop the play of a mod
 *
 *  PARAMS:
 *
 *  ms  microsends of fadding
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int fade_music_out( int ms ) {
    if ( !audio_initialized ) {
        return ( 0 );
    }

    return ( Mix_FadeOutMusic( ms ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : unload_song
 *
 *  Play a MOD
 *
 *  PARAMS:
 *
 *  mod id
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int unload_song( int32_t id ) {
    id--;

    if ( audio_initialized && loaded_songs[id] ) {
        if ( id >= 0 && id < sb_count(loaded_songs) && loaded_songs[id] ) {
            if ( Mix_PlayingMusic() ) {
                Mix_HaltMusic();
            }

            Mix_FreeMusic(loaded_songs[id] );
            loaded_songs[id] = NULL;
        }
    }
    return ( 0 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : stop_song
 *
 *  Stop the play of a mod
 *
 *  PARAMS:
 *
 *  no params
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int stop_song( void ) {
    if ( audio_initialized ) {
        Mix_HaltMusic();
    }

    return ( 0 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : pause_song
 *
 *  Pause the mod in curse, you can resume it after
 *
 *  PARAMS:
 *
 *  no params
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int pause_song( void ) {
    if ( audio_initialized ) {
        Mix_PauseMusic();
    }

    return ( 0 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : resume_song
 *
 *  Resume the mod, paused before
 *
 *  PARAMS:
 *
 *  no params
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int resume_song( void ) {
    if ( audio_initialized ) {
        Mix_ResumeMusic();
    }

    return( 0 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : is_playing_song
 *
 *  Check if there is any mod playing
 *
 *  PARAMS:
 *
 *  no params
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *  TRUE OR FALSE if there is no error
 *
 */

static int is_playing_song( void ) {
    if ( !audio_initialized ) {
        return ( 0 );
    }

    return Mix_PlayingMusic();
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : set_song_volume
 *
 *  Set the volume for mod playing (0-128)
 *
 *  PARAMS:
 *
 *  int volume
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *  0 if there is no error
 *
 */

static int set_song_volume( int volume ) {
    if ( !audio_initialized && sound_init() ) {
        return ( -1 );
    }

    volume < 0 ? volume = 0 : 0 ;
    volume > 128 ? volume = 128 : 0 ;

    Mix_VolumeMusic( volume );
    return 0;
}

/* ------------ */
/* Sonido WAV   */
/* ------------ */

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : load_wav
 *
 *  Load a WAV from a file
 *
 *  PARAMS:
 *      file name
 *
 *  RETURN VALUE:
 *
 *  wav pointer
 *
 */

static int32_t load_wav( const char * filename ) {
    Mix_Chunk *sound = NULL;
    int32_t    id = 0;
    file      *fp;

    if ( !audio_initialized && sound_init() ) {
        return ( 0 );
    }

    if ( !( fp = file_open( filename, "rb0" ) ) ) {
        return ( 0 );
    }

    if ( !( sound = Mix_LoadWAV_RW( SDL_RWFromBGDFP( fp ), 1 ) ) ) {
        file_close( fp );
        fprintf( stderr, "Couldn't load %s: %s\n", filename, SDL_GetError() );
        return( 0 );
    }

    id = find_free_chunkID(loaded_sounds);
    if ( id == -1 ) {
        sb_push(loaded_sounds, sound);
        id = sb_count(loaded_sounds);
    } else {
        loaded_sounds[id-1] = sound;
    }

    return ( id );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : play_wav
 *
 *  Play a WAV
 *
 *  PARAMS:
 *      wav pointer;
 *      number of loops (-1 infinite loops)
 *      channel (-1 any channel)
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *  else channel where the music plays
 *
 */

static int play_wav( int32_t id, int loops, int channel ) {
    id--;

    if ( audio_initialized ) {
        if ( id >= 0 && id < sb_count(loaded_sounds) && loaded_sounds[id] ) {
            return ( Mix_PlayChannel( channel, loaded_sounds[id], loops ) );
        }
    }

    return ( -1 );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : unload_wav
 *
 *  Frees the resources from a wav, unloading it
 *
 *  PARAMS:
 *
 *  wav pointer
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int unload_wav( int32_t id ) {
    id--;

    if ( audio_initialized ) {
        if ( id >= 0 && id < sb_count(loaded_sounds) && loaded_sounds[id] ) {
            Mix_FreeChunk(loaded_sounds[id]);
            loaded_sounds[id] = NULL;
        }
    }

    return ( 0 );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : stop_wav
 *
 *  Stop a wav playing
 *
 *  PARAMS:
 *
 *  int channel
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int stop_wav( int channel ) {
    if ( audio_initialized && Mix_Playing( channel ) ) {
        return( Mix_HaltChannel( channel ) );
    }

    return ( -1 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : pause_wav
 *
 *  Pause a wav playing, you can resume it after
 *
 *  PARAMS:
 *
 *  int channel
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int pause_wav( int channel ) {
    if ( audio_initialized && Mix_Playing( channel ) ) {
        Mix_Pause( channel );
        return ( 0 ) ;
    }

    return ( -1 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : resume_wav
 *
 *  Resume a wav playing, paused before
 *
 *  PARAMS:
 *
 *  int channel
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int resume_wav( int channel ) {
    if ( audio_initialized && Mix_Playing( channel ) ) {
        Mix_Resume( channel );
        return ( 0 ) ;
    }

    return ( -1 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : is_playing_wav
 *
 *  Check a wav playing
 *
 *  PARAMS:
 *
 *  int channel
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *  TRUE OR FALSE if there is no error
 *
 */

static int is_playing_wav( int canal ) {
    if ( audio_initialized ) {
        return( Mix_Playing( canal ) );
    }

    return ( 0 );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : set_wav_volume
 *
 *  Set the volume for wav playing (0-128) IN SAMPLE
 *
 *  PARAMS:
 *
 *  channel id
 *  int volume
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int set_wav_volume( int32_t id, int volume ) {
    if ( !audio_initialized ) {
        return ( -1 );
    }

    id--;

    volume < 0 ? volume = 0 : 0 ;
    volume > 128 ? volume = 128 : 0 ;

    if ( id >= 0 && id < sb_count(loaded_sounds) && loaded_sounds[id] ) {
        return( Mix_VolumeChunk(loaded_sounds[id], volume ) );
    }

    return -1 ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : set_channel_volume
 *
 *  Set the volume for wav playing (0-128) IN CHANNEL
 *
 *  PARAMS:
 *
 *  channel id
 *  int volume
 *
 *  RETURN VALUE:
 *
 * -1 if there is any error
 *
 */

static int  set_channel_volume( int channel, int volume ) {
    if ( !audio_initialized && sound_init() ) {
        return ( -1 );
    }

    volume < 0 ? volume = 0 : 0 ;
    volume > 128 ? volume = 128 : 0 ;

    return( Mix_Volume( channel, volume ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : reserve_channels
 *
 *  Reserve the first channels (0 -> n-1) for the application, i.e. don't allocate
 *  them dynamically to the next sample if requested with a -1 value below.
 *
 *  PARAMS:
 *  number of channels to reserve.
 *
 *  RETURN VALUE:
 *  number of reserved channels.
 * -1 if there is any error
 *
 */

static int reserve_channels( int channels ) {
    if ( !audio_initialized && sound_init() ) {
        return ( -1 );
    }

    return Mix_ReserveChannels( channels );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : set_panning
 *
 *  Set the panning for a wav channel
 *
 *  PARAMS:
 *
 *  channel
 *  left volume (0-255)
 *  right volume (0-255)
 *
 */

static int set_panning( int channel, int left, int right ) {
    if ( !audio_initialized && sound_init() ) {
        return ( -1 );
    }

    if ( Mix_Playing( channel ) ) {
        Mix_SetPanning( channel, ( Uint8 )left, ( Uint8 )right );
        return ( 0 ) ;
    }

    return ( -1 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : set_position
 *
 *  Set the position of a channel. (angle) is an integer from 0 to 360
 *
 *  PARAMS:
 *
 *  channel
 *  angle (0-360)
 *  distance (0-255)
 *
 */

static int set_position( int channel, int angle, int dist ) {
    if ( !audio_initialized && sound_init() ) {
        return ( -1 );
    }

    if ( Mix_Playing( channel ) ) {
        Mix_SetPosition( channel, ( Sint16 )angle, ( Uint8 )dist );
        return ( 0 ) ;
    }

    return ( -1 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : set_distance
 *
 *  Set the "distance" of a channel. (distance) is an integer from 0 to 255
 *  that specifies the location of the sound in relation to the listener.
 *
 *  PARAMS:
 *
 *  channel
 *
 *  distance (0-255)
 *
 */

static int set_distance( int channel, int dist ) {
    if ( !audio_initialized && sound_init() ) {
        return ( -1 );
    }

    if ( Mix_Playing( channel ) ) {
        Mix_SetDistance( channel, ( Uint8 )dist );
        return ( 0 ) ;
    }

    return ( -1 ) ;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : reverse_stereo
 *
 *  Causes a channel to reverse its stereo.
 *
 *  PARAMS:
 *
 *  channel
 *  flip  0 normal  != reverse
 *
 */

static int reverse_stereo( int channel, int flip ) {
    if ( !audio_initialized && sound_init() ) {
        return ( -1 );
    }

    if ( Mix_Playing( channel ) ) {
        Mix_SetReverseStereo( channel, flip );
        return ( 0 ) ;
    }

    return ( -1 ) ;
}

/* --------------------------------------------------------------------------- */
/* Sonido                                                                      */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_load_song
 *
 *  Load a MOD from a file
 *
 *  PARAMS:
 *      file name
 *
 *  RETURN VALUE:
 *
 *      mod id
 *
 */

int32_t modsound_load_song( INSTANCE * my, int * params ) {
    int var;
    const char * filename ;

    if ( !( filename = string_get( params[0] ) ) ) {
        return ( 0 ) ;
    }

    var = load_song( filename );
    string_discard( params[0] );

    return ( var );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_load_song2
 *
 *  Load a MOD from a file
 *
 *  PARAMS:
 *      file name
 *      pointer mod id
 *
 *  RETURN VALUE:
 *
 *
 */

int modsound_bgload_song( INSTANCE * my, int * params ) {
    bgload( load_song, params );

    return 0;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_play_song
 *
 *  Play a MOD
 *
 *  PARAMS:
 *      mod id;
 *      number of loops (-1 infinite loops)
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_play_song( INSTANCE * my, int * params ) {
    if ( params[0] == -1 ) {
        return -1;
    }

    return( play_song( params[0], params[1] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_unload_song
 *
 *  Frees the resources from a MOD and unloads it
 *
 *  PARAMS:
 *      mod id;
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_unload_song( INSTANCE * my, int * params ) {
    if ( params[0] <= 0 ) {
        return ( -1 );
    }

    return( unload_song( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_unload_song2
 *
 *  Frees the resources from a MOD and unloads it
 *
 *  PARAMS:
 *      mod *id;
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_unload_song2( INSTANCE * my, int * params ) {
    int *s = (int *)(params[0]), r;
    if ( !s || *s <= 0 ) {
        return ( -1 );
    }

    r = unload_song( *s );
    *s = 0;
    return( r );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_stop_song
 *
 *  Stop the play of a mod
 *
 *  PARAMS:
 *
 *  no params
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_stop_song( INSTANCE * my, int * params ) {
    return( stop_song() );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_pause_song
 *
 *  Pause the mod in curse, you can resume it after
 *
 *  PARAMS:
 *
 *  no params
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_pause_song( INSTANCE * my, int * params ) {
    return( pause_song() );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_resume_song
 *
 *  Resume the mod, paused before
 *
 *  PARAMS:
 *
 *  no params
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_resume_song( INSTANCE * my, int * params ) {
    return( resume_song() );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_is_playing_song
 *
 *  Check if there is any mod playing
 *
 *  PARAMS:
 *
 *  no params
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  TRUE OR FALSE if there is no error
 *
 */

int modsound_is_playing_song( INSTANCE * my, int * params ) {
    return ( is_playing_song() );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_set_song_volume
 *
 *  Set the volume for mod playing (0-128)
 *
 *  PARAMS:
 *
 *  int volume
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if there is no error
 *
 */

int modsound_set_song_volume( INSTANCE * my, int * params ) {
    return ( set_song_volume( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_fade_music_in
 *
 *  Play a MOD/OGG fading in it
 *
 *  PARAMS:
 *      mod pointer
 *      number of loops (-1 infinite loops)
 *      ms  microsends of fadding
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *
 */

int modsound_fade_music_in( INSTANCE * my, int * params ) {
    if ( params[0] == -1 ) {
        return -1;
    }

    return ( fade_music_in( params[0], params[1], params[2] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_fade_music_out
 *
 *  Stop the play of a mod
 *
 *  PARAMS:
 *
 *  ms  microsends of fadding
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *
 */

int modsound_fade_music_out( INSTANCE * my, int * params ) {
    return ( fade_music_out( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_load_wav
 *
 *  Load a WAV from a file
 *
 *  PARAMS:
 *      file name
 *
 *  RETURN VALUE:
 *
 *      wav id
 *
 */

int32_t modsound_load_wav( INSTANCE * my, int * params ) {
    int var;
    const char * filename ;

    if ( !( filename = string_get( params[0] ) ) ) {
        return ( 0 ) ;
    }

    var = load_wav( filename );
    string_discard( params[0] );

    return ( var );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_load_wav2
 *
 *  Load a WAV from a file
 *
 *  PARAMS:
 *      file name
 *      pointer wav id
 *
 *  RETURN VALUE:
 *
 *
 */

int modsound_bgload_wav( INSTANCE * my, int * params ) {
    bgload( load_wav, params );

    return 0;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_play_wav
 *
 *  Play a WAV
 *
 *  PARAMS:
 *      wav id;
 *      number of loops (-1 infinite loops)
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_play_wav( INSTANCE * my, int * params ) {
    if ( params[0] == -1 ) {
        return -1;
    }

    return( play_wav( params[0], params[1], -1 ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_play_wav_channel
 *
 *  Play a WAV
 *
 *  PARAMS:
 *      wav id;
 *      number of loops (-1 infinite loops)
 *      channel (-1 like modsound_play_wav)
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_play_wav_channel( INSTANCE * my, int * params ) {
    if ( params[0] == -1 ) {
        return -1;
    }

    return( play_wav( params[0], params[1], params[2] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_unload_wav
 *
 *  Frees the resources from a wav, unloading it
 *
 *  PARAMS:
 *
 *  mod id
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_unload_wav( INSTANCE * my, int * params ) {
    if ( params[0] == -1 ) {
        return -1;
    }

    return( unload_wav( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_unload_wav2
 *
 *  Frees the resources from a wav, unloading it
 *
 *  PARAMS:
 *
 *  mod *id
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_unload_wav2( INSTANCE * my, int * params ) {
    int *s = (int *)(params[0]), r;

    if ( !s || *s == -1 ) {
        return ( -1 );
    }

    r = unload_wav( *s );
    *s = 0;

    return( r );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_stop_wav
 *
 *  Stop a wav playing
 *
 *  PARAMS:
 *
 *  wav id
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_stop_wav( INSTANCE * my, int * params ) {
    return( stop_wav( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_pause_wav
 *
 *  Pause a wav playing, you can resume it after
 *
 *  PARAMS:
 *
 *  wav id
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_pause_wav( INSTANCE * my, int * params ) {
    return ( pause_wav( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : resume_wav
 *
 *  Resume a wav playing, paused before
 *
 *  PARAMS:
 *
 *  wav id
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if all goes ok
 *
 */

int modsound_resume_wav( INSTANCE * my, int * params ) {
    return ( resume_wav( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : is_playing_wav
 *
 *  Check a wav playing
 *
 *  PARAMS:
 *
 *  wav id
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  TRUE OR FALSE if there is no error
 *
 */


int modsound_is_playing_wav( INSTANCE * my, int * params ) {
    return ( is_playing_wav( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_set_channel_volume
 *
 *  Set the volume for a wav playing (0-128)
 *
 *  PARAMS:
 *
 *  wav id
 *  int volume
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if there is no error
 *
 */

int modsound_set_channel_volume( INSTANCE * my, int * params ) {
    return( set_channel_volume( params[0], params[1] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_reserve_channels
 *
 *  Reserve the first channels (0 -> n-1) for the application, i.e. don't allocate
 *  them dynamically to the next sample if requested with a -1 value below.
 *
 *  PARAMS:
 *  number of channels to reserve.
 *
 *  RETURN VALUE:
 *  number of reserved channels.
 *  -1 if there is any error
 *
 */

int modsound_reserve_channels( INSTANCE * my, int * params ) {
    return ( reserve_channels( params[0] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_set_wav_volume
 *
 *  Set the volume for a wav playing (0-128)
 *
 *  PARAMS:
 *
 *  wav id
 *  int volume
 *
 *  RETURN VALUE:
 *
 *  -1 if there is any error
 *  0 if there is no error
 *
 */

int modsound_set_wav_volume( INSTANCE * my, int * params ) {
    return( set_wav_volume( params[0], params[1] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_set_panning
 *
 *  Set the panning for a wav channel
 *
 *  PARAMS:
 *
 *  channel
 *  left volume (0-255)
 *  right volume (0-255)
 *
 */

int modsound_set_panning( INSTANCE * my, int * params ) {
    return( set_panning( params[0], params[1], params[2] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_set_position
 *
 *  Set the position of a channel. (angle) is an integer from 0 to 360
 *
 *  PARAMS:
 *
 *  channel
 *  angle (0-360)
 *  distance (0-255)
 *
 */

int modsound_set_position( INSTANCE * my, int * params ) {
    return( set_position( params[0], params[1], params[2] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_set_distance
 *
 *  Set the "distance" of a channel. (distance) is an integer from 0 to 255
 *  that specifies the location of the sound in relation to the listener.
 *
 *  PARAMS:
 *
 *  channel
 *
 *  distance (0-255)
 *
 */

int modsound_set_distance( INSTANCE * my, int * params ) {
    return( set_distance( params[0], params[1] ) );
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : modsound_reverse_stereo
 *
 *  Causes a channel to reverse its stereo.
 *
 *  PARAMS:
 *
 *  channel
 *
 *  flip 0 normal != reverse
 *
 */

int modsound_reverse_stereo( INSTANCE * my, int * params ) {
    return( reverse_stereo( params[0], params[1] ) );
}

/* --------------------------------------------------------------------------- */

int modsound_set_music_position( INSTANCE * my, int * params ) {
    return ( Mix_SetMusicPosition( ( double ) *( float * ) &params[0] ) );
}

/* --------------------------------------------------------------------------- */

int modsound_init( INSTANCE * my, int * params ) {
    return( sound_init() );
}

/* --------------------------------------------------------------------------- */

int modsound_close( INSTANCE * my, int * params ) {
    sound_close();
    return( 0 );
}

/* --------------------------------------------------------------------------- */

void  __bgdexport( mod_sound, module_initialize )() {
    if ( !SDL_WasInit( SDL_INIT_AUDIO ) ) {
        SDL_InitSubSystem( SDL_INIT_AUDIO );
    }
}

/* --------------------------------------------------------------------------- */

void __bgdexport( mod_sound, module_finalize )() {
    if(audio_initialized) {
        sound_close();
    }

    int32_t i=0, n=0;
    // Unload songs, if any
    n = sb_count(loaded_songs);
    for(i=0; i<n; i++) {
        unload_song(i);
    }
    sb_free(loaded_songs);

    // Unload sounds, if any
    n = sb_count(loaded_sounds);
    for(i=0; i<n; i++) {
        unload_wav(i);
    }
    sb_free(loaded_sounds);

    if ( SDL_WasInit( SDL_INIT_AUDIO ) ) {
        SDL_QuitSubSystem( SDL_INIT_AUDIO );
    }
}

/* --------------------------------------------------------------------------- */

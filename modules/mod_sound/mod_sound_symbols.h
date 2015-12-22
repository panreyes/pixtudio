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

#ifndef __MODSOUND_H
#define __MODSOUND_H

#include <bgddl.h>

#ifndef __PXTB__
extern int modsound_init( INSTANCE * my, int * params );
extern int modsound_close( INSTANCE * my, int * params );
extern int32_t modsound_load_song( INSTANCE * my, int * params );
extern int modsound_bgload_song( INSTANCE * my, int * params );
extern int modsound_unload_song( INSTANCE * my, int * params );
extern int modsound_unload_song2( INSTANCE * my, int * params );
extern int modsound_unload_song2( INSTANCE * my, int * params );
extern int modsound_play_song( INSTANCE * my, int * params );
extern int modsound_stop_song( INSTANCE * my, int * params );
extern int modsound_pause_song( INSTANCE * my, int * params );
extern int modsound_resume_song( INSTANCE * my, int * params );
extern int modsound_set_song_volume( INSTANCE * my, int * params );
extern int modsound_is_playing_song( INSTANCE * my, int * params );
extern int32_t modsound_load_wav( INSTANCE * my, int * params );
extern int modsound_bgload_wav( INSTANCE * my, int * params );
extern int modsound_unload_wav( INSTANCE * my, int * params );
extern int modsound_unload_wav2( INSTANCE * my, int * params );
extern int modsound_unload_wav2( INSTANCE * my, int * params );
extern int modsound_play_wav( INSTANCE * my, int * params );
extern int modsound_play_wav_channel( INSTANCE * my, int * params );
extern int modsound_play_wav_channel( INSTANCE * my, int * params );
extern int modsound_stop_wav( INSTANCE * my, int * params );
extern int modsound_pause_wav( INSTANCE * my, int * params );
extern int modsound_resume_wav( INSTANCE * my, int * params );
extern int modsound_is_playing_wav( INSTANCE * my, int * params );
extern int modsound_fade_music_in( INSTANCE * my, int * params );
extern int modsound_fade_music_out( INSTANCE * my, int * params );
extern int modsound_set_wav_volume( INSTANCE * my, int * params );
extern int modsound_set_channel_volume( INSTANCE * my, int * params );
extern int modsound_reserve_channels( INSTANCE * my, int * params );
extern int modsound_set_panning( INSTANCE * my, int * params );
extern int modsound_set_position( INSTANCE * my, int * params );
extern int modsound_set_distance( INSTANCE * my, int * params );
extern int modsound_reverse_stereo( INSTANCE * my, int * params );
extern int modsound_set_music_position( INSTANCE * my, int * params );

DLVARFIXUP  __bgdexport( mod_sound, globals_fixup )[] = {
    { "sound_freq",     NULL, -1, -1 },
    { "sound_mode",     NULL, -1, -1 },
    { "sound_channels", NULL, -1, -1 },
    { NULL,             NULL, -1, -1 }
};

extern void  __bgdexport( mod_sound, module_initialize )();
extern void __bgdexport( mod_sound, module_finalize )();
#endif

DLCONSTANT  __bgdexport( mod_sound, constants_def )[] = {
    { "MODE_MONO"   , TYPE_INT,  0 },
    { "MODE_STEREO" , TYPE_INT,  1 },
    { "ALL_SOUND"   , TYPE_INT, -1 },
    { NULL          , 0       ,  0 }
} ;

char __bgdexport( mod_sound, globals_def )[] =
    "   sound_freq = 44100 ;\n"
    "   sound_mode = MODE_STEREO ;\n"
    "   sound_channels = 8 ;\n";

DLSYSFUNCS  __bgdexport( mod_sound, exported_functions )[] = {
    FUNC( "SOUND_INIT"          , ""     , TYPE_INT , modsound_init               ),
    FUNC( "SOUND_CLOSE"         , ""     , TYPE_INT , modsound_close              ),

    FUNC( "LOAD_SONG"           , "S"    , TYPE_INT , modsound_load_song          ),
    FUNC( "LOAD_SONG"           , "SP"   , TYPE_INT , modsound_bgload_song        ),
    FUNC( "UNLOAD_SONG"         , "I"    , TYPE_INT , modsound_unload_song        ),
    FUNC( "UNLOAD_SONG"         , "P"    , TYPE_INT , modsound_unload_song2       ),

    FUNC( "PLAY_SONG"           , "II"   , TYPE_INT , modsound_play_song          ),
    FUNC( "STOP_SONG"           , ""     , TYPE_INT , modsound_stop_song          ),
    FUNC( "PAUSE_SONG"          , ""     , TYPE_INT , modsound_pause_song         ),
    FUNC( "RESUME_SONG"         , ""     , TYPE_INT , modsound_resume_song        ),

    FUNC( "SET_SONG_VOLUME"     , "I"    , TYPE_INT , modsound_set_song_volume    ),

    FUNC( "IS_PLAYING_SONG"     , ""     , TYPE_INT , modsound_is_playing_song    ),

    FUNC( "LOAD_WAV"            , "S"    , TYPE_INT , modsound_load_wav           ),
    FUNC( "LOAD_WAV"            , "SP"   , TYPE_INT , modsound_bgload_wav         ),
    FUNC( "UNLOAD_WAV"          , "I"    , TYPE_INT , modsound_unload_wav         ),
    FUNC( "UNLOAD_WAV"          , "P"    , TYPE_INT , modsound_unload_wav2        ),

    FUNC( "PLAY_WAV"            , "II"   , TYPE_INT , modsound_play_wav           ),
    FUNC( "PLAY_WAV"            , "III"  , TYPE_INT , modsound_play_wav_channel   ),
    FUNC( "STOP_WAV"            , "I"    , TYPE_INT , modsound_stop_wav           ),
    FUNC( "PAUSE_WAV"           , "I"    , TYPE_INT , modsound_pause_wav          ),
    FUNC( "RESUME_WAV"          , "I"    , TYPE_INT , modsound_resume_wav         ),

    FUNC( "IS_PLAYING_WAV"      , "I"    , TYPE_INT , modsound_is_playing_wav     ),

    FUNC( "FADE_MUSIC_IN"       , "III"  , TYPE_INT , modsound_fade_music_in      ),
    FUNC( "FADE_MUSIC_OUT"      , "I"    , TYPE_INT , modsound_fade_music_out     ),

    FUNC( "SET_WAV_VOLUME"      , "II"   , TYPE_INT , modsound_set_wav_volume     ),
    FUNC( "SET_CHANNEL_VOLUME"  , "II"   , TYPE_INT , modsound_set_channel_volume ),

    FUNC( "RESERVE_CHANNELS"    , "I"    , TYPE_INT , modsound_reserve_channels   ),

    FUNC( "SET_PANNING"         , "III"  , TYPE_INT , modsound_set_panning        ),
    FUNC( "SET_POSITION"        , "III"  , TYPE_INT , modsound_set_position       ),
    FUNC( "SET_DISTANCE"        , "II"   , TYPE_INT , modsound_set_distance       ),

    FUNC( "REVERSE_STEREO"      , "II"   , TYPE_INT , modsound_reverse_stereo     ),

    FUNC( "SET_MUSIC_POSITION"  , "F"    , TYPE_INT , modsound_set_music_position ),

    FUNC( 0                     , 0      , 0        , 0                           )
};



extern DLSYSFUNCS  __bgdexport( mod_sound, exported_functions )[];
extern void  __bgdexport( mod_sound, module_initialize )();
extern void __bgdexport( mod_sound, module_finalize )();

#endif

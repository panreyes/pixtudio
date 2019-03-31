/*
 *  Copyright (C) 2014-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
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

#include <pxtdl.h>

#ifndef __PXTB__
extern int modsound_init( INSTANCE * my, intptr_t * params );
extern int modsound_close( INSTANCE * my, intptr_t * params );
extern int32_t modsound_song_load( INSTANCE * my, intptr_t * params );
extern int modsound_song_bgload( INSTANCE * my, intptr_t * params );
extern int modsound_song_unload( INSTANCE * my, intptr_t * params );
extern int modsound_song_unload2( INSTANCE * my, intptr_t * params );
extern int modsound_song_unload2( INSTANCE * my, intptr_t * params );
extern int modsound_song_play( INSTANCE * my, intptr_t * params );
extern int modsound_song_stop( INSTANCE * my, intptr_t * params );
extern int modsound_song_pause( INSTANCE * my, intptr_t * params );
extern int modsound_song_resume( INSTANCE * my, intptr_t * params );
extern int modsound_song_set_volume( INSTANCE * my, intptr_t * params );
extern int modsound_song_is_playing( INSTANCE * my, intptr_t * params );
extern int32_t modsound_sound_load( INSTANCE * my, intptr_t * params );
extern int modsound_sound_bgload( INSTANCE * my, intptr_t * params );
extern int modsound_sound_unload( INSTANCE * my, intptr_t * params );
extern int modsound_sound_unload2( INSTANCE * my, intptr_t * params );
extern int modsound_sound_unload2( INSTANCE * my, intptr_t * params );
extern int modsound_sound_play( INSTANCE * my, intptr_t * params );
extern int modsound_sound_play_channel( INSTANCE * my, intptr_t * params );
extern int modsound_sound_play_channel( INSTANCE * my, intptr_t * params );
extern int modsound_sound_stop( INSTANCE * my, intptr_t * params );
extern int modsound_sound_pause( INSTANCE * my, intptr_t * params );
extern int modsound_sound_resume( INSTANCE * my, intptr_t * params );
extern int modsound_sound_is_playing( INSTANCE * my, intptr_t * params );
extern int modsound_music_fade_in( INSTANCE * my, intptr_t * params );
extern int modsound_music_fade_out( INSTANCE * my, intptr_t * params );
extern int modsound_sound_set_volume( INSTANCE * my, intptr_t * params );
extern int modsound_channel_set_volume( INSTANCE * my, intptr_t * params );
extern int modsound_channels_reserve( INSTANCE * my, intptr_t * params );
extern int modsound_channel_set_panning( INSTANCE * my, intptr_t * params );
extern int modsound_channel_set_position( INSTANCE * my, intptr_t * params );
extern int modsound_channel_set_distance( INSTANCE * my, intptr_t * params );
extern int modsound_stereo_reserve( INSTANCE * my, intptr_t * params );
extern int modsound_music_set_position( INSTANCE * my, intptr_t * params );

DLVARFIXUP  __pxtexport( mod_sound, globals_fixup )[] = {
    { "sound_freq",     NULL, -1, -1 },
    { "sound_mode",     NULL, -1, -1 },
    { "sound_channels", NULL, -1, -1 },
    { NULL,             NULL, -1, -1 }
};

extern void  __pxtexport( mod_sound, module_initialize )();
extern void __pxtexport( mod_sound, module_finalize )();
#endif

DLCONSTANT  __pxtexport( mod_sound, constants_def )[] = {
    { "MODE_MONO"   , TYPE_INT,  0 },
    { "MODE_STEREO" , TYPE_INT,  1 },
    { "ALL_SOUND"   , TYPE_INT, -1 },
    { NULL          , 0       ,  0 }
} ;

char __pxtexport( mod_sound, globals_def )[] =
    "   sound_freq = 44100 ;\n"
    "   sound_mode = MODE_STEREO ;\n"
    "   sound_channels = 8 ;\n";

DLSYSFUNCS  __pxtexport( mod_sound, exported_functions )[] = {
    FUNC( "SOUND_INIT"          , ""     , TYPE_INT , modsound_init                 ),
    FUNC( "SOUND_CLOSE"         , ""     , TYPE_INT , modsound_close                ),

    FUNC( "SONG_LOAD"           , "S"    , TYPE_INT , modsound_song_load            ),
    FUNC( "SONG_LOAD"           , "SP"   , TYPE_INT , modsound_song_bgload          ),
    FUNC( "SONG_UNLOAD"         , "I"    , TYPE_INT , modsound_song_unload          ),
    FUNC( "SONG_UNLOAD"         , "P"    , TYPE_INT , modsound_song_unload2         ),

    FUNC( "SONG_PLAY"           , "II"   , TYPE_INT , modsound_song_play            ),
    FUNC( "SONG_STOP"           , ""     , TYPE_INT , modsound_song_stop            ),
    FUNC( "SONG_PAUSE"          , ""     , TYPE_INT , modsound_song_pause           ),
    FUNC( "SONG_RESUME"         , ""     , TYPE_INT , modsound_song_resume          ),

    FUNC( "SONG_SET_VOLUME"     , "I"    , TYPE_INT , modsound_song_set_volume      ),

    FUNC( "SONG_IS_PLAYING"     , ""     , TYPE_INT , modsound_song_is_playing      ),

    FUNC( "SOUND_LOAD"          , "S"    , TYPE_INT , modsound_sound_load           ),
    FUNC( "SOUND_LOAD"          , "SP"   , TYPE_INT , modsound_sound_bgload         ),
    FUNC( "SOUND_UNLOAD"        , "I"    , TYPE_INT , modsound_sound_unload         ),
    FUNC( "SOUND_UNLOAD"        , "P"    , TYPE_INT , modsound_sound_unload2        ),

    FUNC( "SOUND_PLAY"          , "II"   , TYPE_INT , modsound_sound_play           ),
    FUNC( "SOUND_PLAY"          , "III"  , TYPE_INT , modsound_sound_play_channel   ),
    FUNC( "SOUND_STOP"          , "I"    , TYPE_INT , modsound_sound_stop           ),
    FUNC( "SOUND_PAUSE"         , "I"    , TYPE_INT , modsound_sound_pause          ),
    FUNC( "SOUND_RESUME"        , "I"    , TYPE_INT , modsound_sound_resume         ),

    FUNC( "SOUND_IS_PLAYING"    , "I"    , TYPE_INT , modsound_sound_is_playing     ),

    FUNC( "MUSIC_FADE_IN"       , "III"  , TYPE_INT , modsound_music_fade_in        ),
    FUNC( "MUSIC_FADE_OUT"      , "I"    , TYPE_INT , modsound_music_fade_out       ),

    FUNC( "SOUND_SET_VOLUME"    , "II"   , TYPE_INT , modsound_sound_set_volume     ),
    FUNC( "CHANNEL_SET_VOLUME"  , "II"   , TYPE_INT , modsound_channel_set_volume   ),

    FUNC( "CHANNELS_RESERVE"    , "I"    , TYPE_INT , modsound_channels_reserve     ),

    FUNC( "CHANNEL_SET_PANNING" , "III"  , TYPE_INT , modsound_channel_set_panning  ),
    FUNC( "CHANNEL_SET_POSITION", "III"  , TYPE_INT , modsound_channel_set_position ),
    FUNC( "CHANNEL_SET_DISTANCE", "II"   , TYPE_INT , modsound_channel_set_distance ),

    FUNC( "STEREO_REVERSE"      , "II"   , TYPE_INT , modsound_stereo_reserve       ),

    FUNC( "MUSIC_SET_POSITION"  , "F"    , TYPE_INT , modsound_music_set_position   ),

    FUNC( 0                     , 0      , 0        , 0                             )
};



extern DLSYSFUNCS  __pxtexport( mod_sound, exported_functions )[];
extern void  __pxtexport( mod_sound, module_initialize )();
extern void __pxtexport( mod_sound, module_finalize )();

#endif

/*
 *  Copyright (C) 2015 Joseba Garcí­a Etxebarria. All rights reserved.
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

#ifndef __MODTHEORA_SYMBOLS_H
#define __MODTHEORA_SYMBOLS_H

#include <pxtdl.h>

#ifndef __PXTB__
extern int video_play(INSTANCE *my, intptr_t * params);
extern int video_stop(INSTANCE *my, intptr_t * params);
extern int video_pause();
extern int video_is_playing();
extern int video_set_volume(INSTANCE *my, intptr_t * params);
extern void refresh_video();

HOOK __pxtexport( mod_theora, handler_hooks )[] = {
    { 3000, refresh_video                     },
    {    0, NULL                              }
} ;

extern void __pxtexport( mod_theora, module_initialize )();
extern void __pxtexport( mod_theora, module_finalize )();
#endif

DLSYSFUNCS __pxtexport( mod_theora, exported_functions )[] = {
    FUNC( "VIDEO_PLAY"                 , "S"    , TYPE_DWORD , video_play       ),
    FUNC( "VIDEO_STOP"                 , ""     , TYPE_DWORD , video_stop       ),
    FUNC( "VIDEO_PAUSE"                , ""     , TYPE_DWORD , video_pause      ),
    FUNC( "VIDEO_IS_PLAYING"           , ""     , TYPE_DWORD , video_is_playing ),
    FUNC( "VIDEO_SET_VOLUME"           , "I"    , TYPE_DWORD , video_set_volume ),
    FUNC( NULL                         , NULL   , 0          , NULL             )
};

char * __pxtexport( mod_theora, module_dependencies )[] = {
    "libgrbase",
    "libvideo",
    NULL
};
#endif

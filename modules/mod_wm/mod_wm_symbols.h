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

#ifndef __MODWM_SYMBOLS_H
#define __MODWM_SYMBOLS_H

#include <pxtdl.h>
#include <SDL_messagebox.h>

#ifndef __PXTB__
extern int bgd_set_title( INSTANCE * my, intptr_t * params );
extern int bgd_set_icon( INSTANCE * my, intptr_t * params );
extern int bgd_minimize( INSTANCE * my, intptr_t * params );
extern int bgd_move_window( INSTANCE * my, intptr_t * params );
extern int bgd_get_window_pos( INSTANCE * my, intptr_t * params );
extern int bgd_get_window_size( INSTANCE * my, intptr_t * params );
extern int bgd_get_desktop_size( INSTANCE * my, intptr_t * params );
extern int bgd_disable_screensaver( INSTANCE * my, intptr_t * params );
extern int bgd_enable_screensaver( INSTANCE * my, intptr_t * params );
extern int bgd_get_locale( INSTANCE * my, intptr_t * params );
extern void bgd_show_messagebox( INSTANCE * my, intptr_t * params );
#endif

DLCONSTANT __pxtexport( mod_wm, constants_def)[] = {
    { "MESSAGEBOX_ERROR"       , TYPE_INT , SDL_MESSAGEBOX_ERROR       },
    { "MESSAGEBOX_WARNING"     , TYPE_INT , SDL_MESSAGEBOX_WARNING     },
    { "MESSAGEBOX_INFORMATION" , TYPE_INT , SDL_MESSAGEBOX_INFORMATION },
    { NULL                     , 0        , 0                          }
} ;

DLSYSFUNCS __pxtexport( mod_wm, exported_functions )[] = {
    FUNC( "SET_TITLE"           , "S"   , TYPE_INT      , bgd_set_title           ),
    FUNC( "SET_ICON"            , "II"  , TYPE_INT      , bgd_set_icon            ),
    FUNC( "MINIMIZE"            , ""    , TYPE_INT      , bgd_minimize            ),
    FUNC( "MOVE_WINDOW"         , "II"  , TYPE_INT      , bgd_move_window         ),
    FUNC( "SET_WINDOW_POS"      , "II"  , TYPE_INT      , bgd_move_window         ),
    FUNC( "GET_WINDOW_POS"      , "PP"  , TYPE_INT      , bgd_get_window_pos      ),
    FUNC( "GET_WINDOW_SIZE"     , "PPPP", TYPE_INT      , bgd_get_window_size     ),
    FUNC( "GET_DESKTOP_SIZE"    , "PP"  , TYPE_INT      , bgd_get_desktop_size    ),
    FUNC( "DISABLE_SCREENSAVER" , ""    , TYPE_INT      , bgd_disable_screensaver ),
    FUNC( "ENABLE_SCREENSAVER"  , ""    , TYPE_INT      , bgd_enable_screensaver  ),
    FUNC( "GET_LOCALE"          , ""    , TYPE_STRING   , bgd_get_locale          ),
    FUNC( "MESSAGEBOX"          , "ISS" , TYPE_UNDEFINED, bgd_show_messagebox     ),

    FUNC( 0                     , 0     , 0           , 0                       )
};

char * __pxtexport( mod_wm, module_dependencies )[] = {
    "libgrbase",
    "libvideo",
    "libwm",
    NULL
};

#endif

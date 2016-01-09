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

#ifndef __MODSCREEN_SYMBOLS_H
#define __MODSCREEN_SYMBOLS_H

#include <bgddl.h>

#ifndef __PXTB__
extern int modscreen_define_region( INSTANCE * my, int * params );
extern int modscreen_out_region( INSTANCE * my, int * params );
extern int modscreen_put( INSTANCE * my, int * params );
extern int modscreen_xput( INSTANCE * my, int * params );
extern int modscreen_put_screen( INSTANCE * my, int * params );
extern int modscreen_clear_screen( INSTANCE * my, int * params );
extern int modscreen_get_screen( INSTANCE * my, int * params );

DLVARFIXUP __bgdexport( mod_screen, locals_fixup )[] = {
    { "ctype"       , NULL, -1, -1 },
    { "cnumber"     , NULL, -1, -1 },

    { NULL          , NULL, -1, -1 }
};

DLVARFIXUP __bgdexport( mod_screen, globals_fixup )[] = {
    { "scroll"      , NULL, -1, -1 },

    { NULL          , NULL, -1, -1 }
};
#endif

DLSYSFUNCS  __bgdexport( mod_screen, exported_functions )[] = {
    FUNC( "REGION_DEFINE" , "IIIII"    , TYPE_INT , modscreen_define_region ),
    FUNC( "REGION_OUT"    , "II"       , TYPE_INT , modscreen_out_region    ),

    FUNC( "PUT"           , "IIII"     , TYPE_INT , modscreen_put           ),
    FUNC( "XPUT"          , "IIIIIIII" , TYPE_INT , modscreen_xput          ),
    FUNC( "SCREEN_PUT"    , "II"       , TYPE_INT , modscreen_put_screen    ),
    FUNC( "SCREEN_CLEAR"  , ""         , TYPE_INT , modscreen_clear_screen  ),

    FUNC( "SCREEN_GET"    , ""         , TYPE_INT , modscreen_get_screen    ),

    FUNC( 0               , 0          , 0        , 0                       )

};

char * __bgdexport( mod_screen, module_dependencies )[] = {
    "libgrbase",
    "libvideo",
    "libblit",
    "librender",
    NULL
};

#endif

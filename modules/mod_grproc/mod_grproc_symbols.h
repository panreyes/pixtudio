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

#ifndef __MODGRPROC_SYMBOLS_H
#define __MODGRPROC_SYMBOLS_H

#include <bgddl.h>

#ifndef __PXTB__
DLVARFIXUP __bgdexport( mod_grproc, locals_fixup )[]  = {
    { "_mod_grproc_reserved.type_scan"  , NULL, -1, -1 },
    { "_mod_grproc_reserved.id_scan"    , NULL, -1, -1 },
    { "_mod_grproc_reserved.context"    , NULL, -1, -1 },

    { "id"                              , NULL, -1, -1 },
    { "reserved.process_type"           , NULL, -1, -1 },
    { "reserved.status"                 , NULL, -1, -1 },

    { "ctype"                           , NULL, -1, -1 },
    { "cnumber"                         , NULL, -1, -1 },

    { "x"                               , NULL, -1, -1 },
    { "y"                               , NULL, -1, -1 },

    { "angle"                           , NULL, -1, -1 },
    { "size"                            , NULL, -1, -1 },
    { "size_x"                          , NULL, -1, -1 },
    { "size_y"                          , NULL, -1, -1 },
    { "flags"                           , NULL, -1, -1 },

    { "region"                          , NULL, -1, -1 },
    { "resolution"                      , NULL, -1, -1 },
    { "xgraph"                          , NULL, -1, -1 },

    { NULL                              , NULL, -1, -1 }
};

DLVARFIXUP __bgdexport( mod_grproc, globals_fixup )[] = {
    { "mouse.x"                         , NULL, -1, -1 },
    { "mouse.y"                         , NULL, -1, -1 },
    { "scroll"                          , NULL, -1, -1 },

    { NULL                              , NULL, -1, -1 }
};

extern void __bgdexport( mod_grproc, process_exec_hook )( INSTANCE * r );

extern int grproc_advance( INSTANCE * my, int * params );
extern int grproc_xadvance( INSTANCE * my, int * params );
extern int grproc_get_angle( INSTANCE * my, int * params );
extern int grproc_get_dist( INSTANCE * a, int * params );
extern int grproc_collision( INSTANCE * my, int * params );
extern int grproc_collision_box( INSTANCE * my, int * params );
extern int grproc_collision_circle( INSTANCE * my, int * params );
extern int grproc_get_real_point( INSTANCE * my, int * params );
#endif

char __bgdexport( mod_grproc, locals_def )[] =
    "STRUCT _mod_grproc_reserved\n"
    "int type_scan;\n"
    "int id_scan;\n"
    "int context;\n"
    "END\n";

DLSYSFUNCS  __bgdexport( mod_grproc, exported_functions )[] = {
    FUNC( "ADVANCE"             , "I"   , TYPE_INT  , grproc_advance            ),
    FUNC( "XADVANCE"            , "II"  , TYPE_INT  , grproc_xadvance           ),

    FUNC( "GET_ANGLE"           , "I"   , TYPE_INT  , grproc_get_angle          ),
    FUNC( "GET_DIST"            , "I"   , TYPE_INT  , grproc_get_dist           ),
    FUNC( "COLLISION"           , "I"   , TYPE_INT  , grproc_collision          ),
    FUNC( "COLLISION_BOX"       , "I"   , TYPE_INT  , grproc_collision_box      ),
    FUNC( "COLLISION_CIRCLE"    , "I"   , TYPE_INT  , grproc_collision_circle   ),

    FUNC( "GET_REAL_POINT"      , "IPP" , TYPE_INT  , grproc_get_real_point     ),

    FUNC( 0                     , 0     , 0         , 0                        )
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_grproc, module_dependencies )[] = {
    "libmouse",
    "libgrbase",
    "libvideo",
    "librender",
    "libblit",
    NULL
};

#endif

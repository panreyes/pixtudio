/*
 *  Copyright Â© 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright Â© 2002-2006 Fenix Team (Fenix)
 *  Copyright Â© 1999-2002 JosÃ© Luis CebriÃ¡n PagÃ¼e (Fenix)
 *
 *  This file is part of Bennu - Game Development
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

#ifdef __BGDC__
char __bgdexport( mod_grproc, locals_def )[] =
    "STRUCT _mod_grproc_reserved\n"
    "int type_scan;\n"
    "int id_scan;\n"
    "int context;\n"
    "END\n";

DLSYSFUNCS  __bgdexport( mod_grproc, functions_exports )[] =
{
    { "ADVANCE"             , "I"   , TYPE_INT  , 0 },
    { "XADVANCE"            , "II"  , TYPE_INT  , 0 },

    { "GET_ANGLE"           , "I"   , TYPE_INT  , 0 },
    { "GET_DIST"            , "I"   , TYPE_INT  , 0 },
    { "COLLISION"           , "I"   , TYPE_INT  , 0 },
    { "COLLISION_BOX"       , "I"   , TYPE_INT  , 0 },
    { "COLLISION_CIRCLE"    , "I"   , TYPE_INT  , 0 },

    { "GET_REAL_POINT"      , "IPP" , TYPE_INT  , 0 },

    { 0                     , 0     , 0         , 0 }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_grproc, modules_dependency )[] =
{
    "libmouse",
    "libgrbase",
    "libvideo",
    "librender",
    "libblit",
    NULL
};
#else
extern char __bgdexport( mod_grproc, locals_def )[];
extern DLVARFIXUP __bgdexport( mod_grproc, locals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_grproc, globals_fixup )[];
extern void __bgdexport( mod_grproc, process_exec_hook )( INSTANCE * r );
extern DLSYSFUNCS  __bgdexport( mod_grproc, functions_exports )[];
extern char * __bgdexport( mod_grproc, modules_dependency )[];
#endif

#endif

/*
 *  Copyright Â© 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright Â© 2002-2006 Fenix Team (Fenix)
 *  Copyright Â© 1999-2002 JosÃ© Luis CebriÃ¡n PagÃ¼e (Fenix)
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

#ifndef __MODDIR_SYMBOLS_H
#define __MODDIR_SYMBOLS_H

#include <bgddl.h>

#ifndef __PXTB__
extern int moddir_cd( INSTANCE * my, int * params );
extern int moddir_chdir( INSTANCE * my, int * params );
extern int moddir_mkdir( INSTANCE * my, int * params );
extern int moddir_rmdir( INSTANCE * my, int * params );
extern int moddir_glob( INSTANCE * my, int * params );
extern int moddir_rm( INSTANCE * my, int * params );
extern int moddir_open( INSTANCE * my, int * params );
extern int moddir_close( INSTANCE * my, int * params );
extern int moddir_read( INSTANCE * my, int * params );
extern int moddir_get_basepath( INSTANCE * my, int * params );
extern int moddir_get_prefpath( INSTANCE * my, int * params );

DLVARFIXUP __bgdexport( mod_dir, globals_fixup)[] = {
    /* varname, pointer (NULL), size, # elements */
    { "fileinfo.path" , NULL, -1, -1 },
    { "fileinfo.name" , NULL, -1, -1 },
    { "fileinfo.directory" , NULL, -1, -1 },
    { "fileinfo.hidden" , NULL, -1, -1 },
    { "fileinfo.readonly" , NULL, -1, -1 },
    { "fileinfo.size" , NULL, -1, -1 },
    { "fileinfo.created" , NULL, -1, -1 },
    { "fileinfo.modified" , NULL, -1, -1 },
    { "fileinfo.accessed" , NULL, -1, -1 },
    { "fileinfo.statechg" , NULL, -1, -1 },
    { NULL, NULL, -1, -1 }
};
#endif

char __bgdexport( mod_dir, globals_def )[] =
    "STRUCT fileinfo\n"
    "    STRING path;\n"
    "    STRING name;\n"
    "    directory;\n"
    "    hidden;\n"
    "    readonly;\n"
    "    size;\n"
    "    STRING created;\n"
    "    STRING modified;\n"
    "    STRING accessed;\n"
    "    STRING statechg;\n"
    "END\n";

DLSYSFUNCS __bgdexport( mod_dir, functions_exports)[] = {
    FUNC( "CD"      , ""  , TYPE_STRING , moddir_cd     ),
    FUNC( "CD"      , "S" , TYPE_STRING , moddir_chdir  ),
    FUNC( "CHDIR"   , "S" , TYPE_INT    , moddir_chdir  ),
    FUNC( "MKDIR"   , "S" , TYPE_INT    , moddir_mkdir  ),
    FUNC( "RMDIR"   , "S" , TYPE_INT    , moddir_rmdir  ),
    FUNC( "GLOB"    , "S" , TYPE_STRING , moddir_glob   ),
    FUNC( "CD"      , "S" , TYPE_STRING , moddir_chdir  ),
    FUNC( "RM"      , "S" , TYPE_INT    , moddir_rm     ),

    FUNC( "DIROPEN" , "S" , TYPE_INT    , moddir_open   ),
    FUNC( "DIRCLOSE", "I" , TYPE_INT    , moddir_close  ),
    FUNC( "DIRREAD" , "I" , TYPE_STRING , moddir_read   ),

    FUNC( "GET_BASE_PATH", ""   , TYPE_STRING , moddir_get_basepath ),
    FUNC( "GET_PREF_PATH", "SS" , TYPE_STRING , moddir_get_prefpath ),

    FUNC( 0         , 0   , 0           , 0 )
};

#endif

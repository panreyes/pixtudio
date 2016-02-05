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

#ifndef __MODPATH_SYMBOLS_H
#define __MODPATH_SYMBOLS_H

#include <pxtdl.h>

#define PF_NODIAG       1
#define PF_REVERSE      2

#ifndef __PXTB__
extern int modpathfind_path_find( INSTANCE * my, int * params );
extern int modpathfind_path_getxy( INSTANCE * my, int * params );
extern int modpathfind_path_wall( INSTANCE * my, int * params );
#endif

DLCONSTANT __pxtexport( mod_path, constants_def )[] = {
    { "PF_NODIAG"   , TYPE_INT, PF_NODIAG   },
    { "PF_REVERSE"  , TYPE_INT, PF_REVERSE  },
    { NULL          , 0       , 0           }
} ;

DLSYSFUNCS __pxtexport( mod_path, exported_functions )[] = {
    FUNC( "PATH_FIND"   , "IIIIIII", TYPE_INT   , modpathfind_path_find  ),
    FUNC( "PATH_GETXY"  , "PP"     , TYPE_INT   , modpathfind_path_getxy ),
    FUNC( "PATH_WALL"   , "I"      , TYPE_INT   , modpathfind_path_wall  ),
    FUNC( 0             , 0        , 0          , 0                      )
};

char * __pxtexport( mod_path, module_dependencies )[] =
{
    "libgrbase",
    NULL
};

#endif

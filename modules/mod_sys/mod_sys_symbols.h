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

#ifndef __MODSYS_SYMBOLS_H
#define __MODSYS_SYMBOLS_H

#include "bgddl.h"
#include "mod_sys.h"

#ifndef __PXTB__
extern int modsys_getenv( INSTANCE * my, int * params );
extern int modsys_exec( INSTANCE * my, int * params );
#endif

DLCONSTANT __bgdexport( mod_sys, constants_def )[] = {
    { "_P_WAIT"     , TYPE_DWORD,  _P_WAIT   },
    { "_P_NOWAIT"   , TYPE_DWORD,  _P_NOWAIT },
    { NULL          , 0         ,  0         }
} ;

DLSYSFUNCS __bgdexport( mod_sys, exported_functions )[] = {
    FUNC( "GETENV"  , "S"    , TYPE_STRING, modsys_getenv ),
    FUNC( "EXEC"    , "ISIP" , TYPE_INT   , modsys_exec   ),
    FUNC( 0         , 0      , 0          , 0             )
};

#endif

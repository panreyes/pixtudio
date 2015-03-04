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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgddl.h"
#include "xstrings.h"

#include <SDL_log.h>

/* ---------------------------------------------------------------------- */

static int modsay_say( INSTANCE * my, int * params )
{
    /* Show debugging info also in stdout */
    SDL_Log( "%s\n", string_get( params[0] ) );
    fflush( stdout );
    string_discard( params[0] ) ;
    return 1 ;
}

/* ---------------------------------------------------------------------- */

static int modsay_say_fast( INSTANCE * my, int * params )
{
    /* Show debugging info also in stdout */
    SDL_Log( "%s\n", string_get( params[0] ) );
    string_discard( params[0] ) ;
    return 1 ;
}

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_say, functions_exports )[] =
{
    { "SAY"     , "S", TYPE_UNDEFINED, modsay_say     },
    { "SAY_FAST", "S", TYPE_UNDEFINED, modsay_say_fast},
    { 0         , 0  , 0             , 0              }
};

/* ----------------------------------------------------------------- */

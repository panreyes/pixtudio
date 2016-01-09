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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bgddl.h"

#include <SDL.h>

#include "dlvaracc.h"

#ifndef __MONOLITHIC__
#include "mod_timers_symbols.h"
#else
extern DLVARFIXUP __bgdexport( mod_timers, globals_fixup )[];
#endif

/* ----------------------------------------------------------------- */

enum {
    TIMER = 0
};

/* ----------------------------------------------------------------- */
/*
 *  FUNCTION : _advance_timers
 *
 *  Update the value of all global timers
 *
 *  PARAMS :
 *      None
 *
 *  RETURN VALUE :
 *      None
 */

void _advance_timers( void ) {
    int * timer, i ;
    int curr_ticktimer = SDL_GetTicks() ;
    static int initial_ticktimer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ;
    static int ltimer[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1} ; // -1 to force initial_ticktimer update

    /* TODO: Here add checking for console_mode, don't advance in this mode */
    timer = ( int * ) ( &GLODWORD( mod_timers, TIMER ) );
    for ( i = 0 ; i < 10 ; i++ )
    {
        if ( timer[i] != ltimer[i] ) initial_ticktimer[i] = curr_ticktimer - ( timer[i] * 10 ) ;
        ltimer[i] = timer[i] = ( curr_ticktimer - initial_ticktimer[i] ) / 10 ;
    }
}


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

#include "xstrings.h"
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include "bgload.h"

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* - bgload functions -------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/**
 * PREP
 * Helper function preparing params
 **/

static bgdata *prep( int *params ) {
    bgdata *t = ( bgdata* )malloc( sizeof( bgdata ) );
    t->file = strdup(( char * )string_get( params[0] ));
    t->id = ( int* )params[1];
    *( t->id ) = -2 ; // WAIT STATUS
    string_discard( params[0] );
    return t;
}

/* --------------------------------------------------------------------------- */
/**
 * bgDoLoad
 * Helper function executed in the new thread
 **/

int bgDoLoad( void *d ) {
    bgdata *t = ( bgdata* )d;
    *( t->id ) = ( *t->fn )( t->file );
    free( t->file );
    free( t );
    return 0;
}

/* --------------------------------------------------------------------------- */

int bgload( int ( *fn )(), int * params ) {
    bgdata *t = prep( params );
    t->fn = fn;

    SDL_CreateThread( bgDoLoad, "PixTudio BG loading thread", (void *)t );
    return 0 ;
}

/* --------------------------------------------------------------------------- */

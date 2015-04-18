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

/* --------------------------------------------------------------------------- */

#include <SDL.h>

#include <stdlib.h>

#include "bgdrtm.h"

#include "libgrbase.h"
#include "libvideo.h"
#include "librender.h"

#include "bgddl.h"
#include "dlvaracc.h"

/* --------------------------------------------------------------------------- */

enum {
    GRAPH_MODE = 0
};

/* --------------------------------------------------------------------------- */

DLVARFIXUP __bgdexport( mod_video, globals_fixup )[] =
{
    /* Nombre de variable global, puntero al dato, tamaño del elemento, cantidad de elementos */
    { "graph_mode" , NULL, -1, -1 },
    { NULL , NULL, -1, -1 }
};

/* --------------------------------------------------------------------------- */

/* Funciones de inicialización y carga */

static int modvideo_set_mode( INSTANCE * my, int * params )
{
    return gr_set_mode( params[0] / 10000, params[0] % 10000, 0 ) ;
}

/* --------------------------------------------------------------------------- */

static int modvideo_set_mode_2( INSTANCE * my, int * params )
{
    return gr_set_mode( params[0], params[1], 0 ) ;
}

/* --------------------------------------------------------------------------- */

static int modvideo_set_mode_3( INSTANCE * my, int * params )
{
    GLODWORD( mod_video, GRAPH_MODE ) = (( GLODWORD( mod_video, GRAPH_MODE ) & 0xFF00 ) | params[2] );
    return gr_set_mode( params[0], params[1], 0 ) ;
}

/* --------------------------------------------------------------------------- */

static int modvideo_set_mode_4( INSTANCE * my, int * params )
{
    GLODWORD( mod_video, GRAPH_MODE ) = ( params[2] | params[3] );
    return gr_set_mode( params[0], params[1], 0 ) ;
}

/* --------------------------------------------------------------------------- */

static int modvideo_set_fps( INSTANCE * my, int * params )
{
    gr_set_fps( params[0], params[1] ) ;
    return params[0];
}

/* --------------------------------------------------------------------------- */
/*
Return a pointer to an array of available screen dimensions for the given format and video flags,
sorted largest to smallest.

Returns NULL if there are no dimensions available for a particular format,
or -1 if any dimension is okay for the given format.
*/

static int modvideo_list_modes( INSTANCE * my, int * params )
{
#warning modvideo_list_modes is a stub implementation (See https://wiki.libsdl.org/SDL_GetDisplayMode)
    return -1;
}

/* --------------------------------------------------------------------------- */

/*
   returns 0 if the requested mode is not supported under any bit depth,
   or returns the bits-per-pixel of the closest available
   mode with the given width, height and requested flags

   params:
        height,width,depth,flags

*/

static int modvideo_mode_is_ok( INSTANCE * my, int * params )
{
#warning modvideo_mode_is_ok is a stub implementation
    return 0;
}

/* --------------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_video, functions_exports )[] =
{

    /* Video */
    { "SET_MODE"        , "I"     , TYPE_INT        , modvideo_set_mode         },
    { "SET_MODE"        , "II"    , TYPE_INT        , modvideo_set_mode_2       },
    { "SET_MODE"        , "III"   , TYPE_INT        , modvideo_set_mode_3       },
    { "SET_MODE"        , "IIII"  , TYPE_INT        , modvideo_set_mode_4       },
    { "SET_FPS"         , "II"    , TYPE_INT        , modvideo_set_fps          },

    { "GET_MODES"       , "II"    , TYPE_POINTER    , modvideo_list_modes       },
    { "MODE_IS_OK"      , "IIII"  , TYPE_INT        , modvideo_mode_is_ok       },

    { 0                 , 0       , 0               , 0                         }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_video, modules_dependency )[] =
{
    "libgrbase",
    "libvideo",
    "librender",
    NULL
};

/* --------------------------------------------------------------------------- */

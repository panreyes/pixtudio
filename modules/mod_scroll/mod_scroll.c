/*
 *  Copyright (C) 2014 Joseba García Echebarria <joseba.gar@gmail.com>
 *  Copyright (C) 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright (C) 2002-2006 Fenix Team (Fenix)
 *  Copyright (C) 1999-2002 José Luis Cebrián Pagüe (Fenix)
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

/* --------------------------------------------------------------------------- */

#include "bgddl.h"
#include "libvideo.h"
#include "libscroll.h"

/* --------------------------------------------------------------------------- */

static int mod_scroll_start( INSTANCE * my, int * params )
{
    scroll_start( params[0], params[1], params[2], params[3], params[4], params[5], 0, 0 ) ;
    return 1 ;
}

static int mod_scroll_start2( INSTANCE * my, int * params )
{
    scroll_start( params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7] ) ;
    return 1 ;
}

static int mod_scroll_stop( INSTANCE * my, int * params )
{
    scroll_stop( params[0] ) ;
    return 1 ;
}

static int mod_scroll_move( INSTANCE * my, int * params )
{
    scroll_update (params[0]) ;
    return 1 ;
}

/* ---------------------------------------------------------------------- */

DLSYSFUNCS __bgdexport( mod_scroll, functions_exports )[] =
{
    { "SCROLL_START"    , "IIIIIIII", TYPE_INT   , mod_scroll_start2  },
    { "SCROLL_START"    , "IIIIII"  , TYPE_INT   , mod_scroll_start   },
    { "SCROLL_STOP"     , "I"       , TYPE_INT   , mod_scroll_stop    },
    { "SCROLL_MOVE"     , "I"       , TYPE_INT   , mod_scroll_move    },

    { "START_SCROLL"    , "IIIIIIII", TYPE_INT   , mod_scroll_start2  },
    { "START_SCROLL"    , "IIIIII"  , TYPE_INT   , mod_scroll_start   },
    { "STOP_SCROLL"     , "I"       , TYPE_INT   , mod_scroll_stop    },
    { "MOVE_SCROLL"     , "I"       , TYPE_INT   , mod_scroll_move    },

    { 0                 , 0         , 0          , 0                  }
};

/* --------------------------------------------------------------------------- */

char * __bgdexport( mod_scroll, modules_dependency )[] =
{
    "libscroll",
    0
};

/* --------------------------------------------------------------------------- */

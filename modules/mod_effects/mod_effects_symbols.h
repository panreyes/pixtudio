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

#ifndef __MODEFFECTS_SYMBOLS_H
#define __MODEFFECTS_SYMBOLS_H

#include "mod_effects.h"
#include <pxtdl.h>

#ifndef __PXTB__
extern int modeffects_grayscale( INSTANCE *my, int *params );
extern int modeffects_rgbscale( INSTANCE *my, int *params );
extern int modeffects_blur( INSTANCE *my, int *params );
extern int modeffects_filter( INSTANCE *my, int *params );
#endif

DLCONSTANT __pxtexport( mod_effects, constants_def )[] = {
    { "BLUR_NORMAL" , TYPE_INT, BLUR_NORMAL     },
    { "BLUR_3x3"    , TYPE_INT, BLUR_3x3        },
    { "BLUR_5x5"    , TYPE_INT, BLUR_5x5        },
    { "BLUR_5x5_MAP", TYPE_INT, BLUR_5x5_MAP    },
    { "GSCALE_RGB"  , TYPE_INT, GSCALE_RGB      },
    { "GSCALE_R"    , TYPE_INT, GSCALE_R        },
    { "GSCALE_G"    , TYPE_INT, GSCALE_G        },
    { "GSCALE_B"    , TYPE_INT, GSCALE_B        },
    { "GSCALE_RG"   , TYPE_INT, GSCALE_RG       },
    { "GSCALE_RB"   , TYPE_INT, GSCALE_RB       },
    { "GSCALE_GB"   , TYPE_INT, GSCALE_GB       },
    { "GSCALE_OFF"  , TYPE_INT, GSCALE_OFF      },

    { NULL          , 0       , 0               }
} ;

DLSYSFUNCS  __pxtexport( mod_effects, exported_functions )[] = {
    FUNC( "GRAYSCALE"   , "IIB"   , TYPE_INT    , modeffects_grayscale ),
    FUNC( "RGBSCALE"    , "IIFFF" , TYPE_INT    , modeffects_rgbscale  ),
    FUNC( "BLUR"        , "IIB"   , TYPE_INT    , modeffects_blur      ),
    FUNC( "FILTER"      , "IIP"   , TYPE_INT    , modeffects_filter    ),
    FUNC( NULL          , NULL    , 0           , NULL                 )
};

char * __pxtexport( mod_effects, module_dependencies )[] = {
    "libgrbase",
    NULL
};

#endif

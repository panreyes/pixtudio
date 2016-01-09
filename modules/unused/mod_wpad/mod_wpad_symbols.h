/*
 *  Copyright (C) 2011-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
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

#ifndef __MODWPAD_SYMBOLS_H
#define __MODWPAD_SYMBOLS_H

#include <bgddl.h>
#include <instance_st.h>
#include "mod_wpad.h"

#ifdef __PXTB__
DLSYSFUNCS  __bgdexport( mod_wpad, exported_functions )[] =
{
    { "WPAD_IS_READY"          , "I" , TYPE_INT      , 0 },
    { "WPAD_INFO"              , "II", TYPE_INT      , 0 },
    { "WPAD_INFO_NUNCHUK"      , "II", TYPE_INT      , 0 },
    { "WPAD_INFO_CLASSIC"      , "II", TYPE_INT      , 0 },
    { "WPAD_INFO_GUITAR"       , "II", TYPE_INT      , 0 },
    { "WPAD_INFO_BB"           , "II", TYPE_INT      , 0 },
    { "WPAD_RUMBLE"            , "II", TYPE_INT      , 0 },
    { 0                        , 0   , 0             , 0 }
};
#else
extern DLSYSFUNCS  __bgdexport( mod_wpad, exported_functions )[];
#endif

#ifndef __PXTB__
/* Function declaration */
extern int modwpad_is_ready( INSTANCE * my, int * params );
extern int modwpad_info( INSTANCE * my, int * params );
extern int modwpad_info_nunchuk( INSTANCE * my, int * params );
extern int modwpad_info_classic( INSTANCE * my, int * params );
extern int modwpad_info_guitar( INSTANCE * my, int * params );
extern int modwpad_info_bb( INSTANCE * my, int * params );
extern int modwpad_rumble( INSTANCE * my, int * params);
#endif


DLCONSTANT __bgdexport( mod_wpad, constants_def )[] =
{
    { "WPAD_BATT",       TYPE_INT,   WPAD_BATT         },
    { "WPAD_X",          TYPE_INT,   WPAD_X            },
    { "WPAD_Y",          TYPE_INT,   WPAD_Y            },
    { "WPAD_Z",          TYPE_INT,   WPAD_Z            },
    { "WPAD_ANGLE",      TYPE_INT,   WPAD_ANGLE        },
    { "WPAD_PITCH",      TYPE_INT,   WPAD_PITCH        },
    { "WPAD_ROLL",       TYPE_INT,   WPAD_ROLL         },
    { "WPAD_ACCELX",     TYPE_INT,   WPAD_ACCELX       },
    { "WPAD_ACCELY",     TYPE_INT,   WPAD_ACCELY       },
    { "WPAD_ACCELZ",     TYPE_INT,   WPAD_ACCELZ       },
    { "WPAD_IS_BB",      TYPE_INT,   WPAD_IS_BB        }, /* Balance Board-only constants */
    { "WPAD_WTL",        TYPE_INT,   WPAD_WTL          },
    { "WPAD_WTR",        TYPE_INT,   WPAD_WTR          },
    { "WPAD_WBL",        TYPE_INT,   WPAD_WBL          },
    { "WPAD_WBR",        TYPE_INT,   WPAD_WBR          },
    { "WPAD_GX",         TYPE_INT,   WPAD_WTL          }, /* Gravity constants */
    { "WPAD_GY",         TYPE_INT,   WPAD_WTR          },
    { "WPAD_GZ",         TYPE_INT,   WPAD_WBL          },
    { "WPAD_HAS_NUNCHUK",TYPE_INT,   WPAD_HAS_NUNCHUK  }, /* Nunchuk */
    { "WPAD_HAS_CLASSIC",TYPE_INT,   WPAD_HAS_CLASSIC  }, /* Classic controller */
    { "WPAD_HAS_GUITAR" ,TYPE_INT,   WPAD_HAS_GUITAR   }, /* Guitar */

    { NULL              , 0       , 0           }
} ;

/* ----------------------------------------------------------------- */

char * __bgdexport( mod_wpad, module_dependencies )[] =
{
    "mod_joy",
    NULL
};

#endif

/*
 *  Copyright (C) Joseba García Etxebarria <joseba.gar@gmail.com>
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

#ifndef __MODSENSOR_SYMBOLS_H
#define __MODSENSOR_SYMBOLS_H

#include <pxtdl.h>

#ifndef __PXTB__
extern int modsensor_number( INSTANCE * my, int * params );
extern int modsensor_open( INSTANCE * my, int * params );
extern void modsensor_close( INSTANCE * my, int * params );
extern int modsensor_name ( INSTANCE * my, int * params );
extern int modsensor_numaxes( INSTANCE * my, int * params );
extern float modsensor_getaxis( INSTANCE * my, int * params );
extern int modsensor_type( INSTANCE * my, int * params );
extern void modsensor_log( INSTANCE * my, int * params );

extern void  __pxtexport( mod_sensor, module_initialize )();
extern void  __pxtexport( mod_sensor, module_finalize )();
#endif

DLCONSTANT  __pxtexport( mod_sensor, constants_def )[] = {
    { "SENSOR_UNKNOWN"              , TYPE_DWORD    , 0               },
    { "SENSOR_ACCEL"                , TYPE_DWORD    , 1               },
    { "SENSOR_MAGNET"               , TYPE_DWORD    , 2               },
    { "SENSOR_ORIENTATION"          , TYPE_DWORD    , 3               },
    { "SENSOR_GYRO"                 , TYPE_DWORD    , 4               },
    { "SENSOR_LIGHT"                , TYPE_DWORD    , 5               },
    { "SENSOR_PRESSURE"             , TYPE_DWORD    , 6               },
    { "SENSOR_TEMPERATURE"          , TYPE_DWORD    , 7               },
    { "SENSOR_PROXIMITY"            , TYPE_DWORD    , 8               },
    { "SENSOR_GRAVITY"              , TYPE_DWORD    , 9               },
    { "SENSOR_LACCEL"               , TYPE_DWORD    , 10              },
    { "SENSOR_ROTVECTOR"            , TYPE_DWORD    , 11              },
    { "SENSOR_RHUMIDITY"            , TYPE_DWORD    , 12              },
};

DLSYSFUNCS  __pxtexport( mod_sensor, exported_functions )[] = {
    FUNC( "SENSOR_NUMBER",  "",    TYPE_INT,       modsensor_number     ),
    FUNC( "SENSOR_OPEN",    "I",   TYPE_INT,       modsensor_open       ),
    FUNC( "SENSOR_CLOSE",   "I",   TYPE_UNDEFINED, modsensor_close      ),
    FUNC( "SENSOR_NAME",    "I",   TYPE_STRING,    modsensor_name       ),
    FUNC( "SENSOR_NUMAXES", "I",   TYPE_INT,       modsensor_numaxes    ),
    FUNC( "SENSOR_GETAXIS", "II",  TYPE_FLOAT,     modsensor_getaxis    ),
    FUNC( "SENSOR_TYPE",    "I",   TYPE_INT,       modsensor_type       ),
    FUNC( "SENSOR_LOG",     "",    TYPE_UNDEFINED, modsensor_log        ),
    FUNC( 0         , 0  , 0             , 0                            )
};

#endif

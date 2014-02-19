/*
 *  Copyright Â© 2013 Joseba GarcÃ­a Etxebarria <joseba.gar@gmail.com>
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

#ifndef __MODSENSOR_SYMBOLS_H
#define __MODSENSOR_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__

DLCONSTANT  __bgdexport( mod_sensor, constants_def )[] = {
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

DLSYSFUNCS  __bgdexport( mod_sensor, functions_exports )[] =
{
    { "SENSOR_NUMBER",  "",    TYPE_INT,       0 },
    { "SENSOR_OPEN",    "I",   TYPE_INT,       0 },
    { "SENSOR_CLOSE",   "I",   TYPE_UNDEFINED, 0 },
    { "SENSOR_NAME",    "I",   TYPE_STRING,    0 },
    { "SENSOR_NUMAXES", "I",   TYPE_INT,       0 },
    { "SENSOR_GETAXIS", "II",  TYPE_FLOAT,     0 },
    { "SENSOR_TYPE",    "I",   TYPE_INT,       0 },
    { "SENSOR_LOG",     "",    TYPE_UNDEFINED, 0 },
    { 0           ,     0,     0             , 0 }
};
#else
extern DLCONSTANT  __bgdexport( mod_sensor, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_sensor, functions_exports )[];
extern void __bgdexport( mod_sensor, module_initialize )();
extern void __bgdexport( mod_sensor, module_finalize )();
#endif

#endif

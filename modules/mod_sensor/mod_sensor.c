/*
 *  Copyright © 2013 Joseba García Etxebarria <joseba.gar@gmail.com>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FAKE
#include <SDL.h>
#endif

#include "bgddl.h"
#include "xstrings.h"

#ifndef MAX_SENSORS
#   define MAX_SENSORS 256
#endif

#ifndef FAKE
#   if ! SDL_VERSION_ATLEAST(2,0,0)
#       error This module needs SDL 2.0, refusing to compile
#   endif

static SDL_Sensor *sensor[MAX_SENSORS];
#endif

/* ---------------------------------------------------------------------- */

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
    { NULL                          , 0             , 0               }
};

/* ---------------------------------------------------------------------- */

// Open given sensor if not already open, return index otherwise
int sensor_open(int i) {
#ifndef FAKE
    if (i > SDL_NumSensors() || i < 0) {
        return -1;
    }

    if(sensor[i]) {
        return i;
    }

    sensor[i] = SDL_SensorOpen(i);

    if (sensor[i]) {
        return i;
    }
#endif

    return -1;
}

void sensor_close(int i) {
#ifndef FAKE
    if (i >= SDL_NumSensors() || i < 0 || !sensor[i]) {
        return;
    }

    SDL_SensorClose(sensor[i]);
    sensor[i] = NULL;
#endif
}

// Return the number of axes in given sensor
// Given sensor must be already open
int sensor_axes(int i) {
    int n=0;

#ifndef FAKE
    if (i >= SDL_NumSensors() || i < 0 || !sensor[i]) {
        return  -1;
    }

    n = SDL_SensorNumAxes(sensor[i]);
#endif

    return n;
}

/* ---------------------------------------------------------------------- */

// Get the total number of sensors attached to the system
// This is considered constant during the whole run of the program, but
// theoretically might not be so
int modsensor_number( INSTANCE * my, int * params ) {
    int n=0;
#ifndef FAKE
    n = SDL_NumSensors();
#endif
    return n ;
}

// Open a sensor. The user needn't call this manually, but may choose to do so
int modsensor_open( INSTANCE * my, int * params ) {
    int n=0;

#ifndef FAKE
    n = sensor_open(params[0]);
#endif
    return n ;
}

// Close a sensor. The user needn't do this manually, but may choose to do so
// nonetheless to free system resources since having an open sensor
void modsensor_close( INSTANCE * my, int * params ) {
#ifndef FAKE
    sensor_close(params[0]);
#endif
}

// Return the name for the given sensor index
// The sensor needn't be open
int modsensor_name ( INSTANCE * my, int * params ) {
    int result;

#ifndef FAKE
    result = string_new(SDL_SensorNameForIndex(params[0]));
#else
    result = string_new("Error");
#endif

    string_use(result);

    return result;
}

// Get the total number of axes in a sensor
int modsensor_numaxes( INSTANCE * my, int * params ) {
    int n=0;

#ifndef FAKE
    if (sensor_open(params[0]) != -1) {
        n = sensor_axes(params[0]);
    }
#endif

    return n;
}

// Get the type for a sensor
int modsensor_type( INSTANCE * my, int * params ) {
    int type=0;

#ifndef FAKE
    if (sensor_open(params[0]) != -1) {
        type = (int)SDL_SensorType(sensor[params[0]]);
    }
#endif

    return type;
}

// Get the value for a sensor axis
float modsensor_getaxis( INSTANCE * my, int * params ) {
    float value=0.0;

#ifndef FAKE
    if (sensor_open(params[0]) != -1) {
        value = SDL_SensorGetAxis(sensor[params[0]], params[1]);
    }
#endif

    return value;
}

// Update the sensor data
void modsensor_log( INSTANCE * my, int * params ) {
#ifndef FAKE
    SDL_SensorUpdate();
#endif
}

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */

DLSYSFUNCS  __bgdexport( mod_sensor, functions_exports )[] =
{
    { "SENSOR_NUMBER",  "",    TYPE_INT,       modsensor_number     },
    { "SENSOR_OPEN",    "I",   TYPE_INT,       modsensor_open       },
    { "SENSOR_CLOSE",   "I",   TYPE_UNDEFINED, modsensor_close      },
    { "SENSOR_NAME",    "I",   TYPE_STRING,    modsensor_name       },
    { "SENSOR_NUMAXES", "I",   TYPE_INT,       modsensor_numaxes    },
    { "SENSOR_GETAXIS", "II",  TYPE_FLOAT,     modsensor_getaxis    },
    { "SENSOR_TYPE",    "I",   TYPE_INT,       modsensor_type       },
    { "SENSOR_LOG",     "",    TYPE_UNDEFINED, modsensor_log        },
    { 0         , 0  , 0             , 0                            }
};

/* --------------------------------------------------------------------------- */

void  __bgdexport( mod_sensor, module_initialize )()
{
#ifndef FAKE
    int i;

    if ( !SDL_WasInit( SDL_INIT_SENSOR ) )
    {
        SDL_InitSubSystem( SDL_INIT_SENSOR );
    }

    // Initialize the elements to NULL, just in case
    for(i=0; i<MAX_SENSORS; i++) {
        sensor[i] = NULL;
    }
#endif
}

/* ----------------------------------------------------------------- */

void  __bgdexport( mod_sensor, module_finalize )()
{
#ifndef FAKE
    int i;

    // Close all open sensors
    for(i=0; i<MAX_SENSORS; i++) {
        if(sensor[i]) {
            sensor_close(i);
        }
    }

    if ( SDL_WasInit( SDL_INIT_SENSOR ) ) SDL_QuitSubSystem( SDL_INIT_SENSOR );
#endif
}

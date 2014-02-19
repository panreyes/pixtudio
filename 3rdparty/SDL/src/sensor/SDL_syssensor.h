/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2012 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL_config.h"

/* This is the system specific header for the SDL sensor API */

#include "SDL_sensor.h"
#include "SDL_sensor_c.h"

/* The SDL sensor structure */
struct _SDL_Sensor
{
    int instance_id;                /* Device instance, monotonically increasing from 0 */
    char *name;                     /* Sensor name - system dependent */
    Uint8 type;                     /* Type of sensor */

    int naxes;                      /* Number of axis controls on the sensor */
    float *axes;                   /* Current axis states */
    float resolution;               /* Resolution for this sensor */

    struct sensor_hwdata *hwdata;   /* Driver dependent information */

    int ref_count;                  /* Reference count for multiple opens */

    Uint8 closed;                   /* 1 if this device is no longer valid */
    Uint8 uncentered;               /* 1 if this device needs to have its state reset to 0 */
    struct _SDL_Sensor *next;       /* pointer to next sensor we have allocated */
};

/* Function to scan the system for sensors.
 * sensor 0 should be the system default sensor.
 * This function should return the number of available sensors, or -1
 * on an unrecoverable fatal error.
 */
extern int SDL_SYS_SensorInit(void);

/* Function to return the number of sensor devices plugged in right now */
extern int SDL_SYS_NumSensors();

/* Function to get the device-dependent name of a sensor */
extern const char *SDL_SYS_SensorNameForDeviceIndex(int device_index);

/* Function to get the current instance id of the sensor located at device_index */
extern SDL_SensorID SDL_SYS_SensorGetInstanceIdOfDeviceIndex(int device_index);

/* Function to open a sensor for use.
   The sensor to open is specified by the index field of the sensor.
   This should fill the nbuttons and naxes fields of the sensor structure.
   It returns 0, or -1 if there is an error.
 */
extern int SDL_SYS_SensorOpen(SDL_Sensor * sensor, int device_index);

/* Function to query if the sensor is currently attached
 *   It returns SDL_TRUE if attached, SDL_FALSE otherwise.
 */
extern SDL_bool SDL_SYS_SensorAttached(SDL_Sensor * sensor);

/* Function to update the state of a sensor - called as a device poll.
 * This function shouldn't update the sensor structure directly,
 * but instead should call SDL_PrivateSensor*() to deliver events
 * and update sensor device state.
 */
extern void SDL_SYS_SensorUpdate(SDL_Sensor * sensor);

/* Function to close a sensor after use */
extern void SDL_SYS_SensorClose(SDL_Sensor * sensor);

/* Function to perform any system-specific sensor related cleanup */
extern void SDL_SYS_SensorQuit(void);

/* vi: set ts=4 sw=4 expandtab: */

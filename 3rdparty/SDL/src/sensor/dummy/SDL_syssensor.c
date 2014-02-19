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

#if defined(SDL_SENSOR_DUMMY) || defined(SDL_SENSOR_DISABLED)

/* This is the system specific header for the SDL sensor API */

#include "SDL_sensor.h"
#include "../SDL_syssensor.h"
#include "../SDL_sensor_c.h"

/* Function to scan the system for sensors.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
int
SDL_SYS_SensorInit(void)
{
    return (0);
}

int SDL_SYS_NumSensors()
{
    return 0;
}

/* Function to get the device-dependent name of a sensor */
const char *
SDL_SYS_SensorNameForDeviceIndex(int device_index)
{
    SDL_SetError("Logic error: No sensors available");
    return (NULL);
}

/* Function to perform the mapping from device index to the instance id for this index */
SDL_SensorID SDL_SYS_SensorGetInstanceIdOfDeviceIndex(int device_index)
{
    return device_index;
}

/* Function to determine is this sensor is attached to the system right now */
SDL_bool SDL_SYS_SensorAttached(SDL_Sensor *sensor)
{
    return SDL_FALSE;
}

/* Function to open a sensor for use.
   The sensor to open is specified by the index field of the sensor.
   This should fill the naxes fields of the sensor structure.
   It returns 0, or -1 if there is an error.
 */
int
SDL_SYS_SensorOpen(SDL_Sensor *sensor, int device_index)
{
    SDL_SetError("Logic error: No sensors available");
    return (-1);
}

/* Function to update the state of a sensor - called as a device poll.
 * This function shouldn't update the sensor structure directly,
 * but instead should call SDL_PrivateSensor*() to deliver events
 * and update sensor device state.
 */
void
SDL_SYS_SensorUpdate(SDL_Sensor* sensor)
{
    return;
}

/* Function to close a sensor after use */
void
SDL_SYS_SensorClose(SDL_Sensor * sensor)
{
    return;
}

/* Function to perform any system-specific sensor related cleanup */
void
SDL_SYS_SensorQuit(void)
{
    return;
}

#endif /* SDL_SENSOR_DUMMY || SDL_SENSOR_DISABLED */

/* vi: set ts=4 sw=4 expandtab: */

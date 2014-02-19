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

#ifdef SDL_SENSOR_ANDROID

/* This is the system specific header for the SDL sensor API */
#include <stdio.h>              /* For the definition of NULL */
#include <android/sensor.h>

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_sensor.h"
#include "SDL_androidsensor.h"
#include "../SDL_syssensor.h"
#include "../SDL_sensor_c.h"
#include "../../core/android/SDL_android.h"

static ASensorManager* mSensorManager;
static ASensorEventQueue* eventqueue;
static ALooper* looper;
static int open_sensors=0;

/* Function to scan the system for sensors.
 * Sensor 0 should be the system default sensor.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
int
SDL_SYS_SensorInit(void)
{
    mSensorManager = ASensorManager_getInstance();
    looper = ALooper_forThread();
    if(! looper) {
        looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
        if(! looper) {
            return -1;
        }
    }

    return 0;
}

int SDL_SYS_NumSensors()
{
    return ASensorManager_getSensorList(mSensorManager, NULL);
}

/* Function to get the device-dependent name of a sensor
 * Should be callable even before opening the sensor */
const char *
SDL_SYS_SensorNameForDeviceIndex(int device_index)
{
    ASensorList list;

    if (device_index >= ASensorManager_getSensorList(mSensorManager, &list) || ! list) {
        SDL_SetError("Sensor index higher than available sensor number");
        return NULL;
    }

    return ASensor_getName(list[device_index]);
}

/* Function to perform the mapping from device index to the instance id for this index */
SDL_SensorID SDL_SYS_SensorGetInstanceIdOfDeviceIndex(int device_index)
{
    return device_index;
}

/* Function to open a sensor for use.
   The sensor to open is specified by the index field of the sensor.
   This should fill the naxes fields of the sensor structure.
   It returns 0, or -1 if there is an error.
 */
int
SDL_SYS_SensorOpen(SDL_Sensor *sensor, int device_index)
{
    int type=0;
    ASensorList list;

    if (device_index >= ASensorManager_getSensorList(mSensorManager, &list) || ! list) {
        return -1;
    }

    sensor->hwdata = (struct sensor_hwdata *)
        SDL_malloc(sizeof(*sensor->hwdata));
    if (sensor->hwdata == NULL) {
        SDL_OutOfMemory();
        return -1;
    }

    sensor->hwdata->asensor = list[device_index];

    type = ASensor_getType(list[device_index]);
    switch(type) {
        case 0x00000001:
            sensor->type = SDL_SENSOR_ACCEL;
            sensor->naxes = 3;
            break;
        case 0x00000002:
            sensor->type = SDL_SENSOR_MAGNET;
            sensor->naxes = 3;
            break;
        case 0x00000003:
            sensor->type = SDL_SENSOR_ORIENTATION;
            sensor->naxes = 3;
            break;
        case 0x00000004:
            sensor->type = SDL_SENSOR_GYRO;
            sensor->naxes = 3;
            break;
        case 0x00000005:
            sensor->type = SDL_SENSOR_LIGHT;
            sensor->naxes = 1;
            break;
        case 0x00000006:
            sensor->type = SDL_SENSOR_PRESSURE;
            sensor->naxes = 1;
            break;
        case 0x00000007:
            sensor->type = SDL_SENSOR_TEMPERATURE;
            sensor->naxes = 1;
            break;
        case 0x00000008:
            sensor->type = SDL_SENSOR_PROXIMITY;
            sensor->naxes = 1;
            break;
        case 0x00000009:
            sensor->type = SDL_SENSOR_GRAVITY;
            sensor->naxes = 1;
            break;
        case 0x0000000a:
            sensor->type = SDL_SENSOR_LACCEL;
            sensor->naxes = 3;
            break;
        case 0x0000000b:
            sensor->type = SDL_SENSOR_ROTVECTOR;
            sensor->naxes = 3;
            break;
        case 0x0000000c:
            sensor->type = SDL_SENSOR_RHUMIDITY;
            sensor->naxes = 1;
            break;
        default:
            sensor->type = SDL_SENSOR_UNKNOWN;
            sensor->naxes = 3;  // Just in case
    }
    
    sensor->resolution = ASensor_getResolution(list[device_index]);
    
    sensor->instance_id = device_index;
    
    // If there were no open sensors, open the event queue and associate
    // it to the looper
    if(open_sensors == 0) {
        eventqueue = ASensorManager_createEventQueue(mSensorManager, looper, 3 /* LOOPER_ID_USER */, NULL, NULL);
    }
    open_sensors++;
    
    ASensorEventQueue_enableSensor(eventqueue, list[device_index]);

    return 0;
}
    
/* Function to update the state of a sensor - called as a device poll.
 * This function shouldn't update the sensor structure directly,
 * but instead should call SDL_PrivateSensor*() to deliver events
 * and update sensor device state.
 * There's some useful information on what the Android sensors give you at:
 * http://developer.android.com/reference/android/hardware/SensorEvent.html
 */
void
SDL_SYS_SensorUpdate(SDL_Sensor* sensor)
{
    int events;
    ASensorEvent event;
    struct android_poll_source* source;

    while (ALooper_pollAll(0, NULL, &events, (void**)&source) == 3 /* LOOPER_ID_USER */ ) {
        // If a sensor has data, process it now.
        while (ASensorEventQueue_getEvents(eventqueue,
                                           &event, 1) > 0) {
            switch(event.type) {
                case 0x00000001:
                    SDL_PrivateSensorAxis(sensor, 0, event.acceleration.x);
                    SDL_PrivateSensorAxis(sensor, 1, event.acceleration.y);
                    SDL_PrivateSensorAxis(sensor, 2, event.acceleration.z);
                    break;
                case 0x00000002:
                    SDL_PrivateSensorAxis(sensor, 0, event.magnetic.x);
                    SDL_PrivateSensorAxis(sensor, 1, event.magnetic.y);
                    SDL_PrivateSensorAxis(sensor, 2, event.magnetic.z);
                    break;
                case 0x00000003:
                    SDL_PrivateSensorAxis(sensor, 0, event.vector.azimuth);
                    SDL_PrivateSensorAxis(sensor, 1, event.vector.pitch);
                    SDL_PrivateSensorAxis(sensor, 2, event.vector.roll);
                    break;
                case 0x00000004:
                    SDL_PrivateSensorAxis(sensor, 0, event.vector.x);
                    SDL_PrivateSensorAxis(sensor, 1, event.vector.y);
                    SDL_PrivateSensorAxis(sensor, 2, event.vector.z);
                    break;
                case 0x00000005:
                    SDL_PrivateSensorAxis(sensor, 0, event.light);
                    break;
                case 0x00000006:
                    SDL_PrivateSensorAxis(sensor, 0, event.pressure);
                    break;
                case 0x00000007:
                    SDL_PrivateSensorAxis(sensor, 0, event.temperature);
                    break;
                case 0x00000008:
                    SDL_PrivateSensorAxis(sensor, 0, event.distance);
                    break;
                case 0x00000009:
                    SDL_PrivateSensorAxis(sensor, 0, event.vector.x);
                    SDL_PrivateSensorAxis(sensor, 1, event.vector.y);
                    SDL_PrivateSensorAxis(sensor, 2, event.vector.z);
                    break;
                case 0x0000000a:
                    SDL_PrivateSensorAxis(sensor, 0, event.acceleration.x);
                    SDL_PrivateSensorAxis(sensor, 1, event.acceleration.y);
                    SDL_PrivateSensorAxis(sensor, 2, event.acceleration.z);
                    break;
                case 0x0000000b:
                    SDL_PrivateSensorAxis(sensor, 0, event.vector.x);
                    SDL_PrivateSensorAxis(sensor, 1, event.vector.y);
                    SDL_PrivateSensorAxis(sensor, 2, event.vector.z);
                    break;
                case 0x0000000c:
                    // Is this OK?
                    SDL_PrivateSensorAxis(sensor, 0, event.data[0]);
                    break;
                default:
                    break;
            }
        }
    }
}

/* Function to determine is this sensor is attached to the system right now
 * Right now we're assuming Android sensors are always attached.
 * TODO: Is there any way to know this info in Android?
 */
SDL_bool SDL_SYS_SensorAttached(SDL_Sensor *sensor)
{
    return SDL_TRUE;
}

/* Function to close a sensor after use */
void
SDL_SYS_SensorClose(SDL_Sensor * sensor)
{
    ASensorEventQueue_disableSensor(eventqueue, sensor->hwdata->asensor);
    
    SDL_free(sensor->hwdata);
    open_sensors--;
    
    // Don't read the sensors if no SDL_Sensor is open
    if(! open_sensors) {
        ASensorManager_destroyEventQueue(mSensorManager, eventqueue);
    }
}

/* Function to perform any system-specific sensor related cleanup */
void
SDL_SYS_SensorQuit(void)
{
}

#endif /* SDL_SENSOR_ANDROID */

/* vi: set ts=4 sw=4 expandtab: */

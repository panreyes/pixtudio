/*
 * Copyright (C) 2013-2016 Joseba García Etxebarria. All rights reserved.
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
#include <strings.h>
#include <libvideo.h>
#include <g_video.h>
#include <SDL.h>
#include "pxtrtm.h"
#include "pxtdl.h"
#include "dlvaracc.h"
#include "xstrings.h"
#include "mod_multi.h"

#ifndef __MONOLITHIC__
#include "mod_multi_symbols.h"
#endif

/* --------------------------------------------------------------------------- */

typedef struct {
    SDL_bool active;
    int x;
    int y;
    int pressure;
    SDL_FingerID fingerid;
} multi_pointer;

multi_pointer pointers[MAX_POINTERS];

int numpointers = 0;

// Required for mouse emulation
enum { MOUSEX = 0,
       MOUSEY,
       MOUSELEFT = 9 };

/* Return the position of finger in the pointers array, if it's not there,
return the first unused entry.
If there are none available, return -1 */
int get_sdlfinger_index(SDL_FingerID finger) {
    int n = 0;

    // First, try to see if the given ID matches any active one
    for (n = 0; n < MAX_POINTERS; n++) {
        if (finger == pointers[n].fingerid && pointers[n].active) {
            return n;
        }
    }

    // ID not found, try to find a free spot
    for (n = 0; n < MAX_POINTERS; n++) {
        if (pointers[n].active == SDL_FALSE) {
            return n;
        }
    }

    // Fail
    return -1;
}

int modmulti_finger_calc(int position, int min, int max, double ratio) {
    if (position < min) {
            return 0;
    }
    if (position > max) {
            return (int) ((max - min) / ratio);
    }
    return (int) ((position - min) / ratio);
}

/* Process SDL events looking for multitouch-related ones */
void parse_input_events() {
    int n   = 0;
    float x = 0.0, y = 0.0;
    double width = 0.0, height = 0.0;
    int offset_x, offset_y, max_x, max_y;
    double scale_ratio;
    SDL_Event e;

    int window_width, window_height;
	
    if (window) {
        SDL_GetWindowSize(window, &window_width, &window_height);
    }

    // SDL will give us the touch position relative to the whole window
    // but we might have set a different virtual resolution
    if (screen) {
        width  = screen->w;
        height = screen->h;
        if (window_width > window_height) {
            scale_ratio = (double) window_height / height;
            offset_x = (window_width - (width * scale_ratio)) / 2;
            offset_y = 0;
        } else {
            scale_ratio = (double) window_width / width;
            offset_x = 0;
            offset_y = (window_height - (height * scale_ratio)) / 2;
        }
        max_x = window_width - offset_x;
        max_y = window_height - offset_y;
    } else {
        // This'll avoid division-by-zero below
        PXTRTM_LOGERROR("Unexpected condition getting resolution, refusing to parse events");
        return;
    }

    // Parse the SDL event
    while (SDL_PeepEvents(&e, 1, SDL_GETEVENT, SDL_FINGERDOWN, SDL_FINGERMOTION) > 0) {
        switch (e.type) {
            case SDL_FINGERDOWN:
                // Retrive the the position in the array
                n = get_sdlfinger_index(e.tfinger.fingerId);

                // Quit if fingerId not found or array full
                if (n == -1) {
                    break;
                }

                // Store the amount of fingers onscreen
                numpointers = SDL_GetNumTouchFingers(e.tfinger.touchId);
                // Store the data about this finger's position
                pointers[n].fingerid = e.tfinger.fingerId;
                pointers[n].active   = SDL_TRUE;
                x                    = e.tfinger.x * window_width;
                y                    = e.tfinger.y * window_height;
                pointers[n].pressure = (float)e.tfinger.pressure * 255;

                // Convert the touch location taking scaling/rotations into account
                pointers[n].x = modmulti_finger_calc((int) x, offset_x, max_x, scale_ratio);
                pointers[n].y = modmulti_finger_calc((int) y, offset_y, max_y, scale_ratio);

                // Fake a mouse click, but only for the first pointer and
                // if libmouse has been imported
                /*if (n == 0) {
                    if ( GLOEXISTS( libmouse, MOUSEX ) ) {
                        GLOINT32( libmouse, MOUSEX )    = pointers[n].x;
                        GLOINT32( libmouse, MOUSEY )    = pointers[n].y;
                        GLODWORD( libmouse, MOUSELEFT ) = 1 ;
                    }
                }*/
                break;

            case SDL_FINGERMOTION:
                // Retrive the touch state, the finger id and the position in the array
                n = get_sdlfinger_index(e.tfinger.fingerId);

                // Quit if fingerid not found
                if (n == -1)
                    break;

                // Update the data about this finger's position
                x                    = e.tfinger.x * window_width;
                y                    = e.tfinger.y * window_height;
                pointers[n].pressure = (float)e.tfinger.pressure * 255;

                // Convert the touch location taking scaling/rotations into account
                pointers[n].x = modmulti_finger_calc((int) x, offset_x, max_x, scale_ratio);
                pointers[n].y = modmulti_finger_calc((int) y, offset_y, max_y, scale_ratio);

                // Fake a mouse move, but only if libmouse has been imported
                /*if (n == 0) {
                    if ( GLOEXISTS( libmouse, MOUSEX ) ) {
                        GLOINT32( libmouse, MOUSEX ) = pointers[n].x;
                        GLOINT32( libmouse, MOUSEY ) = pointers[n].y;
                    }
                }*/
                break;

            case SDL_FINGERUP:
                // Retrive the touch state, the finger id and the position in the array
                n = get_sdlfinger_index(e.tfinger.fingerId);

                // Refresh the total number of fingers onscreen
                numpointers = SDL_GetNumTouchFingers(e.tfinger.touchId);

                // Quit if fingerid not found
                if (n == -1)
                    break;

                // Remove the data about this finger's position
                pointers[n].active   = SDL_FALSE;
                pointers[n].pressure = 0.0;

                // Fake a mouse release, but only for the first pointer and
                // if libmouse is imported
                /*if (n == 0) {
                    if ( GLOEXISTS( libmouse, MOUSEX ) ) {
                        GLODWORD( libmouse, MOUSELEFT ) = 0 ;
                    }
                }*/
                break;
        }
    }
}

// Return the total number of active pointers
int modmulti_numpointers(INSTANCE *my, int *params) {
    return numpointers;
}

// Get some info about the given pointer
int modmulti_info(INSTANCE *my, int *params) {
    const char *info = (char *)string_get(params[1]);
    int n            = params[0];

    string_discard(params[1]);

    // Check for failure
    if (n >= MAX_POINTERS || n < 0) {
        return -1;
    }

    // Return the info we were asked for
    if (strncasecmp(info, "X", 1) == 0) {
        return pointers[n].x;
    } else if (strncasecmp(info, "Y", 1) == 0) {
        return pointers[n].y;
    } else if (strncasecmp(info, "PRESSURE", 8) == 0) {
        return pointers[n].pressure;
    } else if (strncasecmp(info, "ACTIVE", 6) == 0) {
        if (pointers[n].active == SDL_TRUE) {
            return 1;
        } else {
            return 0;
        }
    }

    return -1;
}

/* ----------------------------------------------------------------- */

void __pxtexport(mod_multi, module_initialize)() {
    SDL_SetHint("SDL_ANDROID_SEPARATE_MOUSE_AND_TOUCH", "1");
}

/* ----------------------------------------------------------------- */

/*
 SDL_FINGERDOWN      = 0x700,
 SDL_FINGERUP,
 SDL_FINGERMOTION,
 SDL_TOUCHBUTTONDOWN,
 SDL_TOUCHBUTTONUP,

 // Gesture events
SDL_DOLLARGESTURE   = 0x800,
SDL_DOLLARRECORD,
SDL_MULTIGESTURE,
*/

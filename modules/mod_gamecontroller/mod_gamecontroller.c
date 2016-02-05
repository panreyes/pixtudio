/*
 *  Copyright (C) 2015 Joseba García Etxebarria <joseba.gar@gmail.com>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_joystick.h>
#include <SDL_gamecontroller.h>
#include <stretchy_buffer.h>

/* --------------------------------------------------------------------------- */

#include <pxtdl.h>
#include <xstrings.h>

#include "mod_gamecontroller.h"

#ifndef __MONOLITHIC__
#include "mod_gamecontroller_symbols.h"
#endif

/* --------------------------------------------------------------------------- */

static SDL_GameController **open_controllers = NULL;

/* --------------------------------------------------------------------------- */

/*
 *  FUNCTION : find_free_controllerID
 *
 *  Find a free spot in given array.
 *  If no spots are available, increment the size of the given array
 *  and return the index of the last element.
 *
 *  PARAMS:
 *      array to find free spot in
 *
 *  RETURN VALUE:
 *
 *      an integer with the position index, or -1 if an error occurred
 *
 */

static int find_free_controllerID(SDL_GameController **where) {
    int32_t i = 0, len = 0;

    // Try to find an empty spot (the pointer should be NULL there)
    len = sb_count(where);
    for (i = 0; i < len; i++) {
        if (where[i] == NULL) {
            return i;
        }
    }

    // None available => return -1
    return -1;
}

/*
 *  FUNCTION : check_controller_id
 *
 *  Check if the controller is still valid.
 *
 *  PARAMS:
 *      id of the controller, as returned by modgamecontroller_open
 *
 *  RETURN VALUE:
 *
 *      an integer with the 1 for still valid, 0 for invalid
 *
 */
int check_controller_id(int id) {
    if (id < 0 || id > (sb_count(open_controllers) - 1)) {
        return 0;
    }

    if (open_controllers[id] == NULL) {
        return 0;
    }

    return SDL_GameControllerGetAttached(open_controllers[id]);
}

/* --------------------------------------------------------------------------- */
void controller_close(int index) {
    if (check_controller_id(index)) {
        SDL_GameControllerClose(open_controllers[index]);
        open_controllers[index] = NULL;
    }
}

/* --------------------------------------------------------------------------- */

int modgamecontroller_getaxis(INSTANCE *my, int *params) {
    int id   = params[0];
    int axis = params[1];

    if (!check_controller_id(id)) {
        return CONTROLLER_INVALID;
    }

    return SDL_GameControllerGetAxis(open_controllers[id], axis);
}

int modgamecontroller_getbutton(INSTANCE *my, int *params) {
    int id     = params[0];
    int button = params[1];

    if (!check_controller_id(id)) {
        return CONTROLLER_INVALID;
    }

    return SDL_GameControllerGetButton(open_controllers[id], button);
}

int modgamecontroller_getname(INSTANCE *my, int *params) {
    int str = 0;
    int id  = params[0];

    if (!check_controller_id(id)) {
        str = string_new("INVALID");
        string_use(str);
        return str;
    }

    str = string_new(SDL_GameControllerName(open_controllers[id]));
    string_use(str);

    return str;
}

int modgamecontroller_num(INSTANCE *my, int *params) {
    return (SDL_NumJoysticks());
}

int modgamecontroller_close(INSTANCE *my, int *params) {
    int id = params[0];

    if (!check_controller_id(id)) {
        return CONTROLLER_INVALID;
    }

    controller_close(id);

    return 0;
}

int modgamecontroller_open(INSTANCE *my, int *params) {
    SDL_GameController *controller;
    int n, index = params[0];

    if (SDL_IsGameController(index)) {
        controller = SDL_GameControllerOpen(index);
        n = find_free_controllerID(open_controllers);
        if (n >= 0) {
            open_controllers[n] = controller;
        } else {
            sb_push(open_controllers, controller);
            n = sb_count(open_controllers) - 1;
        }

        return n;
    } else {
        return CONTROLLER_INVALID;
    }
}

/* ------------------------------------------------------------ */
/* Module initialisation routines                               */

void __pxtexport(mod_gamecontroller, module_initialize)() {
    if (!SDL_WasInit(SDL_INIT_GAMECONTROLLER)) {
        SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
    }
}

/* --------------------------------------------------------------------------- */

void __pxtexport(mod_gamecontroller, module_finalize)() {
    int32_t i = 0, n = 0;
    // Unload controllers, if any
    n = sb_count(open_controllers);
    for (i = 0; i < n; i++) {
        controller_close(i);
    }
    sb_free(open_controllers);

    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER)) {
        SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    }
}

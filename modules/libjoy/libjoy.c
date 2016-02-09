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

/* --------------------------------------------------------------------------- */
/* Thanks Sandman for suggest on openjoys at initialization time               */
/* --------------------------------------------------------------------------- */
/* Credits SplinterGU/Sandman 2007-2009                                        */
/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>

/* --------------------------------------------------------------------------- */

#include "pxtdl.h"

#include "pxtrtm.h"

#include "files.h"
#include "xstrings.h"

#ifndef __MONOLITHIC__
#include "libjoy_symbols.h"
#endif

/* --------------------------------------------------------------------------- */

#define MAX_JOYS 32

static int _max_joys = 0;
static SDL_Joystick *_joysticks[MAX_JOYS];
static int _selected_joystick = -1;

/* --------------------------------------------------------------------------- */
/* libjoy_num ()                                                               */
/* Returns the number of joysticks present in the system                       */
/* --------------------------------------------------------------------------- */

int libjoy_num(void) {
    return _max_joys;
}

/* --------------------------------------------------------------------------- */
/* libjoy_name (int JOY)                                                       */
/* Returns the name for a given joystick present in the system                 */
/* --------------------------------------------------------------------------- */

int libjoy_name(int joy) {
    int result;
    result = string_new(SDL_JoystickNameForIndex(joy));
    string_use(result);
    return result;
}

/* --------------------------------------------------------------------------- */
/* libjoy_select (int JOY)                                                     */
/* Returns the selected joystick number                                        */
/* --------------------------------------------------------------------------- */

int libjoy_select(int joy) {
    return (_selected_joystick = joy);
}

/* --------------------------------------------------------------------------- */
/* libjoy_buttons ()                                                           */
/* Returns the selected joystick total buttons                                 */
/* --------------------------------------------------------------------------- */

int libjoy_buttons(void) {
    if (_selected_joystick >= 0 && _selected_joystick < _max_joys) {
        return SDL_JoystickNumButtons(_joysticks[_selected_joystick]);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_axes ()                                                              */
/* Returns the selected joystick total axes                                    */
/* --------------------------------------------------------------------------- */

int libjoy_axes(void) {
    if (_selected_joystick >= 0 && _selected_joystick < _max_joys) {
        return SDL_JoystickNumAxes(_joysticks[_selected_joystick]);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_button ( int button )                                            */
/* Returns the selected joystick state for the given button                    */
/* --------------------------------------------------------------------------- */

int libjoy_get_button(int button) {
    if (_selected_joystick >= 0 && _selected_joystick < _max_joys) {
        return SDL_JoystickGetButton(_joysticks[_selected_joystick], button);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_position ( int axis )                                            */
/* Returns the selected joystick state for the given axis                      */
/* --------------------------------------------------------------------------- */

int libjoy_get_position(int axis) {
    if (_selected_joystick >= 0 && _selected_joystick < _max_joys) {
        return SDL_JoystickGetAxis(_joysticks[_selected_joystick], axis);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_hats ()                                                              */
/* Returns the total number of POV hats of the current selected joystick       */
/* --------------------------------------------------------------------------- */

int libjoy_hats(void) {
    if (_selected_joystick >= 0 && _selected_joystick < _max_joys) {
        return SDL_JoystickNumHats(_joysticks[_selected_joystick]);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_balls ()                                                             */
/* Returns the total number of balls of the current selected joystick          */
/* --------------------------------------------------------------------------- */

int libjoy_balls(void) {
    if (_selected_joystick >= 0 && _selected_joystick < _max_joys) {
        return SDL_JoystickNumBalls(_joysticks[_selected_joystick]);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_hat (int HAT)                                                    */
/* Returns the state of the specfied hat on the current selected joystick      */
/* --------------------------------------------------------------------------- */

int libjoy_get_hat(int hat) {
    if (_selected_joystick >= 0 && _selected_joystick < _max_joys) {
        if (hat >= 0 && hat <= SDL_JoystickNumHats(_joysticks[_selected_joystick])) {
            return SDL_JoystickGetHat(_joysticks[_selected_joystick], hat);
        }
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_ball (int BALL, int* dx, int* dy)                                */
/* Returns the state of the specfied ball on the current selected joystick     */
/* --------------------------------------------------------------------------- */

int libjoy_get_ball(int ball, int *dx, int *dy) {
    if (_selected_joystick >= 0 && _selected_joystick < _max_joys) {
        if (ball >= 0 && ball <= SDL_JoystickNumBalls(_joysticks[ball])) {
            return SDL_JoystickGetBall(_joysticks[_selected_joystick], ball, dx, dy);
        }
    }
    return -1;
}

/* --------------------------------------------------------------------------- */

int libjoy_get_accel(int *x, int *y, int *z) {
    return -1;
}

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/* libjoy_buttons_specific (int JOY)                                           */
/* Returns the selected joystick total buttons                                 */
/* --------------------------------------------------------------------------- */

int libjoy_buttons_specific(int joy) {
    if (joy >= 0 && joy < _max_joys) {
        return SDL_JoystickNumButtons(_joysticks[joy]);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_axes_specific (int JOY)                                              */
/* Returns the selected joystick total axes                                    */
/* --------------------------------------------------------------------------- */

int libjoy_axes_specific(int joy) {
    if (joy >= 0 && joy < _max_joys) {
        return SDL_JoystickNumAxes(_joysticks[joy]);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_button_specific (int JOY, int button)                            */
/* Returns the selected joystick state for the given button                    */
/* --------------------------------------------------------------------------- */

int libjoy_get_button_specific(int joy, int button) {
    if (joy >= 0 && joy < _max_joys) {
        if (button >= 0 && button <= SDL_JoystickNumButtons(_joysticks[joy])) {
            return SDL_JoystickGetButton(_joysticks[joy], button);
        }
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_position_specific (int JOY, int axis)                            */
/* Returns the selected joystick state for the given axis                      */
/* --------------------------------------------------------------------------- */

int libjoy_get_position_specific(int joy, int axis) {
    if (joy >= 0 && joy < _max_joys) {
        if (axis >= 0 && axis <= SDL_JoystickNumAxes(_joysticks[joy])) {
            return SDL_JoystickGetAxis(_joysticks[joy], axis);
        }
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* Added by Sandman */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* libjoy_hats_specific (int JOY)                                              */
/* Returns the total number of POV hats of the specified joystick              */
/* --------------------------------------------------------------------------- */

int libjoy_hats_specific(int joy) {
    if (joy >= 0 && joy < _max_joys) {
        return SDL_JoystickNumHats(_joysticks[joy]);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_balls_specific (int JOY)                                             */
/* Returns the total number of balls of the specified joystick                 */
/* --------------------------------------------------------------------------- */

int libjoy_balls_specific(int joy) {
    if (joy >= 0 && joy < _max_joys) {
        return SDL_JoystickNumBalls(_joysticks[joy]);
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_hat_specific (int JOY, int HAT)                                  */
/* Returns the state of the specfied hat on the specified joystick             */
/* --------------------------------------------------------------------------- */

int libjoy_get_hat_specific(int joy, int hat) {
    if (joy >= 0 && joy < _max_joys) {
        if (hat >= 0 && hat <= SDL_JoystickNumHats(_joysticks[joy])) {
            return SDL_JoystickGetHat(_joysticks[joy], hat);
        }
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* libjoy_get_ball_specific (int JOY, int BALL, int* dx, int* dy)              */
/* Returns the state of the specfied ball on the specified joystick            */
/* --------------------------------------------------------------------------- */

int libjoy_get_ball_specific(int joy, int ball, int *dx, int *dy) {
    if (joy >= 0 && joy < _max_joys) {
        if (ball >= 0 && ball <= SDL_JoystickNumBalls(_joysticks[joy])) {
            return SDL_JoystickGetBall(_joysticks[joy], ball, dx, dy);
        }
    }
    return -1;
}

/* --------------------------------------------------------------------------- */

int libjoy_get_accel_specific(int joy, int *x, int *y, int *z) {
    return -1;
}

/* --------------------------------------------------------------------------- */
/* Funciones de inicializacion del modulo/plugin                               */
/* --------------------------------------------------------------------------- */

void __pxtexport(libjoy, module_initialize)() {
    int i;

#ifdef WIN32
    SDL_SetHint(SDL_HINT_XINPUT_ENABLED, "0");
#endif
	
    if (!SDL_WasInit(SDL_INIT_JOYSTICK)) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
        SDL_JoystickEventState(SDL_ENABLE);
    }

    /* Open all joysticks */
    if ((_max_joys = SDL_NumJoysticks()) > MAX_JOYS) {
        PXTRTM_LOGERROR("[JOY] Warning: maximum number of joysticks exceeded (%i>%i)", _max_joys,
                        MAX_JOYS);
        _max_joys = MAX_JOYS;
    }

    for (i = 0; i < _max_joys; i++) {
        _joysticks[i] = SDL_JoystickOpen(i);
        if (!_joysticks[i])
            PXTRTM_LOG("[JOY] Failed to open joystick '%i'", i);
    }

    SDL_JoystickUpdate();
}

/* ----------------------------------------------------------------- */

void __pxtexport(libjoy, module_finalize)() {
    int i;

    for (i = 0; i < _max_joys; i++)
        if (_joysticks[i])
            SDL_JoystickClose(_joysticks[i]);

    if (SDL_WasInit(SDL_INIT_JOYSTICK)) {
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    }
}

/* ----------------------------------------------------------------- */

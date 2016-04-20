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

#include <string.h>
#include <stdlib.h>

#define __LIB_RENDER
#include "librender.h"

/* -------------------------------------------------------------------------- */

int fade_inc  = 0;
int fade_on   = 0;
int fade_set  = 0;
int fade_step = 64;

SDL_Color fade_from;
SDL_Color fade_to;
SDL_Color fade_pos = {255, 255, 255, 0};

/* -------------------------------------------------------------------------- */

void gr_fade_init(int r, int g, int b, int a, int speed) {
    if (fade_pos.r == r && fade_pos.g == g && fade_pos.b == b) {
        GLODWORD(librender, FADING) = 0;
        fade_on = 0;
        return;
    }

    fade_inc  = speed;
    fade_step = 0;
    fade_on   = 1;
    fade_from = fade_pos;
    fade_to.r = (uint8_t)r;
    fade_to.g = (uint8_t)g;
    fade_to.b = (uint8_t)b;
    fade_to.a = (uint8_t)a;

    GLODWORD(librender, FADING) = 1;
}

/* -------------------------------------------------------------------------- */

void gr_fade_step() {
    if (fade_on) {
        fade_set = 1;
        GLODWORD(librender, FADING) = 1;

        fade_step += fade_inc;
        if (fade_step < 0) {
            GLODWORD(librender, FADING) = 0;
            fade_step = 0;
            fade_on   = 0;
        }

        if (fade_step >= 64) {
            GLODWORD(librender, FADING) = 0;
            fade_step = 64;
            fade_on   = 0;
        }

        fade_pos.a = (uint8_t) ((fade_to.a-fade_from.a)/64. * fade_step + fade_from.a);

        if ((fade_step + fade_inc < 0 || fade_step + fade_inc > 64) &&
            (fade_pos.a == fade_to.a)) {
            GLODWORD(librender, FADING) = 0;
            fade_step = 64;
            fade_on   = 0;
        }
    }

    if (fade_set) {
        if (!fade_on && fade_pos.a == 0) {
            fade_set = 0;
        }

        // Store the old SDL Draw blend mode & set to alpha blending
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        // Draw a filled rectangle on the renderer with the right alpha
        SDL_SetRenderDrawColor(renderer,
                               fade_to.r, fade_to.g, fade_to.b, fade_pos.a);
        SDL_RenderFillRect(renderer, NULL);
    }
}

/* -------------------------------------------------------------------------- */

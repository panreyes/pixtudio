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

#include <SDL.h>

#include <stdlib.h>

#include "pxtrtm.h"

#include "libgrbase.h"
#include "libvideo.h"
#include "librender.h"

#include "pxtdl.h"
#include "dlvaracc.h"

#ifndef __MONOLITHIC__
#include "mod_video_symbols.h"
#else
extern DLVARFIXUP __pxtexport(mod_video, globals_fixup)[];
#endif

/* --------------------------------------------------------------------------- */

enum { GRAPH_MODE = 0 };

/* --------------------------------------------------------------------------- */

int modvideo_set_mode(INSTANCE *my, int *params) {
    return gr_set_mode(params[0], params[1]);
}

/* --------------------------------------------------------------------------- */

int modvideo_set_mode_2(INSTANCE *my, int *params) {
    GLODWORD(mod_video, GRAPH_MODE) = params[2];
    if(params[2] > 0 && params[2] <= 32) {
        PXTRTM_LOG("DEPRECATION WARNING: Setting the bit depth in set_mode is no longer valid\n");
    }
    return gr_set_mode(params[0], params[1]);
}

/* --------------------------------------------------------------------------- */

int modvideo_set_fps(INSTANCE *my, int *params) {
    gr_set_fps(params[0], params[1]);
    return params[0];
}

/* --------------------------------------------------------------------------- */

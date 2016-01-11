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

#ifndef __G_VIDEO_H
#define __G_VIDEO_H

#include <SDL.h>

#include "libgrbase.h"
#include "g_video_constants.h"

/* --------------------------------------------------------------------------- */

extern GRAPH *icon;

extern SDL_Surface *screen;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_RendererInfo renderer_info;

extern char *apptitle;

extern int scr_width;
extern int scr_height;
extern int renderer_width;
extern int renderer_height;

extern int scr_initialized;

extern int full_screen;
extern int double_buffer;
extern int hardware_scr;
extern int grab_input;
extern int frameless;

extern int waitvsync;

extern int scale_resolution;

extern int scale_resolution_aspectratio;
extern int scale_resolution_orientation;

/* --------------------------------------------------------------------------- */

extern int gr_init(int width, int height);
extern void gr_set_caption(char *title);
extern int gr_set_icon(GRAPH *map);
extern int gr_set_mode(int width, int height);
extern void gr_wait_vsync();

/* --------------------------------------------------------------------------- */

#endif

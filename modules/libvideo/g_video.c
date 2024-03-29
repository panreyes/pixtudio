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

#include <stdlib.h>
#include <string.h>

#include "pxtrtm.h"

#include "pxtdl.h"
#include "dlvaracc.h"

#include "libvideo.h"

#ifndef __MONOLITHIC__
#include "libvideo_symbols.h"
#else
extern DLVARFIXUP __pxtexport(libvideo, globals_fixup)[];
#endif

/* --------------------------------------------------------------------------- */

GRAPH *icon = NULL;

SDL_Surface *screen    = NULL;
SDL_Window *window     = NULL;
SDL_Renderer *renderer = NULL;
SDL_RendererInfo renderer_info;

char *apptitle = NULL;

int scr_width       = 320;
int scr_height      = 240;
int renderer_width  = 320;
int renderer_height = 240;

int scr_initialized = 0;

int full_screen   = 0;
int double_buffer = 0;
int hardware_scr  = 0;
int grab_input    = 0;
int frameless     = 0;
int waitvsync     = 0;

int scale_resolution             = 0;
int scale_resolution_aspectratio = 0;

char former_scale_quality = 0;

enum { GRAPH_MODE = 0,
       FULL_SCREEN,
       SCALE_RESOLUTION,
       SCALE_RESOLUTION_ASPECTRATIO,
       SCALE_QUALITY };

/* --------------------------------------------------------------------------- */

void gr_set_caption(char *title) {
    SDL_SetWindowTitle(window, apptitle = title);
}

/* --------------------------------------------------------------------------- */

int gr_set_icon(GRAPH *map) {
    if ((icon = map)) {
        SDL_Surface *ico = NULL;
        if (icon->format->depth == 8) {
            SDL_Color palette[256];
            if (sys_pixel_format && sys_pixel_format->palette) {
                int n;
                for (n = 0; n < 256; n++) {
                    palette[n].r = sys_pixel_format->palette->rgb[n].r;
                    palette[n].g = sys_pixel_format->palette->rgb[n].g;
                    palette[n].b = sys_pixel_format->palette->rgb[n].b;
                }
            }

            ico = SDL_CreateRGBSurfaceFrom(icon->data, 32, 32, 8, 32, 0x00, 0x00, 0x00, 0x00);

            SDL_SetPaletteColors(ico->format->palette, palette, 0, 256);
        } else {
            ico = SDL_CreateRGBSurfaceFrom(icon->data, 32, 32, icon->format->depth, icon->pitch,
                                           icon->format->Rmask, icon->format->Gmask,
                                           icon->format->Bmask, icon->format->Amask);
        }

        SDL_SetWindowIcon(window, ico);
        SDL_FreeSurface(ico);
    }

    return 1;
}

/* --------------------------------------------------------------------------- */

int gr_set_mode(int width, int height) {
    int surface_width  = width;
    int surface_height = height;
    int texture_depth  = 0;
    Uint32 sdl_flags   = 0;
    Uint32 format      = 0;
    Uint32 Rmask       = 0;
    Uint32 Gmask       = 0;
    Uint32 Bmask       = 0;
    Uint32 Amask       = 0;
    char *e;
    char scale_quality;
    char *scale_quality_hint;

    full_screen = (GLODWORD(libvideo, GRAPH_MODE) & MODE_FULLSCREEN) ? 1 : 0;
    grab_input  = (GLODWORD(libvideo, GRAPH_MODE) & MODE_MODAL) ? 1 : 0;
    frameless   = (GLODWORD(libvideo, GRAPH_MODE) & MODE_FRAMELESS) ? 1 : 0;
    waitvsync   = (GLODWORD(libvideo, GRAPH_MODE) & MODE_WAITVSYNC) ? 1 : 0;
    full_screen |= GLODWORD(libvideo, FULL_SCREEN);

    scale_resolution             = GLODWORD(libvideo, SCALE_RESOLUTION);
    scale_resolution_aspectratio = GLODWORD(libvideo, SCALE_RESOLUTION_ASPECTRATIO);
    scale_quality                = GLOBYTE(libvideo, SCALE_QUALITY);

    if (scale_quality > 1) {
        scale_quality_hint = "best";
    } else if (scale_quality == 1) {
        scale_quality_hint = "linear";
    } else {
        scale_quality_hint = "nearest";
    }

    // Overwrite all params with environment vars
    if ((e = getenv("SCALE_RESOLUTION"))) {
        scale_resolution = atol(e);
    }
    if ((e = getenv("SCALE_RESOLUTION_ASPECTRATIO"))) {
        scale_resolution_aspectratio = atol(e);
    }
    if ((e = getenv("SCALE_QUALITY"))) {
        if (strcmp(e, "0") == 0) {
            scale_quality_hint = "nearest";
        } else if(strcmp(e, "1") == 0) {
            scale_quality_hint = "linear";
        } else if(strcmp(e, "2") == 0) {
            scale_quality_hint = "best";
        }
    }

    format = SDL_PIXELFORMAT_ARGB8888;

    if (scrbitmap) {
        bitmap_destroy(scrbitmap);
        scrbitmap = NULL;
    }

    // If given a value for scale_resolution, use it
    if (scale_resolution != -1) {
        surface_width  = scale_resolution / 10000;
        surface_height = scale_resolution % 10000;
    }

    // Use the new & fancy SDL 2 routines
    if (!window) {
        sdl_flags = SDL_WINDOW_SHOWN;
        if (frameless) {
            sdl_flags |= SDL_WINDOW_BORDERLESS;
        }
        if (full_screen) {
            sdl_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        if (grab_input) {
            sdl_flags |= SDL_WINDOW_INPUT_GRABBED;
        }
        window = SDL_CreateWindow(apptitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  surface_width, surface_height, sdl_flags);
        if (!window) {
            PXTRTM_LOGERROR("Error creating window (%s)", SDL_GetError());
            return -1;
        }
    } else {
// Window resizing is not allowed in android/iOS
#if !defined(__ANDROID__) &&                                                                       \
    !((defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)) && !defined(TARGET_OS_MAC))
        int w, h;

        SDL_GetWindowSize(window, &w, &h);
        if (w != surface_width || h != surface_height) {
            SDL_SetWindowSize(window, surface_width, surface_height);
        }

        sdl_flags = SDL_GetWindowFlags(window);
        if ((sdl_flags & SDL_WINDOW_BORDERLESS) && !frameless) {
            SDL_SetWindowBordered(window, SDL_TRUE);
        } else if (!(sdl_flags & SDL_WINDOW_BORDERLESS) && frameless) {
            SDL_SetWindowBordered(window, SDL_FALSE);
        }

        if ((sdl_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) && !full_screen) {
            SDL_SetWindowFullscreen(window, 0);
        } else if (!(sdl_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) && full_screen) {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
#endif
    }

    // Handle window grab
    if (grab_input) {
        SDL_SetWindowGrab(window, SDL_TRUE);
    } else {
        SDL_SetWindowGrab(window, SDL_FALSE);
    }
    
    // Destroy renderer if SDL_HINT_RENDER_SCALE_QUALITY has changed.
    if (renderer && former_scale_quality != scale_quality) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (!renderer) {
        former_scale_quality = scale_quality;
        sdl_flags = SDL_RENDERER_ACCELERATED;
        if (waitvsync) {
            sdl_flags |= SDL_RENDERER_PRESENTVSYNC;
        }
        // We will trust SDL's render driver choice, but also
        // let the user override this default via a environment var
        if ((e = getenv("SDL_HINT_RENDER_DRIVER"))) {
            SDL_SetHint(SDL_HINT_RENDER_DRIVER, e);
        }
        
        #ifndef NO_MODSHADER
        /* Force OpenGL. We will need it for GLSL shaders */
        #ifdef __NINTENDO_SWITCH__
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles");
        #else
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        #endif
        #endif
#ifdef SDL_HINT_RENDER_BATCHING
        // Use SDL_Renderer's batching capability (if present)
        SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
#endif
        renderer = SDL_CreateRenderer(window, -1, sdl_flags);
        if (!renderer) {
            PXTRTM_LOGERROR("Error creating renderer (%s)", SDL_GetError());
            SDL_DestroyWindow(window);
            return -1;
        }
    }

    // Store the renderer info too
    SDL_GetRendererInfo(renderer, &renderer_info);
    // Store the renderer resolution
    SDL_GetRendererOutputSize(renderer, &renderer_width, &renderer_height);

    // Print some debugging info on the renderer
    if(debug) {
        PXTRTM_LOG("Renderer info:\n");
        PXTRTM_LOG("==============\n");
        PXTRTM_LOG("Accelerated rendering: %d\n", (renderer_info.flags & SDL_RENDERER_ACCELERATED) > 0);
        PXTRTM_LOG("Render to texture:     %d\n", (renderer_info.flags & SDL_RENDERER_TARGETTEXTURE) > 0);
        PXTRTM_LOG("Rendering driver:      %s\n", renderer_info.name);
        PXTRTM_LOG("VSYNC:                 %d\n", renderer_info.flags & SDL_RENDERER_PRESENTVSYNC);
        PXTRTM_LOG("Max texture size:      %dx%d\n", renderer_info.max_texture_width, renderer_info.max_texture_height);
        PXTRTM_LOG("Renderer size:         %dx%d\n", renderer_width, renderer_height);
    }

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // make the scaled rendering look smoother.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scale_quality_hint);

    // Enable SDL scaling, if needed
    if (renderer_width != width || renderer_height != height) {
        SDL_RenderSetLogicalSize(renderer, width, height);
        if(debug) {
            PXTRTM_LOG("Set logical size to: %dx%d\n", width, height);
        }
    }

    // This way we can force only one of the sizes (or both) to be native
    if (width == 0) {
        SDL_GetWindowSize(window, &width, NULL);
    }
    if (height == 0) {
        SDL_GetWindowSize(window, NULL, &height);
    }

    // Create a SDL_Surface for the pixel data until the complete rendering pipeline
    // is handled by SDL_Render
    SDL_PixelFormatEnumToMasks(format, &texture_depth, &Rmask, &Gmask, &Bmask, &Amask);
    if (screen) {
        SDL_FreeSurface(screen);
    }
    screen = SDL_CreateRGBSurface(0, width, height, texture_depth, Rmask, Gmask, Bmask, Amask);

    if (!sys_pixel_format) {
        sys_pixel_format = bitmap_create_format(32);
    } else {
        PALETTE *p = sys_pixel_format->palette;

        free(sys_pixel_format);
        sys_pixel_format = bitmap_create_format(32);

        if (p) {
            sys_pixel_format->palette = p;
            pal_refresh(sys_pixel_format->palette);
        }
    }

    scr_initialized = 1;

    SDL_ShowCursor(0);

    pal_refresh(NULL);
    palette_changed = 1;

    //    gr_make_trans_table();

    /* Bitmaps de fondo */

    /* Only allow background with same properties that video mode */
    if (!background || scr_width != screen->w || scr_height != screen->h ||
        sys_pixel_format->depth != background->format->depth) {
        if (background) {
            bitmap_destroy(background);
        }
        background = bitmap_new(0, screen->w, screen->h, sys_pixel_format->depth);
        if (background) {
            gr_clear(background);
            bitmap_add_cpoint(background, 0, 0);
        }
    }

    scr_width  = screen->w;
    scr_height = screen->h;

    regions[0].x  = 0;
    regions[0].y  = 0;
    regions[0].x2 = screen->w;
    regions[0].y2 = screen->h;

    // Finalmente seteamos icono de aplicacion
    // Necesitamos crear una surface a partir de un MAP generico de 16x16...
    gr_set_icon(icon);

    if (background)
        background->modified = 1;

    return 0;
}

/* --------------------------------------------------------------------------- */

int gr_init(int width, int height) {
#if defined(__ANDROID__) ||                                                                        \
    ((defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)) && !defined(TARGET_OS_MAC))
    return gr_set_mode(0, 0);
#else
    return gr_set_mode(width, height);
#endif
}

/* --------------------------------------------------------------------------- */

void __pxtexport(libvideo, module_initialize)() {
    char *e;

    if (!SDL_WasInit(SDL_INIT_VIDEO)) {
        SDL_InitSubSystem(SDL_INIT_VIDEO);
    }

    // Disable screensaver/screen-lock. According to SDL docs it'll reenable after SDL quits
    SDL_DisableScreenSaver();

    apptitle = appname;

    if ((e = getenv("VIDEO_WIDTH"))) {
        scr_width = atoi(e);
    }
    if ((e = getenv("VIDEO_HEIGHT"))) {
        scr_height = atoi(e);
    }
    if ((e = getenv("VIDEO_FULLSCREEN"))) {
        GLODWORD(libvideo, GRAPH_MODE) |= atoi(e) ? MODE_FULLSCREEN : 0;
    }

    // Disabled. It's better to use set_mode manually once, instead of setting the mode twice
    // as it bugs vsync and scale_quality for some reason.
    // gr_init(scr_width, scr_height);
}

/* --------------------------------------------------------------------------- */

void __pxtexport(libvideo, module_finalize)() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    if (SDL_WasInit(SDL_INIT_VIDEO)) {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
}

/* --------------------------------------------------------------------------- */

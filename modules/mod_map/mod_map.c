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

#include "xstrings.h"
#include "mod_map.h"

#include "librender.h"
#include "libtext.h"

#include "bgload.h"

/* --------------------------------------------------------------------------- */

#define G_WIDTH 0
#define G_HEIGHT 1
#define G_CENTER_X 2
#define G_X_CENTER 2
#define G_CENTER_Y 3
#define G_Y_CENTER 3
#define G_PITCH 4
#define G_DEPTH 5

#define B_CLEAR 0x00000001

/* --------------------------------------------------------------------------- */

int modmap_graphic_set(INSTANCE *my, int *params) {
    GRAPH *map;

    map = bitmap_get(params[0], params[1]);
    if (!map)
        return 0;

    switch (params[2]) {
        case 2: /* g_center_x */
            bitmap_set_cpoint(map, 0, params[3],
                              (map->ncpoints) ? (map->cpoints[0].y) : (map->height / 2));
            return 1;

        case 3: /* g_center_y */
            bitmap_set_cpoint(map, 0, (map->ncpoints) ? (map->cpoints[0].x) : (map->width / 2),
                              params[3]);
            return 1;
    }
    return 1;
}

int modmap_graphic_info(INSTANCE *my, int *params) {
    GRAPH *map;

    map = bitmap_get(params[0], params[1]);
    if (!map)
        return 0;

    switch (params[2]) {
        case G_WIDTH: /* g_wide */
            return map->width;

        case G_HEIGHT: /* g_height */
            return map->height;

        case G_PITCH: /* g_pitch */
            return map->pitch;

        case G_DEPTH: /* g_depth */
            return map->format->depth;

        case G_CENTER_X: /* g_center_x */
            if (map->ncpoints > 0)
                if (map->cpoints[0].x != CPOINT_UNDEFINED)
                    return map->cpoints[0].x;
            return map->width / 2;

        case G_CENTER_Y: /* g_center_y */
            if (map->ncpoints > 0)
                if (map->cpoints[0].y != CPOINT_UNDEFINED)
                    return map->cpoints[0].y;
            return map->height / 2;
    }

    return 1;
}

int modmap_colormod_set(INSTANCE *my, int *params) {
    // Modify how graphs are shown as:
    // srcC = srcC * (color / 255)
    GRAPH *map;

    map = bitmap_get(params[0], params[1]);
    if (!map || !map->texture) {
        return 0;
    }

    // Color modulation components
    Uint8 r = (Uint8)params[2];
    Uint8 g = (Uint8)params[3];
    Uint8 b = (Uint8)params[4];

    if (SDL_SetTextureColorMod(map->texture, r, g, b) == -1) {
        return 0;
    }

    return 1;
}

int modmap_set_point(INSTANCE *my, int *params) {
    GRAPH *bmp = bitmap_get(params[0], params[1]);
    if (!bmp || params[2] < 0 || params[2] > 999)
        return -1;
    bitmap_set_cpoint(bmp, (uint32_t)params[2], params[3], params[4]);
    return 1;
}

int modmap_set_center(INSTANCE *my, int *params) {
    GRAPH *bmp = bitmap_get(params[0], params[1]);
    if (!bmp)
        return -1;
    bitmap_set_cpoint(bmp, 0, params[2], params[3]);
    return 1;
}

int modmap_get_point(INSTANCE *my, int *params) {
    GRAPH *bmp;

    bmp = bitmap_get(params[0], params[1]);
    if (!bmp)
        return 0;

    /* Use the center as control point if it is not there */
    if (params[2] == 0 && (bmp->ncpoints == 0 || bmp->cpoints[0].x == CPOINT_UNDEFINED)) {
        *(int *)params[3] = bmp->width / 2;
        *(int *)params[4] = bmp->height / 2;
        return 1;
    }

    if ((uint32_t)params[2] >= bmp->ncpoints || params[2] < 0)
        return 0;
    if (bmp->cpoints[params[2]].x == CPOINT_UNDEFINED &&
        bmp->cpoints[params[2]].y == CPOINT_UNDEFINED)
        return 0;

    *(int *)params[3] = bmp->cpoints[params[2]].x;
    *(int *)params[4] = bmp->cpoints[params[2]].y;
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_load_png(INSTANCE *my, int *params) {
    int r = gr_load_png(string_get(params[0]));
    string_discard(params[0]);
    return r;
}

int modmap_load_pcx(INSTANCE *my, int *params) {
    int r = (int)gr_load_pcx(string_get(params[0]));
    string_discard(params[0]);
    return r;
}

int modmap_load_jpg(INSTANCE *my, int *params) {
    int r = gr_load_jpg(string_get(params[0]));
    string_discard(params[0]);
    return r;
}

int modmap_load_webp(INSTANCE *my, int *params) {
    int r = gr_load_webp(string_get(params[0]));
    string_discard(params[0]);
    return r;
}

int modmap_load_image(INSTANCE *my, int *params) {
	const char *filename = string_get(params[0]);
	unsigned char header[12];
	int r = -1;
	
	file *fp = file_open(filename, "rb");
    if(! fp) {
        PXTRTM_LOGERROR("Could not open '%s'\n", filename);
		string_discard(params[0]);
        return -1;
    }
	
	file_read(fp, header, 12);
	
	file_close(fp);

	if (header[0]==137 && header[1]=='P' && header[2]=='N' && header[3]=='G') { /* PNG */
		r = gr_load_png(filename);
	} else if(header[0]==255 && header[1]==216) { /* JPG */
		r = gr_load_jpg(filename);
	} else if (header[8]=='W' && header[9]=='E' && header[10]=='B' && header[11]=='P') { /* WEBP */
		r = gr_load_webp(filename);
	} else if (header[0]=='m' && ((header[1]=='a' && header[2]=='p') || (header[1]=='0' && header[2]=='1') || 
		(header[1]=='1' && header[2]=='6') || (header[1]=='3' && header[2]=='2'))){ /* MAP */
		r = gr_load_map(filename);
	}
	
	string_discard(params[0]);
	return r;
}

/* --------------------------------------------------------------------------- */

int modmap_save_png(INSTANCE *my, int *params) {
    int r = (int)gr_save_png(bitmap_get(params[0], params[1]), string_get(params[2]));
    string_discard(params[2]);
    return r;
}

/* ---------------------------------------------------------------------- */

int modmap_map_buffer(INSTANCE *my, int *params) {
    GRAPH *map;

    if (params[0] || params[1])
        map = bitmap_get(params[0], params[1]);
    else
        map = background;

    return map ? (int)map->data : 0;
}

/* --------------------------------------------------------------------------- */

int modmap_map_clear(INSTANCE *my, int *params) {
    GRAPH *map = bitmap_get(params[0], params[1]);
    if (map)
        gr_clear_as(map, params[2]);
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_new_map(INSTANCE *my, int *params) {
    GRAPH *map;
    map = bitmap_new_syslib(params[0], params[1], params[2]);
    if (map)
        gr_clear(map);
    return map ? map->code : 0;
}

/* --------------------------------------------------------------------------- */

int modmap_new_map_extend(INSTANCE *my, int *params) {
    GRAPH *map;
    map = bitmap_new_syslib(params[0], params[1], params[2]);
    if (map && (params[3] & B_CLEAR))
        gr_clear(map);
    return map ? map->code : 0;
}

/* --------------------------------------------------------------------------- */

int modmap_map_clone(INSTANCE *my, int *params) {
    GRAPH *origin, *map = NULL;
    origin = bitmap_get(params[0], params[1]);
    if (origin)
        map = bitmap_clone(origin);
    if (!map)
        return 0;
    map->code = bitmap_next_code();
    grlib_add_map(0, map);
    return map->code;
}

/* --------------------------------------------------------------------------- */

int modmap_map_put(INSTANCE *my, int *params) {
    GRAPH *dest = bitmap_get(params[0], params[1]);
    GRAPH *orig = bitmap_get(params[0], params[2]);

    if (!dest || !orig)
        return 0;

    gr_blit(dest, NULL, params[3], params[4], 0, 255, 255, 255, orig);
    return 1;
}

/* --------------------------------------------------------------------------- */
/** MAP_XPUT (FILE, GRAPH_DEST, GRAPH_SRC, X, Y, ANGLE, SIZE, FLAGS)
 *  Draws a map into another one, with most blitter options including flags and alpha
 */

int modmap_map_xput(INSTANCE *my, int *params) {
    GRAPH *dest = bitmap_get(params[0], params[1]);
    GRAPH *orig = bitmap_get(params[0], params[2]);

    if (!dest || !orig) {
        return 0;
    }

    if (params[5] == 0 && params[6] == 100)
        gr_blit(dest, 0, params[3], params[4], params[7], 255, 255, 255, orig);
    else
        gr_rotated_blit(dest, 0, params[3], params[4], params[7], params[5], params[6], params[6],
                        255, 255, 255, orig);
    return 1;
}

/* --------------------------------------------------------------------------- */
/** MAP_XPUTNP (FILE_DST, GRAPH_DST, FILE_SRC, GRAPH_SRC, X, Y, ANGLE, SCALE_X, SCALE_Y, FLAGS)
 *  Enhanced MAP_XPUT with all parametes and different FPG file and non-proportional scale
 */

int modmap_map_xputnp(INSTANCE *my, int *params) {
    GRAPH *dest = bitmap_get(params[0], params[1]);
    GRAPH *orig = bitmap_get(params[2], params[3]);

    if (!orig || !dest) {
        return 0;
    }

    if (params[6] == 0 && params[7] == 100 && params[8] == 100) {
        gr_blit(dest, 0, params[4], params[5], params[9], 255, 255, 255, orig);
    } else {
        gr_rotated_blit(dest, 0, params[4], params[5], params[9], params[6], params[7], params[8],
                        255, 255, 255, orig);
    }
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_map_name(INSTANCE *my, int *params) {
    GRAPH *map = bitmap_get(params[0], params[1]);
    int result;

    if (!map)
        return 0;
    result = string_new(map->name);
    string_use(result);
    return result;
}

/* --------------------------------------------------------------------------- */

int modmap_map_set_name(INSTANCE *my, int *params) {
    GRAPH *map      = bitmap_get(params[0], params[1]);
    const char *ptr = string_get(params[2]);
    if (map) {
        strncpy(map->name, ptr, sizeof(map->name));
        map->name[sizeof(map->name) - 1] = 0;
    }
    string_discard(params[2]);
    return 0;
}

/* --------------------------------------------------------------------------- */

int modmap_map_exists(INSTANCE *my, int *params) {
    GRAPH *map = bitmap_get(params[0], params[1]);
    return map == NULL ? 0 : 1;
}

/* --------------------------------------------------------------------------- */

int modmap_map_block_copy(INSTANCE *my, int *params) {
    GRAPH *dest, *orig;
    REGION clip;
    int centerx, centery, flag;
    int32_t x, y, dx, dy;
    uint32_t w, h;

    dest = bitmap_get(params[0], params[1]);
    if (!dest)
        return 0;

    orig = bitmap_get(params[0], params[4]);
    if (!orig)
        return 0;

    x    = params[5];
    y    = params[6];
    w    = params[7];
    h    = params[8];
    dx   = params[2];
    dy   = params[3];
    flag = params[9];

    if (orig->ncpoints > 0 && orig->cpoints[0].x != CPOINT_UNDEFINED) {
        centerx = orig->cpoints[0].x;
        centery = orig->cpoints[0].y;
    } else {
        centery = orig->height / 2;
        centerx = orig->width / 2;
    }

    if (flag & B_HMIRROR)
        centerx = orig->width - 1 - centerx;
    if (flag & B_VMIRROR)
        centery = orig->height - 1 - centery;

    if (x < 0) {
        dx += x;
        w += x;
        x = 0;
    }
    if (y < 0) {
        dy += y;
        h += y;
        y = 0;
    }
    if (dx < 0) {
        x += dx;
        w += dx;
        dx = 0;
    }
    if (dy < 0) {
        y += dy;
        h += dy;
        dy = 0;
    }

    if (x + w > orig->width)
        w = orig->width - x;

    if (y + h > orig->height)
        h = orig->height - y;

    if (dx + w > dest->width)
        w = dest->width - dx;

    if (dy + h > dest->height)
        h = dest->height - dy;

    if (w <= 0 || h <= 0)
        return 0;

    clip.x  = dx;
    clip.y  = dy;
    clip.x2 = dx + w - 1;
    clip.y2 = dy + h - 1;
    gr_blit(dest, &clip, dx - x + centerx, dy - y + centery, flag, 255, 255, 255, orig);

    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_load_map(INSTANCE *my, int *params) {
    int r = gr_load_map(string_get(params[0]));
    string_discard(params[0]);
    return r;
}

/* --------------------------------------------------------------------------- */

int modmap_unload_map(INSTANCE *my, int *params) {
    return grlib_unload_map(params[0], params[1]);
}

/* ---------------------------------------------------------------------- */

int modmap_save_map(INSTANCE *my, int *params) {
    int r = (int)gr_save_map(bitmap_get(params[0], params[1]), (char *)string_get(params[2]));
    string_discard(params[2]);
    return r;
}

/* --------------------------------------------------------------------------- */

int modmap_get_rgb(INSTANCE *my, int *params) {
    gr_get_rgb(params[0], (int *)params[1], (int *)params[2], (int *)params[3]);
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_get_rgba(INSTANCE *my, int *params) {
    gr_get_rgba(params[0], (int *)params[1], (int *)params[2], (int *)params[3], (int *)params[4]);
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_rgb(INSTANCE *my, int *params) {
    return sys_pixel_format->depth > 8 ? gr_rgb(params[0], params[1], params[2])
                                       : gr_find_nearest_color(params[0], params[1], params[2]);
}

/* --------------------------------------------------------------------------- */

int modmap_rgba(INSTANCE *my, int *params) {
    return sys_pixel_format->depth > 8 ? gr_rgba(params[0], params[1], params[2], params[3])
                                       : gr_find_nearest_color(params[0], params[1], params[2]);
}

/* --------------------------------------------------------------------------- */

int modmap_get_rgb_depth(INSTANCE *my, int *params) {
    gr_get_rgb_depth(params[4], params[0], (int *)params[1], (int *)params[2], (int *)params[3]);
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_get_rgba_depth(INSTANCE *my, int *params) {
    gr_get_rgba_depth(params[5], params[0], (int *)params[1], (int *)params[2], (int *)params[3],
                      (int *)params[4]);
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_rgb_depth(INSTANCE *my, int *params) {
    return params[3] > 8 ? gr_rgb_depth(params[3], params[0], params[1], params[2])
                         : gr_find_nearest_color(params[0], params[1], params[2]);
}

/* --------------------------------------------------------------------------- */

int modmap_rgba_depth(INSTANCE *my, int *params) {
    return params[4] > 8 ? gr_rgba_depth(params[4], params[0], params[1], params[2], params[3])
                         : gr_find_nearest_color(params[0], params[1], params[2]);
}

/* --------------------------------------------------------------------------- */

int modmap_fade(INSTANCE *my, int *params) {
    gr_fade_init(params[0], params[1], params[2], params[3], params[4]);
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_fade_in(INSTANCE *my, int *params) {
    gr_fade_init(0, 0, 0, 0, 8);
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_fade_out(INSTANCE *my, int *params) {
    gr_fade_init(0, 0, 0, 255, 8);
    return 1;
}

/* ---------------------------------------------------------------------- */

/* Funciones de FPG */

int modmap_load_fpg(INSTANCE *my, int *params) {
    int r;
    r = gr_load_fpg(string_get(params[0]));
    string_discard(params[0]);
    return r;
}

/* --------------------------------------------------------------------------- */

int modmap_save_fpg(INSTANCE *my, int *params) {
    int r;
    r = gr_save_fpg(params[0], string_get(params[1]));
    string_discard(params[1]);
    return r;
}

/* --------------------------------------------------------------------------- */

int modmap_unload_fpg(INSTANCE *my, int *params) {
    grlib_destroy(params[0]);
    return 1;
}

/* --------------------------------------------------------------------------- */

int modmap_fpg_exists(INSTANCE *my, int *params) {
    GRLIB *lib = grlib_get(params[0]);
    return lib == NULL ? 0 : 1;
}

/* --------------------------------------------------------------------------- */

int modmap_fpg_add(INSTANCE *my, int *params) {
    GRAPH *orig = bitmap_get(params[2], params[3]);
    GRAPH *dest;

    if (orig == NULL)
        return 0;
    dest       = bitmap_clone(orig);
    dest->code = params[1];

    return grlib_add_map(params[0], dest);
}

/* --------------------------------------------------------------------------- */

int modmap_fpg_new(INSTANCE *my, int *params) {
    return grlib_new();
}

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/** LOAD_FNT (STRING FILENAME)
 *  Load a .FNT font from disk (returns the font ID)
 */

int modmap_load_fnt(INSTANCE *my, int *params) {
    int r = gr_font_load((char *)string_get(params[0]));
    string_discard(params[0]);
    return r;
}

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/** LOAD_TTF (STRING FILENAME)
 *  Load a .TTF font from disk (returns the font ID)
 */

int modmap_load_ttf(INSTANCE *my, int *params) {
    int r = gr_font_ttf_load((char *)string_get(params[0]));
    string_discard(params[0]);
    return r;
}

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/** LOAD_BDF (STRING FILENAME)
 *  Load a .BDF font from disk (returns the font ID)
 */

int modmap_load_bdf(INSTANCE *my, int *params) {
    int r = gr_load_bdf((char *)string_get(params[0]));
    string_discard(params[0]);
    return r;
}

/* --------------------------------------------------------------------------- */
/** UNLOAD_FNT (FONT)
 *  Destroys a font in memory
 */

int modmap_unload_fnt(INSTANCE *my, int *params) {
    if (params[0] > 0) {
        gr_font_destroy(params[0]);
    }

    return 0;
}

/* --------------------------------------------------------------------------- */
/** FNT_NEW (DEPTH)
 *  Create a new font in memory (returns the font ID)
 */

int modmap_fnt_new(INSTANCE *my, int *params) {
    return gr_font_new(CHARSET_CP850, params[0], FONT_TYPE_BITMAP);
}

/* --------------------------------------------------------------------------- */

/** FNT_NEW (CHARSET, DEPTH)
 *  Create a new font in memory (returns the font ID)
 */

int modmap_fnt_new_charset(INSTANCE *my, int *params) {
    return gr_font_new(params[0], params[1], FONT_TYPE_BITMAP);
}

/* --------------------------------------------------------------------------- */

/** FNT_NEW (FILE, GRAPH, CHARSET, WITDH, HEIGHT, FIRST, LAST, FLAGS)
 *  Create a new font in memory (returns the font ID)
 */

int modmap_fnt_new_from_bitmap(INSTANCE *my, int *params) {
    GRAPH *bmp = bitmap_get(params[0], params[1]);
    if (!bmp)
        return -1;
    return gr_font_newfrombitmap(bmp, params[2], params[3], params[4], params[5], params[6],
                                 params[7]);
}

/* --------------------------------------------------------------------------- */
/** GET_GLYPH (FONT, GLYPH)
 *  Create a system map as a copy of one of the font glyphs (returns the map ID)
 */

int modmap_get_glyph(INSTANCE *my, int *params) {
    FONT *font = gr_font_get(params[0]);
    GRAPH *map;
    unsigned char c = params[1];

    if (!font) {
        return -1;
    }

    if(font->type == FONT_TYPE_VECTOR) {
        // The glyphs are not stored as bitmaps in the font
        // (only their alpha channel is) so we call
        // gr_text_bitmap to render one glyph
        unsigned char buffer[2] = " ";
        buffer[0] = (unsigned char)params[1];

        GRAPH *gr = gr_text_bitmap(params[0], (char *)buffer, 0);
        if (!gr) {
            return -1;
        }

        return gr->code;
    } else {
        if (font->charset == CHARSET_ISO8859) {
            c = iso88591_to_cp850[c];
        }
        if (!font->glyph[c].bitmap) {
            return -1;
        }

        map = bitmap_clone(font->glyph[c].bitmap);
        if (!map) {
            return -1;
        }

        map->code = bitmap_next_code();

        if (!map->ncpoints) {
            bitmap_add_cpoint(map, map->width / 2, map->height / 2);
        }
        bitmap_add_cpoint(map, font->glyph[c].xoffset, font->glyph[c].yoffset);
        bitmap_add_cpoint(map, font->glyph[c].xadvance, font->glyph[c].yadvance);

        grlib_add_map(0, map);

        return map->code;
    }
}

/* --------------------------------------------------------------------------- */
/** SET_GLYPH (FONT, GLYPH, LIBRARY, GRAPHIC)
 *  Change one of the font's glyphs
 */

int modmap_set_glyph(INSTANCE *my, int *params) {
    FONT *font      = gr_font_get(params[0]);
    GRAPH *map      = bitmap_get(params[2], params[3]);
    unsigned char c = params[1];

    if(!font) {
        return 0;
    }

    if(font->type != FONT_TYPE_BITMAP) {
        return 0;
    }

    if (font->charset == CHARSET_ISO8859) {
        c = iso88591_to_cp850[c];
    }

    if (map) {
        if (font->glyph[c].bitmap) {
            grlib_unload_map(0, font->glyph[c].bitmap->code);
        }
        font->glyph[c].bitmap = bitmap_clone(map);
        if (font->glyph[c].bitmap) {
            font->glyph[c].bitmap->code = bitmap_next_code();

            if (map->ncpoints >= 3 && map->cpoints) {
                font->glyph[c].xoffset  = map->cpoints[1].x;
                font->glyph[c].yoffset  = map->cpoints[1].y;
                font->glyph[c].xadvance = map->cpoints[2].x;
                font->glyph[c].yadvance = map->cpoints[2].y;
            } else {
                font->glyph[c].xoffset  = 0;
                font->glyph[c].yoffset  = 0;
                font->glyph[c].xadvance = map->width + map->width / 5;
                font->glyph[c].yadvance = map->height + map->height / 5;
                bitmap_add_cpoint(font->glyph[c].bitmap, 0, 0);
            }
            grlib_add_map(0, font->glyph[c].bitmap);
        }
    }

    return 0;
}

/* --------------------------------------------------------------------------- */
/** TTF_SET_SIZE (FONT, SIZE)
 *  Set the size of a vector font (in pixels)
 */

int modmap_ttf_set_size(INSTANCE *my, int *params) {
    FONT *font = gr_font_get(params[0]);

    if(!font || font->type != FONT_TYPE_VECTOR) {
        return -1;
    }

    // Nothing to do
    if(font->size == params[0]) {
        return 0;
    }

    int error = FT_Set_Pixel_Sizes(font->face, params[1], params[1]);
    if(error) {
        return -1;
    }

    font->size = params[1];

    // Cache the new glyphs
    render_glyphs(params[0]);

    return 0;
}

/* --------------------------------------------------------------------------- */
/** TTF_GET_FAMILY (FONT)
 *  Gets a TTF font's family name
 */
int modmap_ttf_get_family(INSTANCE *my, int *params) {
    FONT *font = gr_font_get(params[0]);
    const char *family_name;

    if(!font || font->type != FONT_TYPE_VECTOR) {
        family_name = "";
    } else {
        if(!font->face->family_name) {
            family_name = "";
        } else {
            family_name = (const char *)font->face->family_name;
        }
    }

    int str_id = string_new(family_name);
    string_use(str_id);

    return str_id;
}

/* --------------------------------------------------------------------------- */
/** TTF_GET_STYLE (FONT)
 *  Gets a TTF font's family name
 */
int modmap_ttf_get_style(INSTANCE *my, int *params) {
    FONT *font = gr_font_get(params[0]);
    const char *style_name;

    if(!font || font->type != FONT_TYPE_VECTOR) {
        style_name = "";
    } else {
        if(!font->face->style_name) {
            style_name = "";
        } else {
            style_name = (const char *)font->face->style_name;
        }
    }

    int str_id = string_new(style_name);
    string_use(str_id);

    return str_id;
}

/* --------------------------------------------------------------------------- */
/** SAVE_FNT (FONT, STRING FILENAME)
 *  Saves a font to disk
 */

int modmap_save_fnt(INSTANCE *my, int *params) {
    int r = gr_font_save(params[0], (char *)string_get(params[1]));
    string_discard(params[1]);
    return r;
}

/* --------------------------------------------------------------------------- */
/**
   int LOAD_FPG(STRING FICHERO, INT POINTER VARIABLE)
   Loads fpg file FICHERO on a separate thread
   VARIABLE is -2 while waiting, -1 on error, >=0 otherwise
 **/

int modmap_bgload_fpg(INSTANCE *my, int *params) {
    bgload(gr_load_fpg, params);
    return 0;
}

int modmap_bgload_map(INSTANCE *my, int *params) {
    bgload(gr_load_map, params);
    return 0;
}

int modmap_bgload_png(INSTANCE *my, int *params) {
    bgload(gr_load_png, params);
    return 0;
}

int modmap_bgload_pcx(INSTANCE *my, int *params) {
    bgload(gr_load_pcx, params);
    return 0;
}

int modmap_bgload_jpg(INSTANCE *my, int *params) {
    bgload(gr_load_jpg, params);
    return 0;
}

int modmap_bgload_webp(INSTANCE *my, int *params) {
    bgload(gr_load_webp, params);
    return 0;
}

int modmap_bgload_fnt(INSTANCE *my, int *params) {
    bgload(gr_font_load, params);
    return 0;
}

int modmap_bgload_bdf(INSTANCE *my, int *params) {
    bgload(gr_load_bdf, params);
    return 0;
}

/* --------------------------------------------------------------------------- */

void __pxtexport(mod_map, module_finalize)() {
#ifndef WIN32
    // Unload all the loaded fonts
    // This code seems to crash on Windows, and I don't yet know why...
    for(int32_t i=0; i<MAX_FONTS; i++) {
        gr_font_destroy(i);
    }
#endif

    FT_Done_FreeType(font_library);
}

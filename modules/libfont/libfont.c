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

#define __LIB_FONT
#include "libfont.h"
#include "systemfont.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#ifndef __MONOLITHIC__
#include "libfont_symbols.h"
#endif

/* --------------------------------------------------------------------------- */

FONT *fonts[MAX_FONTS] = {0};
int font_count         = 0;   /* System font */
FT_Library font_library;      /* For FreeType-rendered fonts */

/* --------------------------------------------------------------------------- */

static int align_bitmap_char_left(unsigned char *data, int width, int height, int pitch, int bpp);
static int get_bitmap_char_width(unsigned char *data, int width, int height, int pitch, int bpp);

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_new
 *
 *  Create a new font, with no characters in it.
 *  The font uses the MS-DOS charset and 8bpp by default.
 *
 *  PARAMS :
 *      charset
 *      bpp
 *      type
 *
 *  RETURN VALUE :
 *      Code of the new font or -1 if error
 *      The font data is in the global array fonts[index]
 *
 */

int gr_font_new(int charset, uint8_t bpp, uint8_t type) {
    // Vector fonts are not supported for bpp!=32
    if(type == FONT_TYPE_VECTOR && bpp != 32) {
        return -1;
    }

    FONT *f = (FONT *)malloc(sizeof(FONT));

    if (f == NULL) {
        return -1; // No memory
    }

    if (font_count == MAX_FONTS - 1) {  // Too many fonts
        free(f);
        return -1;
    }

    memset(f, 0, sizeof(FONT));
    f->charset   = charset; // CHARSET_CP850
    f->bpp       = bpp;     // 8
    f->type      = type;
    f->maxwidth  = 0;
    f->maxheight = 0;

    fonts[font_count] = f;
    return font_count++;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_newfrombitmap
 *
 *  Create a new font using a bitmap as source.
 *  For 1bpp fonts, the bitmap should be in black and white (1 bit per pixel)
 *  with a fixed character size and a character width of 8, 16, 24...
 *
 *  PARAMS :
 *  map         Pointer to the bitmap
 *  charset     Charset
 *  width       Width of each character, in bits (pixels)
 *  height      Height of each character
 *  first       First char
 *  last        Last char
 *  options     Can be 0 or a combination of the following flags:
 *
 * NFB_FIXEDWIDTH  Create a fixed width font (the default is a propotional width one)
 *
 *  RETURN VALUE :
 *      -1 if Error, id otherwise
 *
 */

int gr_font_newfrombitmap(GRAPH *map, int charset, int width, int height, int first, int last,
                          int options) {
    char *chardata;
    FONT *f;
    char *ptr, *charptr;
    int i, y, id;
    int charsize;
    int linesize = 0;
    int w, h, cw, ch;
    GRAPH *bitmap;

    id = gr_font_new(charset, map->format->depth, FONT_TYPE_BITMAP);
    if (id == -1)
        return -1;

    f = fonts[id];

    charsize = map->pitch * height;

    switch (map->format->depth) {
        case 1:
            linesize = width / 8;
            break;

        case 8:
            linesize = width;
            break;

        case 16:
            linesize = width * sizeof(uint16_t);
            break;

        case 32:
            linesize = width * sizeof(uint32_t);
            break;
    }

    ch = map->height / height;
    cw = map->width / width;

    i = first;

    for (h = 0; h < ch; h++) {
        if (i > last)
            break;

        chardata = map->data + h * charsize;

        for (charptr = chardata, w = 0; w < cw; w++, charptr += linesize, i++) {
            int align = 0;

            if (options != NFB_FIXEDWIDTH)
                align = align_bitmap_char_left((unsigned char *)charptr, width, height, map->pitch,
                                               map->format->depth) *
                        map->format->depthb;

            bitmap = bitmap_new(i, width, height, map->format->depth);
            if (!bitmap) {
                gr_font_destroy(id);
                return -1; // No memory
            }

            f->glyph[i].bitmap  = bitmap;
            f->glyph[i].xoffset = 0;
            f->glyph[i].yoffset = 0;

            bitmap_add_cpoint(bitmap, 0, 0);

            ptr = bitmap->data;
            memset(bitmap->data, '\0', bitmap->pitch * bitmap->height);

            for (y = 0; y < height; y++, ptr += bitmap->pitch)
                memcpy(ptr, charptr + map->pitch * y + align, bitmap->widthb - align);

            if (options != NFB_FIXEDWIDTH) {
                if (map->format->depth == 1)
                    f->glyph[i].xadvance =
                        get_bitmap_char_width((unsigned char *)charptr, width, height, map->pitch,
                                              map->format->depth) +
                        1;
                else
                    f->glyph[i].xadvance =
                        get_bitmap_char_width(bitmap->data, width, height, bitmap->pitch,
                                              bitmap->format->depth) +
                        1;
            } else {
                f->glyph[i].xadvance = width + 1;
            }

            bitmap->modified   = 0;
            bitmap->info_flags = 0;
            bitmap_update_texture(bitmap);
        }
    }

    /* Set a reasonable size for the space */

    f->glyph[32].xadvance = width * 65 / 100;
    f->maxwidth           = width;
    f->maxheight          = height;

    return id;
}

/* --------------------------------------------------------------------------- */
/* Utility function used by gr_new_fontfrombitmap to align characters */

static int align_bitmap_char_left(unsigned char *data, int width, int height, int pitch, int bpp) {
    int leftest, n, c, x;
    static int leftest_table[256] = {0};

    if (leftest_table[0] == 0) {
        for (n = 0; n < 256; n++) {
            if (n & 0x80)
                leftest_table[n] = 0;
            else if (n & 0x40)
                leftest_table[n] = 1;
            else if (n & 0x20)
                leftest_table[n] = 2;
            else if (n & 0x10)
                leftest_table[n] = 3;
            else if (n & 0x08)
                leftest_table[n] = 4;
            else if (n & 0x04)
                leftest_table[n] = 5;
            else if (n & 0x02)
                leftest_table[n] = 6;
            else if (n & 0x01)
                leftest_table[n] = 7;
            else
                leftest_table[n] = 8;
        }
    }

    if (bpp == 1) {
        leftest = 8;
        for (n = 0; n < height; n++) {
            for (c = 0; c < width; c += 8) {
                if (leftest > c + leftest_table[data[(width * n + c) / 8]])
                    leftest = c + leftest_table[data[(width * n + c) / 8]];
            }
        }

        if (leftest > 7) {
            if (width > leftest)
                for (n = 0; n < height; n++)
                    memmove(data + n * width / 8, data + (n * width + leftest) / 8,
                            (width - leftest) / 8);

            leftest &= 7;
        }

        for (n = 0; n < height * width / 8; n++)
            data[n] <<= leftest;

        return 0;
    } else {
        int align = width;

        switch (bpp) {
            case 8: {
                uint8_t *p = (uint8_t *)data;
                while (height--) {
                    p = (uint8_t *)(data + height * pitch);
                    for (x = 0; x < width && !*p++; x++)
                        ;
                    if (align > x)
                        align = x;
                }
                return (align == width) ? 0 : align;
            }

            case 16: {
                uint16_t *p = (uint16_t *)data;
                while (height--) {
                    p = (uint16_t *)(data + height * pitch);
                    for (x = 0; x < width && !*p++; x++)
                        ;
                    if (align > x)
                        align = x;
                }
                return (align == width) ? 0 : align;
            }

            case 32: {
                uint32_t *p = (uint32_t *)data;
                while (height--) {
                    p = (uint32_t *)(data + height * pitch);
                    for (x = 0; x < width && !*p++; x++)
                        ;
                    if (align > x)
                        align = x;
                }
                return (align == width) ? 0 : align;
            }
        }

        return 0;
    }
}

/* --------------------------------------------------------------------------- */
/* Utility function used by gr_new_fontfrombitmap to calculate char widths */

static int get_bitmap_char_width(unsigned char *data, int width, int height, int pitch, int bpp) {
    int x, c, d, max = 0, w;

    switch (bpp) {
        case 1:
            while (height--) {
                for (x = 0; x < width; x += 8) {
                    c = *data++;
                    for (d = 8; d > 0; d--, c >>= 1)
                        if (c & 0x01)
                            break;
                    if (x * 8 + d > max)
                        max = x * 8 + d;
                }
            }
            return (max < 4) ? 4 : max;

        case 8: {
            uint8_t *p = (uint8_t *)data;
            while (height--) {
                w = 0;
                p = (uint8_t *)(data + height * pitch);
                for (x = 0; x < width; x++) {
                    if (*p++)
                        w = x;
                }
                if (max < w)
                    max = w;
            }
            return (!max) ? width * 65 / 100 : max;
        }

        case 16: {
            uint16_t *p;
            while (height--) {
                w = 0;
                p = (uint16_t *)(data + height * pitch);
                for (x = 0; x < width; x++) {
                    if (*p++)
                        w = x;
                }
                if (max < w)
                    max = w;
            }
            return (!max) ? width * 65 / 100 : max;
        }

        case 32: {
            uint32_t *p;
            while (height--) {
                w = 0;
                p = (uint32_t *)(data + height * pitch);
                for (x = 0; x < width; x++) {
                    if (*p++)
                        w = x;
                }
                if (max < w)
                    max = w;
            }
            return (!max) ? width * 65 / 100 : max;
        }
    }

    return width;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_systemfont
 *
 *  Create the system font. This function should be called once.
 *
 *  PARAMS :
 *  chardata  Pointer to the system font data
 *
 *  RETURN VALUE :
 *      Always returns 1
 *
 */

int gr_font_systemfont(char *chardata) {
    GRAPH *map = bitmap_new_ex(0, 8, 8 * 256, 32, chardata, 32);
    if (!map)
        return -1;

    int last_count = font_count;
    if (fonts[0])
        gr_font_destroy(0);
    font_count = 0;

    gr_font_newfrombitmap(map, CHARSET_CP850, 8, 8, 0, 255, 0);
    if (last_count)
        font_count = last_count;

    bitmap_destroy(map);

    return 1;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_destroy
 *
 *  Destroy a font and all the internal bitmap data
 *
 *  PARAMS :
 *  fontid  ID of the font
 *
 *  RETURN VALUE :
 *      None
 *
 */

void gr_font_destroy(int fontid) {
    int n;

    if (fontid >= 0 && fontid < font_count) {
        if (!fonts[fontid]) {
            return;
        }

        if(fonts[fontid]->type == FONT_TYPE_BITMAP) {
            for (n = 0; n < MAX_FONTS; n++) {
                if (fonts[fontid]->glyph[n].bitmap) {
                    bitmap_destroy(fonts[fontid]->glyph[n].bitmap);
                }
            }
        } else {
            FT_Done_Face(fonts[fontid]->face);
        }

        free(fonts[fontid]);
        fonts[fontid] = NULL;
        while (font_count > 0 && fonts[font_count - 1] == 0) {
            font_count--;
        }
    }
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_font_get
 *
 *  Return a font object, given an ID
 *
 *  PARAMS :
 *  id  id of the font
 *
 *  RETURN VALUE :
 *      Pointer to the font object or NULL if it does not exist
 *
 */

FONT *gr_font_get(int id) {
    if (id >= 0 && id < MAX_FONTS) {
        return fonts[id];
    }

    return NULL;
}

/* --------------------------------------------------------------------------- */

void __pxtexport(libfont, module_initialize)() {
    gr_font_systemfont((char *)default_font);
}

/* --------------------------------------------------------------------------- */

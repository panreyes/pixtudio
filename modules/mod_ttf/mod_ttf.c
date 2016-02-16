/*  Theora module for PixTudio
 *
 *  Originally written by Joseba Garci­a Etxebarria <joseba.gar@gmail.com>
 *  based on the simplesdl.c example included with theoraplay
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
*/

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/* Freetype 2 */
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

/* PixTudio stuff */
#include "pxtdl.h"
#include "pxtrtm.h"
#include "libgrbase.h"
#include "g_video.h"
#include "xstrings.h"
#include "xctype.h"
#include "mod_map.h"

#ifndef __MONOLITHIC__
#include "mod_ttf_symbols.h"
#endif

#define MAX_FACES 255

typedef struct {
    FT_Face   face;
    bool      loaded;
    GRAPH    *gr_glyph[256];
    uint32_t  xadvance[256];
    uint32_t  yadvance[256];
    uint32_t  xoffset[256];
    uint32_t  yoffset[256];
} FONTFACE;

FONTFACE faces[MAX_FACES];

/* ---------------------- */
FT_Library library;
/* ---------------------- */

bool preload_glyphs(int n) {
    // Pre-render all tha glyph graphs
    for (uint16_t charcode = 0; charcode < 256; charcode++) {
        // Is there a previous graph? -> unload it
        if(faces[n].gr_glyph[charcode]) {
            bitmap_destroy(faces[n].gr_glyph[charcode]);
        }

        // Get the font face index for CP850 character n
        FT_UInt glyph_index = FT_Get_Char_Index(faces[n].face, cp850_to_utf8[charcode]);

        // load glyph image into the slot without rendering
        int error = FT_Load_Glyph(faces[n].face, glyph_index, FT_LOAD_TARGET_LIGHT | FT_LOAD_RENDER);
        if (error) {
            continue;
        }

        // Store the font metrics
        faces[n].xadvance[charcode] = faces[n].face->glyph->advance.x >> 6;
        faces[n].yadvance[charcode] = faces[n].face->glyph->advance.y >> 6;
        faces[n].xoffset[charcode]      = faces[n].face->glyph->bitmap_left;
        faces[n].yoffset[charcode]       = faces[n].face->glyph->bitmap_top;

        // Create a 8bpp graph for the glyph image, which
        if(faces[n].face->glyph->bitmap.width > 0 && faces[n].face->glyph->bitmap.rows > 0) {
            faces[n].gr_glyph[charcode] = bitmap_new(charcode, faces[n].face->glyph->bitmap.width, faces[n].face->glyph->bitmap.rows, 8);
            bitmap_add_cpoint(faces[n].gr_glyph[charcode], 0, 0);
            // Store the contents of the glyph bitmap
            uint8_t *graph_pos;
            uint8_t *alpha_pos;

            for(uint32_t y = 0; y < faces[n].face->glyph->bitmap.rows; y++) {
                for(uint32_t x = 0; x < faces[n].face->glyph->bitmap.width; x++) {
                    graph_pos = ((uint8_t *)faces[n].gr_glyph[charcode]->data) + faces[n].gr_glyph[charcode]->pitch * y + x;
                    alpha_pos = ((uint8_t *)faces[n].face->glyph->bitmap.buffer) + faces[n].face->glyph->bitmap.pitch * y + x;
                    *graph_pos = *alpha_pos;
                }
            }
        } else {
            // Mark the GRAPH pointer empty so that we don't use it
            faces[n].gr_glyph[charcode] = NULL;
        }
    }

    return true;
}

bool load_face(const char *path, uint16_t size, uint8_t n) {
    // First of all, read the whole file into memory
    file *fp = file_open(path, "rb");
    if(!fp) {
        if(debug) {
            PXTRTM_LOGERROR("ERROR: Could not load font face %s\n", path);
        }
        return false;
    }

    // Read the file size
    int fsize = file_size(fp);
    if(fsize <= 0) {
        file_close(fp);
        if(debug) {
            PXTRTM_LOGERROR("ERROR: font face size is 0\n");
        }
        return false;
    }

    // Read the file into memory
    void *data[fsize];
    int read = 0;
    if((read = file_read (fp, data, fsize)) < size) {
        if(debug) {
            PXTRTM_LOGERROR("You should not be here\n");
        }
    }
    file_close(fp);

    // Create the font face and perform some basic checks
    int error = FT_New_Memory_Face(library, (const FT_Byte*)data, read, 0, &faces[n].face);
    if(error) {
        if(debug) {
            PXTRTM_LOGERROR("ERROR: Could not load font face %s\n", path);
        }
        return false;
    }

    if(FT_HAS_VERTICAL(faces[n].face)) {
        if(debug) {
            PXTRTM_LOGERROR("ERROR: Vertical font faces are not supported\n");
        }
        FT_Done_Face(faces[n].face);
        return false;
    }

    if(!FT_IS_SCALABLE(faces[n].face)) {
        if(debug) {
            PXTRTM_LOGERROR("ERROR: Non-scallable font faces are not supported\n");
        }
        FT_Done_Face(faces[n].face);
        return false;
    }

    // Set the character size in px
    error = FT_Set_Pixel_Sizes(faces[n].face, size, size);
    if(error) {
        FT_Done_Face(faces[n].face);
        return false;
    }

    // Store the glyph bitmaps
    preload_glyphs(n);

    // Mark the font face as loaded
    faces[n].loaded = true;

    return true;
}

// Determine the size of a text's bounding box
bool get_text_size(const char *text, uint8_t fontid, uint32_t *w, uint32_t *h, int32_t *baseline_y) {
    int32_t top_pixel = 0;
    int32_t bottom_pixel = 0;
    *w = 0;
    *h = 0;
    *baseline_y = 0;
    unsigned char code;
    FT_UInt previous    = 0;
    uint32_t num_glyphs = strlen(text);

    // Run through all the glyphs and compute the box size
    for (uint32_t n = 0; n < num_glyphs; n++) {
        // Character code in CP850 encoding
        code = (unsigned char)text[n];

        // Is this glyph bigger than the biggest? -> Store the value
        if(top_pixel < faces[fontid].yoffset[code]) {
            top_pixel = faces[fontid].yoffset[code];
        }

        if(faces[fontid].gr_glyph[code] && (bottom_pixel > (int32_t)(faces[fontid].yoffset[code] - faces[fontid].gr_glyph[code]->height))) {
            bottom_pixel = faces[fontid].yoffset[code] - faces[fontid].gr_glyph[code]->height;
        }

        // Is this glyph deeper than the deepest? -> Store the value
        if(faces[fontid].gr_glyph[code] && (faces[fontid].gr_glyph[code]->height - faces[fontid].yoffset[code]) > *baseline_y) {
            *baseline_y = faces[fontid].gr_glyph[code]->height - faces[fontid].yoffset[code];
        }

        FT_UInt glyph_index = FT_Get_Char_Index(faces[fontid].face, cp850_to_utf8[(unsigned char)text[n]]);

        /* retrieve kerning distance and move pen position */
        if (FT_HAS_KERNING(faces[fontid].face) && previous && glyph_index) {
            FT_Vector  delta;

            FT_Get_Kerning(faces[fontid].face, previous, glyph_index, FT_KERNING_DEFAULT, &delta);

            *w += (delta.x >> 6);
        }

        /* increment pen position */
        *w += faces[fontid].xadvance[code];

        /* record current glyph index */
        previous = glyph_index;
    }

//    *w += faces[fontid].xoffset[code] + faces[fontid].gr_glyph[code]->width;
    *h  = top_pixel - bottom_pixel;


    return -1;
}

int ttf_draw(INSTANCE *my, int *params) {
    // HACK, HACK, HAAAACK!
    extern int fntcolor32;
    unsigned char code;

    if (!scr_initialized) {
        return (-1);
    }

    // Load the given path
    if(load_face(string_get(params[0]), params[2], 0) == false) {
        return -1;
    }

    uint16_t pen_x = 0;
    uint16_t pen_y = 0;

    FT_Bool use_kerning = FT_HAS_KERNING(faces[0].face);
    FT_UInt previous    = 0;

    const char *text = string_get(params[1]);
    uint32_t num_glyphs = strlen(text);

    FT_Vector pos[num_glyphs];   /* glyph position */

    // TODO: This can probably be moved into get_text_size
    for (uint32_t n = 0; n < num_glyphs; n++) {
        // Character code in CP850 encoding
        code = (unsigned char)text[n];

        FT_UInt glyph_index = FT_Get_Char_Index(faces[0].face, cp850_to_utf8[(unsigned char)text[n]]);

        /* retrieve kerning distance and move pen position */
        if (use_kerning && previous && glyph_index) {
            FT_Vector  delta;

            FT_Get_Kerning(faces[0].face, previous, glyph_index, FT_KERNING_DEFAULT, &delta);

            pen_x += (delta.x >> 6);
        }

        /* store current pen position */
        pos[n].x = pen_x;
        pos[n].y = pen_y;

        /* increment pen position */
        pen_x += faces[0].xadvance[code];

        /* record current glyph index */
        previous = glyph_index;
    }

    // Decrease reference count, now that we're done with it
    string_discard(params[1]);

    // Determine the size of the text's bounding box
    uint32_t w, h;
    int32_t baseline_y;
    get_text_size(text, 0, &w, &h, &baseline_y);

    // This GRAPH will hold the alpha channel for the text
    GRAPH *alpha_graph = bitmap_new(0, w, h, 8);
    if (!alpha_graph) {
        if(debug) {
            PXTRTM_LOGERROR("ERROR: Could not create alpha GRAPH\n");
        }
        FT_Done_Face(faces[0].face);
        return -1;
    }
    gr_clear(alpha_graph);

    // Draw the text into the GRAPH
    for (int16_t n = 0; n < num_glyphs; n++) {
        FT_Vector  pen;

        pen.x = pos[n].x;
        pen.y = pos[n].y;

        // Character code in CP850 encoding
        code = (unsigned char)text[n];

        if(faces[0].gr_glyph[code]) {
            int x = pen.x + faces[0].xoffset[code];
            int y = pen.y + h - faces[0].yoffset[code] - baseline_y;
            gr_blit(alpha_graph, NULL, x, y, 0,  255,  255,  255, faces[0].gr_glyph[code]);
        }
    }

    // Finally, create the destination 32bpp GRAPH with the same size as alpha_graph
    GRAPH *graph = bitmap_new(0, alpha_graph->width, alpha_graph->height, 32);
    gr_clear_as(graph, fntcolor32);

    // Set the contents of alpha_graph as the alpha channel for graph
    uint8_t *graph_pos = graph->data;
    uint8_t *alpha_pos = graph->data;

    for(uint32_t y = 0; y < graph->height; y++) {
        for(uint32_t x = 0; x < graph->width; x++) {
            graph_pos = ((uint8_t *)graph->data) + graph->pitch * y + x * graph->format->depthb + 3;
            alpha_pos = ((uint8_t *)alpha_graph->data) + alpha_graph->pitch * y + x * alpha_graph->format->depthb;
            *graph_pos = *alpha_pos;
        }
    }

    // Everything correct -> Add the graph to the system library
    graph->code = bitmap_next_code();
    bitmap_destroy(alpha_graph);
    grlib_add_map(0, graph);

    // We're done with the font face, unload it
    FT_Done_Face(faces[0].face);

    return graph->code;
}

int print_code(INSTANCE *my, int * params) {
    const char *text = string_get(params[0]);

    printf("Got '%s'\n", text);
    printf("Length: %zu\n\n", strlen(text));
    for(int n=0; n<strlen(text); n++) {
        printf("%c ; %d\n", text[n], (unsigned char)text[n]);
    }
    string_discard(params[0]);

    return 0;
}

void __pxtexport(mod_ttf, module_initialize)() {
    int error = FT_Init_FreeType(&library);
    if (error) {
        PXTRTM_LOGERROR("ERROR: Could not start Freetype library\n");
    }

    for(int32_t i=0; i<MAX_FACES; i++) {
        faces[i].loaded = false;
    }
}

void __pxtexport(mod_ttf, module_finalize)() {
    FT_Done_FreeType(library);
}

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
#include <bgddl.h>
#include <bgdrtm.h>
#include <libgrbase.h>
#include <g_video.h>
#include <xstrings.h>
#include "mod_map.h"

#ifndef __MONOLITHIC__
#include "mod_ttf_symbols.h"
#endif

#define MAX_GLYPHS 32

typedef struct {
    FT_Face   face;
    FT_Glyph  glyphs[255];
    GRAPH    *gr[255];
} FONTFACE;

FONTFACE faces[255];

/* ---------------------- */
FT_Library library;
/* ---------------------- */

bool load_face(const char *path, uint16_t size, uint8_t n) {
    int error = FT_New_Face(library, path, 0, &faces[n].face);
    if(error) {
        if(debug) {
            BGDRTM_LOGERROR("ERROR: Could not load font face %s\n", path);
        }
        return false;
    }

    if(FT_HAS_VERTICAL(faces[n].face)) {
        if(debug) {
            BGDRTM_LOGERROR("ERROR: Vertical font faces are not supported\n");
        }
        FT_Done_Face(faces[n].face);
        return false;
    }

    if(!FT_IS_SCALABLE(faces[n].face)) {
        if(debug) {
            BGDRTM_LOGERROR("ERROR: Non-scallable font faces are not supported\n");
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

    return true;
}

int ttf_load(INSTANCE *my, int *params) {
    int error;
    // HACK, HACK, HAAAACK!
    extern int fntcolor32;

    if (!scr_initialized) {
        return (-1);
    }

    // Load the given path
    if(load_face(string_get(params[0]), 40, 0) == false) {
        return -1;
    }

    uint16_t pen_x = 0;
    uint16_t pen_y = 0;

    FT_UInt num_glyphs  = 0;
    FT_Bool use_kerning = FT_HAS_KERNING(faces[0].face);
    FT_UInt previous    = 0;

    FT_Glyph      glyphs[MAX_GLYPHS];   /* glyph image    */
    FT_Vector     pos   [MAX_GLYPHS];   /* glyph position */

    const char *text = string_get(params[1]);
    uint16_t num_chars = strlen(text);

    for (uint8_t n = 0; n < num_chars; n++) {
        /* convert character code to glyph index */
        FT_UInt glyph_index = FT_Get_Char_Index(faces[0].face, text[n]);

        /* retrieve kerning distance and move pen position */
        if (use_kerning && previous && glyph_index) {
            FT_Vector  delta;

            FT_Get_Kerning(faces[0].face, previous, glyph_index, FT_KERNING_DEFAULT, &delta);

            pen_x += delta.x >> 6;
        }

        /* store current pen position */
        pos[num_glyphs].x = pen_x;
        pos[num_glyphs].y = pen_y;

        /* load glyph image into the slot without rendering */
        error = FT_Load_Glyph(faces[0].face, glyph_index, FT_LOAD_DEFAULT);
        if (error) {
            continue;  /* ignore errors, jump to next glyph */
        }

        /* extract glyph image and store it in our table */
        error = FT_Get_Glyph(faces[0].face->glyph, &glyphs[num_glyphs]);
        if (error) {
            continue;  /* ignore errors, jump to next glyph */
        }

        /* increment pen position */
        pen_x += faces[0].face->glyph->advance.x >> 6;

        /* record current glyph index */
        previous = glyph_index;

        /* increment number of glyphs */
        num_glyphs++;
    }

    // Decrease reference count, now that we're done with it
    string_discard(params[1]);

    // Create the graph holding the text
    GRAPH *alpha_graph = NULL;

    // Make the box as high as needed so that any text fits in
    uint32_t highest_y = FT_MulFix(abs(faces[0].face->ascender), faces[0].face->size->metrics.y_scale) >> 6;
    uint32_t baseline_y = FT_MulFix(abs(faces[0].face->descender), faces[0].face->size->metrics.y_scale) >> 6;

    // Draw the text into the GRAPH
    for (int16_t n = num_glyphs-1; n >= 0; n-- ) {
        FT_Glyph   image;
        FT_Vector  pen;

        image = glyphs[n];

        pen.x = pos[n].x;
        pen.y = pos[n].y;

        error = FT_Glyph_To_Bitmap(&image, FT_RENDER_MODE_NORMAL, &pen, 0);
        if ( !error ) {
            FT_BitmapGlyph bit = (FT_BitmapGlyph)image;
            if( bit->bitmap.width > 0) {
                if(alpha_graph == NULL) {
                    alpha_graph = bitmap_new(0,
                                             pen.x + bit->bitmap.width + bit->left,
                                             highest_y + baseline_y,
                                             8);
                    if (!alpha_graph) {
                        if(debug) {
                            BGDRTM_LOGERROR("ERROR: Could not create alpha GRAPH\n");
                        }
                        FT_Done_Face(faces[0].face);
                        return -1;
                    }

                    // Clear the graph (make all the points transparent)
                    gr_clear(alpha_graph);
                }

                // Create a 8bpp graph for the glyph
                GRAPH *glyph_graph = bitmap_new_ex(0,
                                                   bit->bitmap.width, bit->bitmap.rows, 8,
                                                   bit->bitmap.buffer, bit->bitmap.pitch);
                gr_blit(alpha_graph, NULL,
                        pen.x + bit->left + glyph_graph->width/2.0,
                        pen.y + alpha_graph->height - bit->top + glyph_graph->height/2.0 - baseline_y,
                        0,  255,  255,  255, glyph_graph);

                bitmap_destroy(glyph_graph);
            }

            FT_Done_Glyph( image );
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

void __bgdexport(mod_ttf, module_initialize)() {
    int error = FT_Init_FreeType(&library);
    if (error) {
        BGDRTM_LOGERROR("ERROR: Could not start Freetype library\n");
    }
}

void __bgdexport(mod_ttf, module_finalize)() {
    FT_Done_FreeType(library);
}

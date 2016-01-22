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

/* Freetype 2 */
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

/* SDL2 (to try to get screen DPI) */
#include <SDL.h>

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
FT_UInt       glyph_index;
FT_Bool       use_kerning;
FT_UInt       previous;

FT_Glyph      glyphs[MAX_GLYPHS];   /* glyph image    */
FT_Vector     pos   [MAX_GLYPHS];   /* glyph position */
FT_UInt       num_glyphs;

/* ---------------------- */
FT_Library library;
/* ---------------------- */

void compute_string_bbox(FT_BBox *abbox) {
    FT_BBox  bbox;
    FT_BBox  glyph_bbox;


    /* initialize string bbox to "empty" values */
    bbox.xMin = bbox.yMin =  32000;
    bbox.xMax = bbox.yMax = -32000;

    /* for each glyph image, compute its bounding box, */
    /* translate it, and grow the string bbox          */
    for (uint8_t n = 0; n < num_glyphs; n++) {
        FT_Glyph_Get_CBox(glyphs[n], ft_glyph_bbox_pixels, &glyph_bbox);

        glyph_bbox.xMin += pos[n].x;
        glyph_bbox.xMax += pos[n].x;
        glyph_bbox.yMin += pos[n].y;
        glyph_bbox.yMax += pos[n].y;

        if (glyph_bbox.xMin < bbox.xMin) {
            bbox.xMin = glyph_bbox.xMin;
        }

        if (glyph_bbox.yMin < bbox.yMin) {
            bbox.yMin = glyph_bbox.yMin;
        }

        if (glyph_bbox.xMax > bbox.xMax) {
            bbox.xMax = glyph_bbox.xMax;
        }

        if (glyph_bbox.yMax > bbox.yMax) {
            bbox.yMax = glyph_bbox.yMax;
        }
    }

    /* check that we really grew the string bbox */
    if (bbox.xMin > bbox.xMax) {
        bbox.xMin = 0;
        bbox.yMin = 0;
        bbox.xMax = 0;
        bbox.yMax = 0;
    }

    /* return string bbox */
    *abbox = bbox;
}

int ttf_load(INSTANCE *my, int *params) {
    if (!scr_initialized) {
        return (-1);
    }

    // Load the given path
    FT_Face face;
    const char *path = string_get(params[0]);
    int error = FT_New_Face( library, path, 0, &face );
    string_discard(params[0]);
    if(error) {
        if(debug) {
            BGDRTM_LOGERROR("ERROR: Could not load font face %s\n", path);
        }
        return -1;
    }

    if(FT_HAS_VERTICAL(face)) {
        if(debug) {
            BGDRTM_LOGERROR("ERROR: Vertical font faces are not supported\n");
        }
        FT_Done_Face(face);
        return -1;
    }

    // Try to determine the DPI of the display the PixTudio window is at
    float hdpi = 100., vdpi = 100.;
    if(window) {
        int nDisplay = SDL_GetWindowDisplayIndex(window);
        if(nDisplay >= 0) {
            if(SDL_GetDisplayDPI(nDisplay, NULL, &hdpi, &vdpi) < 0) {
                // Could not get DPI info, use a default value
                hdpi = vdpi = 100.;
            }
        }
    }

    // Set the character size to 16pt
    error = FT_Set_Char_Size(face, 0, 16*64, (int)hdpi, (int)vdpi);
    if(error) {
        FT_Done_Face(face);
        return -1;
    }

    ////////////////////////////////////////////
    uint16_t pen_x = 0;   /* start at (0,0) */
    uint16_t pen_y = 0;

    num_glyphs  = 0;
    use_kerning = FT_HAS_KERNING(face);
    previous    = 0;

    const char *text = string_get(params[1]);
    uint16_t num_chars = strlen(text);

    for (uint8_t n = 0; n < num_chars; n++) {
        /* convert character code to glyph index */
        glyph_index = FT_Get_Char_Index(face, text[n]);

        /* retrieve kerning distance and move pen position */
        if (use_kerning && previous && glyph_index) {
            FT_Vector  delta;

            FT_Get_Kerning(face, previous, glyph_index,
                           FT_KERNING_DEFAULT, &delta);

            pen_x += delta.x >> 6;
        }

        /* store current pen position */
        pos[num_glyphs].x = pen_x;
        pos[num_glyphs].y = pen_y;

        /* load glyph image into the slot without rendering */
        error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
        if (error) {
            continue;  /* ignore errors, jump to next glyph */
        }

        /* extract glyph image and store it in our table */
        error = FT_Get_Glyph(face->glyph, &glyphs[num_glyphs]);
        if (error) {
            continue;  /* ignore errors, jump to next glyph */
        }

        /* increment pen position */
        pen_x += face->glyph->advance.x >> 6;

        /* record current glyph index */
        previous = glyph_index;

        /* increment number of glyphs */
        num_glyphs++;
    }

    // Decrease reference count, now that we're done with it
    //string_discard(params[1]);

    // Get the bounding box size
    FT_BBox string_bbox;
    compute_string_bbox(&string_bbox);

    printf("Size: %ldx%ld\n", string_bbox.xMax - string_bbox.xMin, string_bbox.yMax - string_bbox.yMin);

    // Create the graph holding the text
    int graphid  = bitmap_next_code();
    GRAPH *graph = bitmap_new(graphid,
                              string_bbox.xMax - string_bbox.xMin,
                              string_bbox.yMax - string_bbox.yMin,
                              8);
    if (!graph) {
        if(debug) {
            BGDRTM_LOGERROR("ERROR: Could not create GRAPH\n");
        }
        FT_Done_Face(face);
        return -1;
    }
    // Clear the graph (make all the points transparent)
    gr_clear(graph);

    // Draw the text into the GRAPH
    for (uint8_t n = 0; n < num_glyphs; n++ ) {
        FT_Glyph   image;
        FT_Vector  pen;

        image = glyphs[n];

        pen.x = pos[n].x;
        pen.y = pos[n].y;

        error = FT_Glyph_To_Bitmap(&image, FT_RENDER_MODE_NORMAL, &pen, 0);
        if ( !error ) {
            FT_BitmapGlyph bit = (FT_BitmapGlyph)image;
            if( bit->bitmap.width > 0) {
                GRAPH *glyph_graph = bitmap_new_ex(-1,
                                                   bit->bitmap.width, bit->bitmap.rows, 8,
                                                   bit->bitmap.buffer, bit->bitmap.pitch);

                printf("Char: '%c', (%f, %f)\n", text[n], pen.x + bit->left + glyph_graph->width / 2.0, bit->bitmap.rows + bit->top + glyph_graph->height / 2.0);
                gr_blit(graph, NULL, pen.x + bit->left + glyph_graph->width / 2.0, bit->bitmap.rows - bit->top + glyph_graph->height / 2.0,     0,  255,  255,  255, glyph_graph);

                /*my_draw_bitmap( bit->bitmap,
                                bit->left,
                                my_target_height - bit->top );*/

                bitmap_destroy(glyph_graph);
            }

            FT_Done_Glyph( image );
        }
    }

    string_discard(params[1]);

    // Eeverything correct -> Add the graph to the system library
    grlib_add_map(0, graph);

    // We're done with the font face
    FT_Done_Face(face);

    return graphid;
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

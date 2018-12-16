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

#include <strings.h>
#include <files.h>
#include <pxtrtm.h>
#ifndef NO_JPEG
#include <jpeglib.h>
#endif

#include "mod_map.h"
#include "g_bitmap.h"

/* --------------------------------------------------------------------------- */

GRAPH *gr_read_jpg(const char *filename) {
#ifdef NO_JPEG
	if(debug) {
		PXTRTM_LOGERROR("Could not load '%s', JPEG loading not compiled in\n", filename);
	}
	return NULL
#else
    // First of all, we read the whole JPEG file into memory
    file *infd = file_open(filename, "rb");
    if(! infd) {
        PXTRTM_LOGERROR("Could not open '%s'\n", filename);
        return NULL;
    }

    // Get the size of the file to construct an in-memory buffer
    // with all its data
    // This is kind of overkill, we should be reading one line at
    // a time, at most.
    int size = file_size(infd);
    uint8_t *data = (uint8_t *)malloc((size_t)size);
    if(!data) {
        PXTRTM_LOGERROR("Could not allcoate memory for '%s'\n", filename);
        file_close(infd);
        return NULL;
    }
    int read = file_read(infd, data, size);
    if(read != size) {
        PXTRTM_LOGERROR("Error reading data from '%s'\n", filename);
        PXTRTM_LOGERROR("expected to read %d bytes and got %d\n", size, read);
        file_close(infd);
        free(data);
        return NULL;
    }

    file_close(infd);

    // We will now prepare the information needed to decode this data
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // TODO: Replace this error handler for our own
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // Set the data source to a memory buffer
    jpeg_mem_src(&cinfo, data, (unsigned long)size);
    // Check that the JPG image header is valid
    if(jpeg_read_header(&cinfo, 1) != 1) {
        // We only print an error if the user set the debugging flag
        if(debug) {
            PXTRTM_LOGERROR("'%s' does not have a valid JPG header, not loading\n", filename);
        }

        free(data);
        return NULL;
    }

    // By calling jpeg_start_decompress, you populate cinfo
    // and can then allocate your output bitmap buffers for
    // each scanline.
    jpeg_start_decompress(&cinfo);

    // Create a 32bpp output graph
    // 24bpp should be fine, but PixTudio cannot handle that...
    cinfo.out_color_space = JCS_EXT_BGRA;
    GRAPH *gr = bitmap_new(0, cinfo.output_width, cinfo.output_height, 32);

    // Read the data line by line
    while(cinfo.output_scanline < cinfo.output_height) {
        unsigned char *buffer_array[1];
        buffer_array[0] = (uint8_t *)gr->data + (cinfo.output_scanline) * gr->pitch;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }

    // Free resource
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(data);

    // Happily return the GRAPH
    gr->needs_texture_update = 1;
    return gr;
#endif
}

/* --------------------------------------------------------------------------- */

int gr_load_jpg(const char *mapname) {
    GRAPH *gr = gr_read_jpg(mapname);
    if (!gr) {
        return 0;
    }
    gr->code = bitmap_next_code();
    grlib_add_map(0, gr);
    return gr->code;
}

/* --------------------------------------------------------------------------- */

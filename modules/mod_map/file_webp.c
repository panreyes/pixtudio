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
#include <webp/decode.h>

#include "mod_map.h"
#include "g_bitmap.h"

/* --------------------------------------------------------------------------- */

GRAPH *gr_read_webp(const char *filename) {
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
    file_close(infd);
    if(read != size) {
        PXTRTM_LOGERROR("Error reading data from '%s'\n", filename);
        PXTRTM_LOGERROR("expected to read %d bytes and got %d\n", size, read);
        free(data);
        return NULL;
    }

    // We will now prepare the information needed to decode the graphic in data
    int width, height;
    int success = WebPGetInfo((const uint8_t*)data, (size_t)size, &width, &height);
    if(!success) {
        PXTRTM_LOGERROR("Error reading info from '%s'\n", filename);
        free(data);
        return NULL;
    }

    // Create a 32bpp output graph
    // 24bpp should be fine, but PixTudio cannot handle that...
    GRAPH *gr = bitmap_new(0, width, height, 32);
    if(!gr) {
        PXTRTM_LOGERROR("Could not create bitmap for reading '%s'\n", filename);
        free(data);
        return NULL;
    }

    // Decode the webp image into the GRAPH
    if(WebPDecodeBGRAInto((const uint8_t*)data, (size_t)size, (uint8_t *)gr->data,
    	                  gr->pitch * height, gr->pitch) == NULL) {
        PXTRTM_LOGERROR("Could not decode bitmap for '%s'\n", filename);
        bitmap_destroy(gr);
        free(data);
        return NULL;
    }

    // Free the file contents from memory
    free(data);

    // Happily return the GRAPH
    gr->needs_texture_update = 1;
    return gr;
}

/* --------------------------------------------------------------------------- */

int gr_load_webp(const char *mapname) {
    GRAPH *gr = gr_read_webp(mapname);
    if (!gr) {
        return 0;
    }
    gr->code = bitmap_next_code();
    grlib_add_map(0, gr);
    return gr->code;
}

/* --------------------------------------------------------------------------- */

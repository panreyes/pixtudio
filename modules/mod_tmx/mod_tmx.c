#include <stdlib.h>
#include <string.h>
#include <tmx.h>

#include "pxtdl.h"

#include "files.h"
#include "xctype.h"
#include "xstrings.h"

#include "dlvaracc.h"

#include "mod_tmx.h"

#ifndef __MONOLITHIC__
#include "mod_tmx_symbols.h"
#endif


int mod_tmx_load_map(INSTANCE * my, int * params) {
    const char *filename;
    if ( ! (filename = string_get(params[0])) ) {
        return 0;
    }
    tmx_map *map = tmx_load(filename);
    if (!map) {
        tmx_perror("Cannot load map");
        return -1;
    }
    return (int)map;
}

int mod_tmx_get_map_width(INSTANCE * my, int * params) {
    tmx_map * map = (tmx_map *)params[0];
    return map->width;
}

int mod_tmx_get_map_height(INSTANCE * my, int * params) {
    tmx_map * map = (tmx_map *)params[0];
    return map->height;
}

int mod_tmx_unload_map(INSTANCE * my, int * params) {
    tmx_map * map = (tmx_map *)params[0];
    tmx_map_free(map);
}

void* tex_loader(const char *path) {
}

void __pxtexport( mod_tmx, module_initialize )() {
}

void __pxtexport( mod_tmx, module_finalize )() {
}

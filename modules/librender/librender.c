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

/* --------------------------------------------------------------------------- */

#include "pxtdl.h"
#include "dlvaracc.h"

#define __LIB_RENDER
#include "librender.h"

#ifndef __MONOLITHIC__
#include "librender_symbols.h"
#endif

/* --------------------------------------------------------------------------- */
/* Son las variables que se desea acceder.                           */
/* El interprete completa esta estructura, si la variable existe.    */
/* (usada en tiempo de ejecucion)                                    */

DLVARFIXUP __pxtexport(librender, globals_fixup)[] = {
    /* Nombre de variable global, puntero al dato, tamaño del elemento, cantidad de elementos */
    {"fps", NULL, -1, -1},        {"speed_gauge", NULL, -1, -1},  {"frame_time", NULL, -1, -1},

    {"scale_mode", NULL, -1, -1}, {"restore_type", NULL, -1, -1}, {"dump_type", NULL, -1, -1},

    {"fading", NULL, -1, -1},     {"alpha_steps", NULL, -1, -1},

    {NULL, NULL, -1, -1}};

DLVARFIXUP __pxtexport(librender, locals_fixup)[] = {
    {"ctype", NULL, -1, -1},   // 0            CTYPE               0
    {"cnumber", NULL, -1, -1}, // 1            CNUMBER             1

    {"x", NULL, -1, -1},               // 2            COORDX              2
    {"y", NULL, -1, -1},               // 3            COORDY              3
    {"z", NULL, -1, -1},               // 4            COORDZ              4
    {"file", NULL, -1, -1},            // 5            FILEID              5
    {"graph", NULL, -1, -1},           // 6            GRAPHID             6
    {"size", NULL, -1, -1},            // 7            GRAPHSIZE           7
    {"angle", NULL, -1, -1},           // 8            ANGLE               8
    {"flags", NULL, -1, -1},           // 9            FLAGS               9
    {"alpha", NULL, -1, -1},           // 10           ALPHA               10
    {"palette", NULL, -1, -1},         // 11           PALETTEID           11
    {"region", NULL, -1, -1},          // 12           REGIONID            12
    {"resolution", NULL, -1, -1},      // 13           RESOLUTION          13
    {"size_x", NULL, -1, -1},          // 14           GRAPHSIZEX          14
    {"size_y", NULL, -1, -1},          // 15           GRAPHSIZEY          15
    {"blendop", NULL, -1, -1},         // 16           BLENDOP             16
    {"collision_graph", NULL, -1, -1}, // 17           COLLISIONGRAPHID    17

    {"_render_reserved_.object_id", NULL, -1, -1}, // 18           OBJECTID            18
    {"_render_reserved_.graph_ptr", NULL, -1, -1}, // 19           GRAPHPTR            19

    {"_render_reserved_._saved_.x", NULL, -1, -1},       // 20           SAVED_COORDX        20
    {"_render_reserved_._saved_.y", NULL, -1, -1},       // 21           SAVED_COORDY        21
    {"_render_reserved_._saved_.z", NULL, -1, -1},       // 22           SAVED_COORDZ        22
    {"_render_reserved_._saved_.file", NULL, -1, -1},    // 23           SAVED_FILEID        23
    {"_render_reserved_._saved_.graph", NULL, -1, -1},   // 24           SAVED_GRAPHID       24
    {"_render_reserved_._saved_.size", NULL, -1, -1},    // 25           SAVED_GRAPHSIZE     25
    {"_render_reserved_._saved_.angle", NULL, -1, -1},   // 26           SAVED_ANGLE         26
    {"_render_reserved_._saved_.flags", NULL, -1, -1},   // 27           SAVED_FLAGS         27
    {"_render_reserved_._saved_.alpha", NULL, -1, -1},   // 28           SAVED_ALPHA         28
    {"_render_reserved_._saved_.palette", NULL, -1, -1}, // 29           SAVED_PALETTE       29
    {"_render_reserved_._saved_.size_x", NULL, -1, -1},  // 30           SAVED_GRAPHSIZEX    30
    {"_render_reserved_._saved_.size_y", NULL, -1, -1},  // 31           SAVED_GRAPHSIZEY    31
    {"_render_reserved_._saved_.blendop", NULL, -1, -1}, // 32           SAVED_BLENDOP       32
    {"_render_reserved_._saved_.centerx", NULL, -1, -1}, // 33           SAVED_COORDX        33
    {"_render_reserved_._saved_.centery", NULL, -1, -1}, // 34           SAVED_COORDY        34

    {"reserved.status", NULL, -1, -1}, // 35           STATUS              35

    {"modr", NULL, -1, -1}, // 36           MODR                36
    {"modg", NULL, -1, -1}, // 37           MODG                37
    {"modb", NULL, -1, -1}, // 38           MODB                38

    {NULL, NULL, -1, -1}};

/* --------------------------------------------------------------------------- */

/* Bigest priority first execute
   Lowest priority last execute */

HOOK __pxtexport(librender,
                 handler_hooks)[] = {{9500, gr_wait_frame}, {9000, gr_draw_frame}, {0, NULL}};

/* --------------------------------------------------------------------------- */

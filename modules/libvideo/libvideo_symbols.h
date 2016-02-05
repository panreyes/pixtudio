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

#ifndef __VIDEO_SYMBOLS_H
#define __VIDEO_SYMBOLS_H

#include <pxtdl.h>
#include "g_video_constants.h"

/* --------------------------------------------------------------------------- */
/* Global vars (compile time) */

char __pxtexport( libvideo, globals_def )[] =
    "graph_mode = 0;\n"
    "full_screen = 0;\n"
    "scale_resolution = -1;\n"
    "scale_resolution_aspectratio = 0;\n"
    "BYTE scale_quality = 1;\n";

/* --------------------------------------------------------------------------- */

char *__pxtexport( libvideo, module_dependencies )[] = {
    "libgrbase",
    NULL
};

DLCONSTANT  __pxtexport( libvideo, constants_def )[] = {
    { "MODE_WINDOW"         , TYPE_DWORD    , MODE_WINDOW           },
    { "MODE_FULLSCREEN"     , TYPE_DWORD    , MODE_FULLSCREEN       },

    { "MODE_WAITVSYNC"      , TYPE_DWORD    , MODE_WAITVSYNC        },
    { "WAITVSYNC"           , TYPE_DWORD    , MODE_WAITVSYNC        },

    { "MODE_8BITS"          , TYPE_DWORD    , 8                     },
    { "MODE_16BITS"         , TYPE_DWORD    , 16                    },
    { "MODE_32BITS"         , TYPE_DWORD    , 32                    },

    { "MODE_8BPP"           , TYPE_DWORD    , 8                     },
    { "MODE_16BPP"          , TYPE_DWORD    , 16                    },
    { "MODE_32BPP"          , TYPE_DWORD    , 32                    },

    { "MODE_MODAL"          , TYPE_DWORD    , MODE_MODAL            },  /* GRAB INPUT */
    { "MODE_FRAMELESS"      , TYPE_DWORD    , MODE_FRAMELESS        },  /* FRAMELESS window */

    { "SCALE_NONE"          , TYPE_DWORD    , SCALE_NONE            },

    { "SRO_NORMAL"          , TYPE_DWORD    , SRO_NORMAL            },
    { "SRO_LEFT"            , TYPE_DWORD    , SRO_LEFT              },
    { "SRO_DOWN"            , TYPE_DWORD    , SRO_DOWN              },
    { "SRO_RIGHT"           , TYPE_DWORD    , SRO_RIGHT             },

    { "SRA_STRETCH"         , TYPE_DWORD    , SRA_STRETCH           },
    { "SRA_PRESERVE"        , TYPE_DWORD    , SRA_PRESERVE          },

    { "SCALE_NEAREST"       , TYPE_BYTE     , 0                     },
    { "SCALE_LINEAR"        , TYPE_BYTE     , 1                     },

    { NULL                  , 0             , 0                     }
} ;

#ifndef __PXTB__
DLVARFIXUP __pxtexport( libvideo, globals_fixup )[] = {
    /* The compiler will fill in the gaps */
    { "graph_mode" , NULL, -1, -1 },
    { "full_screen" , NULL, -1, -1 },
    { "scale_resolution", NULL, -1, -1 },
    { "scale_resolution_aspectratio", NULL, -1, -1 },
    { "scale_quality", NULL, -1, -1 },

    { NULL , NULL, -1, -1 }
};

extern void __pxtexport( libvideo, module_initialize )();
extern void __pxtexport( libvideo, module_finalize )();
#endif

#endif

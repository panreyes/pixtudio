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

#ifndef __BLIT_SYMBOLS_H
#define __BLIT_SYMBOLS_H

#include <pxtdl.h>
#include "g_blitflags.h"

DLCONSTANT __pxtexport( libblit, constants_def )[] =
{
    /* gr_blit flags */
    { "B_HMIRROR"           , TYPE_DWORD, B_HMIRROR     },
    { "B_VMIRROR"           , TYPE_DWORD, B_VMIRROR     },
    { "B_ALPHA"             , TYPE_DWORD, B_ALPHA       },
    { "B_ABLEND"            , TYPE_DWORD, B_ABLEND      },
    { "B_SBLEND"            , TYPE_DWORD, B_SBLEND      },
    { "B_MBLEND"            , TYPE_DWORD, B_MBLEND      },
    { "B_NOCOLORKEY"        , TYPE_DWORD, B_NOCOLORKEY  },

    { NULL                  , 0         ,  0            }
} ;

#endif

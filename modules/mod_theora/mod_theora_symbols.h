/*
 *  Copyright (C) 2015 Joseba Garcí­a Echebarria. All rights reserved.
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

#ifndef __MODTHEORA_SYMBOLS_H
#define __MODTHEORA_SYMBOLS_H

#include <bgddl.h>

#ifdef __PXTB__
DLSYSFUNCS __bgdexport( mod_theora, functions_exports )[] =
{
    {"VIDEO_PLAY"                  , "S"    , TYPE_DWORD , NULL  },
    {"VIDEO_STOP"                  , ""     , TYPE_DWORD , NULL  },
    {"VIDEO_PAUSE"                 , ""     , TYPE_DWORD , NULL  },
    {"VIDEO_IS_PLAYING"            , ""     , TYPE_DWORD , NULL  },
    {"VIDEO_SET_VOLUME"            , "I"    , TYPE_DWORD , NULL  },
    { NULL                         , NULL   , 0          , NULL  }
};
#else
extern DLSYSFUNCS __bgdexport( mod_theora, functions_exports )[];
extern HOOK __bgdexport( mod_theora, handler_hooks )[];
extern void __bgdexport( mod_theora, module_initialize )();
extern void __bgdexport( mod_theora, module_finalize )();
extern char __bgdexport( mod_theora, modules_dependency )[];
#endif

#endif

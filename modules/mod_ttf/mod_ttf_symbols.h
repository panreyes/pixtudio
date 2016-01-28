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

#pragma once

#include <bgddl.h>

#ifndef __PXTB__
extern int ttf_load(INSTANCE *my, int * params);

extern void __bgdexport( mod_ttf, module_initialize )();
extern void __bgdexport( mod_ttf, module_finalize )();
#endif

DLSYSFUNCS __bgdexport( mod_ttf, exported_functions )[] = {
    FUNC( "TTF_LOAD"                   , "SS"   , TYPE_DWORD , ttf_load       ),
    FUNC( NULL                         , NULL   , 0          , NULL           )
};

char * __bgdexport( mod_ttf, module_dependencies )[] = {
    "libgrbase",
    "libvideo",
    NULL
};
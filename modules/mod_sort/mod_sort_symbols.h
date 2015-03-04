/*
 *  Copyright Â© 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright Â© 2002-2006 Fenix Team (Fenix)
 *  Copyright Â© 1999-2002 JosÃ© Luis CebriÃ¡n PagÃ¼e (Fenix)
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

#ifndef __MODSORT_SYMBOLS_H
#define __MODSORT_SYMBOLS_H

#include <bgddl.h>

#ifdef __BGDC__
DLSYSFUNCS  __bgdexport( mod_sort, functions_exports )[] =
{
    /* Funciones sort */
    { "QUICKSORT"   , "PIIIBB", TYPE_INT    , 0 },
    { "KSORT"       , "V++V++", TYPE_INT    , 0 },
    { "KSORT"       , "V++V++I", TYPE_INT   , 0 },
    { "SORT"        , "V++I"  , TYPE_INT    , 0 },
    { "SORT"        , "V++"   , TYPE_INT    , 0 },
    { 0             , 0       , 0           , 0 }
};
#else
extern DLSYSFUNCS  __bgdexport( mod_sort, functions_exports )[];
#endif

#endif

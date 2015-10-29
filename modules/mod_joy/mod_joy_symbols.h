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

#ifndef __MODJOY_SYMBOLS_H
#define __MODJOY_SYMBOLS_H

#include <bgddl.h>

#ifdef __PXTB__
DLSYSFUNCS  __bgdexport( mod_joy, functions_exports )[] =
{
    { "JOY_AXES"            , ""      , TYPE_INT    , 0 },
    { "JOY_AXES"            , "I"     , TYPE_INT    , 0 },
    { "JOY_NUM_AXES"         , ""      , TYPE_INT    , 0 },
    { "JOY_NUM_AXES"         , "I"     , TYPE_INT    , 0 },
    { "JOY_GET_AXIS"         , "I"     , TYPE_INT    , 0 },
    { "JOY_GET_AXIS"         , "II"    , TYPE_INT    , 0 },
    { "JOY_BUTTONS"         , ""      , TYPE_INT    , 0 },
    { "JOY_BUTTONS"         , "I"     , TYPE_INT    , 0 },
    { "JOY_NAME"            , "I"     , TYPE_STRING , 0 },
    { "JOY_NUM_BUTTONS"      , ""      , TYPE_INT    , 0 },
    { "JOY_NUM_BUTTONS"      , "I"     , TYPE_INT    , 0 },
    { "JOY_NUMBER"          , ""      , TYPE_INT    , 0 },
    { "JOY_SELECT"          , "I"     , TYPE_INT    , 0 },
    { "JOY_GET_BUTTON"       , "I"     , TYPE_INT    , 0 },
    { "JOY_GET_BUTTON"       , "II"    , TYPE_INT    , 0 },
    { "JOY_GET_POSITION"     , "I"     , TYPE_INT    , 0 },
    { "JOY_GET_POSITION"     , "II"    , TYPE_INT    , 0 },
    { "JOY_NUM_HATS"         , ""      , TYPE_INT    , 0 },
    { "JOY_NUM_HATS"         , "I"     , TYPE_INT    , 0 },   /* Added by Sandman */
    { "JOY_NUM_BALLS"        , ""      , TYPE_INT    , 0 },
    { "JOY_NUM_BALLS"        , "I"     , TYPE_INT    , 0 },   /* Added by Sandman */
    { "JOY_GET_HAT"          , "I"     , TYPE_INT    , 0 },
    { "JOY_GET_HAT"          , "II"    , TYPE_INT    , 0 },   /* Added by Sandman */
    { "JOY_GET_BALL"         , "IPP"   , TYPE_INT    , 0 },
    { "JOY_GET_BALL"         , "IIPP"  , TYPE_INT    , 0 },   /* Added by Sandman */
    { "JOY_GET_ACCEL"        , "PPP"   , TYPE_INT    , 0 },
    { "JOY_GET_ACCEL"        , "IPPP"  , TYPE_INT    , 0 },
    { 0                     , 0       , 0           , 0 }
};

char * __bgdexport( mod_joy, modules_dependency )[] =
{
    "libjoy",
    NULL
};
#else
extern DLSYSFUNCS  __bgdexport( mod_joy, functions_exports )[];
extern char * __bgdexport( mod_joy, modules_dependency )[];
#endif

#endif

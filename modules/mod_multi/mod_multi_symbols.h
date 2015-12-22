/*
*  Copyright (C) 2013 Joseba GarcÃ­a Etxebarria. All rights reserved.
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

#ifndef __MODMULTIPOINTER_SYMBOLS_H
#define __MODMULTIPOINTER_SYMBOLS_H

#include "bgddl.h"

#ifndef __PXTB__
// Fucntion declarations
extern int modmulti_numpointers(INSTANCE * my, int * params);
extern int modmulti_info(INSTANCE * my, int * params);
extern void parse_input_events();

// Symbol tables
HOOK __bgdexport( mod_multi, handler_hooks )[] = {
    { 5500, parse_input_events                },
    {    0, NULL                              }
} ;
extern void __bgdexport( mod_multi, module_initialize )();
#endif

char * __bgdexport( mod_multi, module_dependencies )[] = {
    "libsdlhandler",
    NULL
};

DLSYSFUNCS __bgdexport( mod_multi, exported_functions )[] = {
    FUNC( "MULTI_NUMPOINTERS" , ""      , TYPE_INT    , modmulti_numpointers ),
    FUNC( "MULTI_INFO"        , "IS"    , TYPE_INT    , modmulti_info ),
    FUNC( 0                   , 0       , 0           , 0 )
};
#endif

/*
 *  Copyright (C) 2016 Pablo Antonio Navarro Reyes <panreyes@panreyes.com>
 *  Copyright (C) 2016 Joseba García Etxebarria <joseba.gar@gmail.com>
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

#ifndef __MODEPIC_SYMBOLS_H
#define __MODEPIC_SYMBOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mod_epic.h"
#include <pxtdl.h>

#ifndef __PXTB__
extern int epic_achievement_unlock(INSTANCE *my, int *params);
extern int epic_init(INSTANCE *my, int *params);
extern int epic_tick(INSTANCE *my, int *params);

extern void __pxtexport( mod_epic, module_initialize )();
extern void __pxtexport( mod_epic, module_finalize )();
extern DLVARFIXUP __pxtexport( mod_epic, globals_fixup )[];
#endif

// Not currently used, but keep it just in case
char __pxtexport( mod_epic, globals_def )[] =
    "\n";

DLSYSFUNCS __pxtexport(mod_epic, exported_functions)[] = {
    FUNC("EPIC_ACHIEVEMENT_UNLOCK"  , "S" , TYPE_INT   , epic_achievement_unlock  ),
	FUNC("EPIC_TICK"                , ""  , TYPE_INT   , epic_tick                ),
    FUNC("EPIC_INIT"                , "SSSSSSSSS" , TYPE_INT   , epic_init         ),
	// Future functions?
    //FUNC("EPIC_ACHIEVEMENT_DELETE"  , "S" , TYPE_INT   , epic_achievement_delete  ),
    //FUNC("EPIC_ACHIEVEMENT_CHECK"   , "S" , TYPE_INT   , epic_achievement_check   ),
    //FUNC("EPIC_IS_SUBSCRIBED_APP"   , "I"  , TYPE_INT  , epic_is_subscribed_app   ),
    FUNC(0, 0, 0, 0)};

// Not currently used, but keep it just in case:
char * __pxtexport( mod_epic, module_dependencies )[] = {
    "libgrbase",
    NULL
};

#endif

#ifdef __cplusplus
}
#endif

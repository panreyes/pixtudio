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

#ifndef __MODSTEAM_SYMBOLS_H
#define __MODSTEAM_SYMBOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pxtdl.h>

#ifndef __PXTB__
extern int steam_achievement_unlock(INSTANCE *my, int *params);
extern int steam_achievement_delete(INSTANCE *my, int *params);
extern int steam_achivement_check(INSTANCE *my, int *params);
extern int steam_achievement_icon_get(INSTANCE *my, int *params);
extern int steam_avatar_get(INSTANCE *my, int *params);

extern void __pxtexport( mod_steam, module_initialize )();
extern void __pxtexport( mod_steam, module_finalize )();
extern DLVARFIXUP __pxtexport( mod_steam, globals_fixup )[];
#endif

char __pxtexport( mod_steam, globals_def )[] =
    "INT steam_appid = 0;\n"
    "STRING steam_username = \"\";\n";

DLSYSFUNCS __pxtexport(mod_steam, exported_functions)[] = {
    FUNC("STEAM_ACHIEVEMENT_UNLOCK", "S",  TYPE_INT, steam_achievement_unlock),
    FUNC("STEAM_ACHIEVEMENT_DELETE", "S",  TYPE_INT, steam_achievement_delete),
    FUNC("STEAM_ACHIEVEMENT_CHECK", "S",  TYPE_INT, steam_achivement_check),
    FUNC("STEAM_ACHIEVEMENT_ICON_GET", "S",  TYPE_INT, steam_achievement_icon_get),
    FUNC("STEAM_AVATAR_GET", "", TYPE_INT, steam_avatar_get),
    FUNC(0, 0, 0, 0)};

char * __pxtexport( mod_steam, module_dependencies )[] = {
    "libgrbase",
    NULL
};

#endif

#ifdef __cplusplus
}
#endif

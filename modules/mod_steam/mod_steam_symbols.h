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
extern int steam_init(INSTANCE *my, int *params);
extern int steam_close(INSTANCE *my, int *params);
extern int steam_username(INSTANCE *my, int *params);
extern int steam_unlock_achievement(INSTANCE *my, int *params);
extern int steam_check_achievement(INSTANCE *my, int *params);
#endif

DLSYSFUNCS __pxtexport(mod_steam, exported_functions)[] = {
    FUNC("STEAM_INIT",  "I", TYPE_INT, steam_init ),
    FUNC("STEAM_CLOSE", "",  TYPE_INT, steam_close),
    FUNC("STEAM_USERNAME", "",  TYPE_STRING, steam_username),
    FUNC("STEAM_UNLOCK_ACHIEVEMENT", "S",  TYPE_INT, steam_unlock_achievement),
    FUNC("STEAM_CHECK_ACHIEVEMENT", "S",  TYPE_INT, steam_check_achievement),
    FUNC(0, 0, 0, 0)};

#endif

#ifdef __cplusplus
}
#endif

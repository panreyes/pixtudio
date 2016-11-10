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

#include "pxtdl.h"
#include "stdio.h"
#include <unistd.h>
#include <pxtrtm.h>
#include <steam_api.h>

#ifndef __MONOLITHIC__
#include "mod_steam_symbols.h"
#endif

/* ---------------------------------------------------------------------- */
extern "C" {
    #include <xstrings.h>
    static int steam_loaded = 0;

    void SteamAPIDebugTextHook(int nSeverity, const char *pchDebugText) {
        printf( "%s\n", pchDebugText );
    }

    int steam_init(INSTANCE *my, int *params) {
        if (!SteamAPI_Init()) {
            fprintf(stderr, "Steam Error: SteamAPI_Init - "
                            "Steam must be running to play this game\n");
            fflush(stderr);

            return 0;
        }

        if(params[0] > 0){
            if (SteamAPI_RestartAppIfNecessary((uint32_t)params[0])) {
                fprintf(stderr, "Steam Error: SteamAPI_RestartAppIfNecessary\n");
                fflush(stderr);
                return 0;
            }
        }

        SteamClient()->SetWarningMessageHook( &SteamAPIDebugTextHook );

        if (!SteamUser()->BLoggedOn()) {
            fprintf(stderr, "Steam Error: Steam user is not logged in - "
                            "Steam user must be logged in to play this game\n");
            fflush(stderr);

            return -1;
        }

        SteamUserStats()->RequestCurrentStats();

        steam_loaded = 1;

        fprintf(stdout, "Steam Init OK.\n");
        fflush(stdout);

        return 0;
    }

    /* ---------------------------------------------------------------------- */

    int steam_username(INSTANCE *my, int *params) {
        const char *name;
        if(steam_loaded) {
            name = SteamFriends()->GetPersonaName();
        } else {
            name = "";
        }

        int string_id = string_new(name);
        string_use(string_id);

        return string_id;
    }

    /* ---------------------------------------------------------------------- */

    int steam_unlock_achievement(INSTANCE *my, int *params) {
        if(!steam_loaded) {
            return -1;
        }

        // TODO: This part is technically right, but won't work unless we
        // process the callback from RequestCurrentState()
        // https://partner.steamgames.com/documentation/bootstrap_achieve
        const char *achievement = string_get(params[0]);
        bool retval = SteamUserStats()->SetAchievement(achievement);
        string_discard(params[0]);
        retval *= SteamUserStats()->StoreStats();

        if(retval == true) {
            return 0;
        } else {
            return -1;
        }
    }

    /* ---------------------------------------------------------------------- */

    int steam_check_achievement(INSTANCE *my, int *params) {
        if(!steam_loaded) {
            return -1;
        }

        const char *achievement = string_get(params[0]);
        bool achieved;
        SteamUserStats()->GetAchievement(achievement, &achieved);
        string_discard(params[0]);

        if(achieved){
            return 1;
        } else {
            return 0;
        }
    }

    /* ---------------------------------------------------------------------- */
    void __pxtexport( mod_steam, module_finalize )() {
        if(!steam_loaded) {
            return;
        }

        SteamAPI_Shutdown();
    }
}

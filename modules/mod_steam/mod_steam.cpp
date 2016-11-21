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
#include <stdlib.h>

#ifndef __MONOLITHIC__
#include "mod_steam_symbols.h"
#endif

// steam_appid is the first global var we'll define
enum {
    STEAM_APPID = 0,
    STEAM_USERNAME
};

/* ---------------------------------------------------------------------- */
extern "C" {
    #include <mod_map.h>
    #include <xstrings.h>
    #include <dlvaracc.h>
    static int steam_loaded = 0;
    static uint32_t steam_appid = 0;

    DLVARFIXUP __pxtexport(mod_steam, globals_fixup)[] = {
        /* Name of global var, pointer to the data, size, #elements */
        {"steam_appid", NULL, -1, -1},
        {"steam_username", NULL, -1, -1},
        {NULL, NULL, -1, -1}
    };

    void SteamAPIDebugTextHook(int nSeverity, const char *pchDebugText) {
        printf( "%s\n", pchDebugText );
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

    int steam_delete_achievement(INSTANCE *my, int *params) {
        if(!steam_loaded) {
            return -1;
        }

        // TODO: This part is technically right, but won't work unless we
        // process the callback from RequestCurrentState()
        // https://partner.steamgames.com/documentation/bootstrap_achieve
        const char *achievement = string_get(params[0]);
        bool retval = SteamUserStats()->ClearAchievement(achievement);
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

    int steam_get_achievement_icon(INSTANCE *my, int *params) {
        if(!steam_loaded) {
            return -1;
        }

        // We get the icon ID for the given achievement,
        // and then use that ID to retrieve the pixels
        const char *achievement = string_get(params[0]);
        int icon_id = SteamUserStats()->GetAchievementIcon(achievement);
        //int icon_id = SteamFriends()->GetLargeFriendAvatar(SteamUser()->GetSteamID());
        string_discard(params[0]);
        if(icon_id <= 0) {
            return -1;
        }

        // Get the image size
        uint32_t width, height;
        bool retval = SteamUtils()->GetImageSize(icon_id, &width, &height);
        if(retval == false) {
            return -1;
        }
        // Allocate the pixel buffer and fill it with the icon data
        size_t size = 4 * height * width * sizeof(uint8_t);
        uint8_t *rgba_data = (uint8_t *)malloc(size);
        retval = SteamUtils()->GetImageRGBA(icon_id, rgba_data, (int)size);
        if(retval == false) {
            free(rgba_data);
            return -1;
        }
        // Convert RGBA -> BGRA
        uint8_t temp_color;
        for (uint32_t i = 0; i < 4*width*height; i += 4) {
            temp_color = rgba_data[i];
            rgba_data[i] = rgba_data[i+2];
            //rgba_data[i+1] = rgba_data[i+1];
            rgba_data[i+2] = temp_color;
            //rgba_data[i+3] = rgba_data[i+3];
            /*rgba_data[i] = 255;       // B
            rgba_data[i+1] = 0;     // G
            rgba_data[i+2] = 0;     // R
            rgba_data[i+3] = 255;     // A*/
        }

        // We create a temporary GRAPH with the pixels
        GRAPH *gr_achievement = bitmap_new_ex(-1, width, height, 32, rgba_data, 4*width);
        if (!gr_achievement) {
            free(rgba_data);
            return -1;
        }

        // Duplicate it so that we don't have to care
        // about freeing the memory later
        GRAPH *gr = bitmap_clone(gr_achievement);
        if(!gr) {
            free(rgba_data);
            return -1;
        }
        bitmap_destroy(gr_achievement);
        free(rgba_data);

        gr->code = bitmap_next_code();
        grlib_add_map(0, gr);
        return gr->code;
    }

    /* ---------------------------------------------------------------------- */

    void __pxtexport(mod_steam, module_initialize)() {
        if (!SteamAPI_Init()) {
            fprintf(stderr, "Steam Error: SteamAPI_Init - "
                            "Steam must be running to play this game\n");
            fflush(stderr);

            return;
        }

        // Get the Steam app ID
        steam_appid = SteamUtils()->GetAppID();
        GLODWORD(mod_steam, STEAM_APPID) = steam_appid;

        if (SteamAPI_RestartAppIfNecessary(steam_appid)) {
            fprintf(stderr, "Steam Error: SteamAPI_RestartAppIfNecessary\n");
            fflush(stderr);

            return;
        }

        SteamClient()->SetWarningMessageHook( &SteamAPIDebugTextHook );

        if (!SteamUser()->BLoggedOn()) {
            fprintf(stderr, "Steam Error: Steam user is not logged in - "
                            "Steam user must be logged in to play this game\n");
            fflush(stderr);

            return;
        }

        // Set the steam username to the global var
        const char *name;
        name = SteamFriends()->GetPersonaName();
        int string_id = string_new(name);
        string_use(string_id);
        GLODWORD(mod_steam, STEAM_USERNAME) = string_id;

        // Request the current player stats
        // TODO: Should we create the callback for this?
        SteamUserStats()->RequestCurrentStats();

        // Mark the process as successful
        steam_loaded = 1;

        fprintf(stdout, "Steam Init OK.\n");
        fflush(stdout);
    }

    /* ---------------------------------------------------------------------- */
    void __pxtexport( mod_steam, module_finalize )() {
        if(!steam_loaded) {
            return;
        }

        SteamAPI_Shutdown();
        string_discard(GLODWORD(mod_steam, STEAM_USERNAME));
    }
}

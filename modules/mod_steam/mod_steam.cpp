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

#include "mod_steam.h"
#include <pxtdl.h>
#include <stdio.h>
#include <unistd.h>
#include <pxtrtm.h>
#include <stdlib.h>
#include <steam_api.h>
#if defined(_WIN32) && defined(__GNUC__)
#include <steam_api_flat.h>
#endif

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
    static uint32_t steam_userid = 0;

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

    /* Create a GRAPH from a steam icon ID */
    GRAPH *gr_from_icon_id(int icon_id) {
        if(icon_id <= 0) {
            return NULL;
        }

        // Get the image size
        uint32_t width, height;
        bool retval = SteamUtils()->GetImageSize(icon_id, &width, &height);
        if(retval == false || width <= 0 || height <= 0) {
            return NULL;
        }

        // Create the GRAPH which will hold the achievement icon
        GRAPH *gr = bitmap_new(0, width, height, 32);
        if(!gr) {
            return NULL;
        }

        size_t size = 4 * height * width * sizeof(uint8_t);
        uint8_t *pixel_data = (uint8_t *)(gr->data);
        retval = SteamUtils()->GetImageRGBA(icon_id, pixel_data, (int)size);
        if(retval == false) {
            bitmap_destroy(gr);
            return NULL;
        }

        // Swap color channels
        uint8_t temp_color;
        for (uint32_t i = 0; i < 4*width*height; i += 4) {
            temp_color = pixel_data[i];
            pixel_data[i] = pixel_data[i+2];    // B channel
            pixel_data[i+2] = temp_color;       // R channel
        }

        // Register the map in the system lib
        gr->code = bitmap_next_code();
        grlib_add_map(0, gr);

        // Mark the graph for texture update
        gr->needs_texture_update = 1;

        return gr;
    }

    /* ---------------------------------------------------------------------- */

    GRAPH *gr_avatar_get(CSteamID user_id, uint8_t avatar_size) {
        // We get the icon ID for the given achievement,
        // and then use that ID to retrieve the pixels
        int icon_id;
        if(avatar_size == AVATAR_SMALL) {
            icon_id = SteamFriends()->GetSmallFriendAvatar(user_id);
        } else if (avatar_size == AVATAR_MEDIUM) {
            icon_id = SteamFriends()->GetMediumFriendAvatar(user_id);
        } else {
            icon_id = SteamFriends()->GetLargeFriendAvatar(user_id);
        }

        if(icon_id <= 0) {
            return NULL;
        }

        // Create the GRAPH which will hold the achievement icon
        GRAPH *gr_avatar = gr_from_icon_id(icon_id);
        if(!gr_avatar) {
            return NULL;
        }

        return gr_avatar;
    }

    /* ---------------------------------------------------------------------- */

    int steam_achievement_unlock(INSTANCE *my, int *params) {
        if(!steam_loaded) {
            return -1;
        }

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

    int steam_achievement_delete(INSTANCE *my, int *params) {
        if(!steam_loaded) {
            return -1;
        }

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

    int steam_achivement_check(INSTANCE *my, int *params) {
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

    int steam_achievement_get_icon(INSTANCE *my, int *params) {
        if(!steam_loaded) {
            return -1;
        }

        // We get the icon ID for the given achievement,
        // and then use that ID to retrieve the pixels
        const char *achievement = string_get(params[0]);
        int icon_id = SteamUserStats()->GetAchievementIcon(achievement);
        string_discard(params[0]);
        if(icon_id <= 0) {
            return -1;
        }

        // Create the GRAPH which will hold the achievement icon
        GRAPH *gr_achievement = gr_from_icon_id(icon_id);
        if(!gr_achievement) {
            return -1;
        }

        return gr_achievement->code;
    }

    /* ---------------------------------------------------------------------- */

    int steam_avatar_get(INSTANCE *my, int *params) {
        if(!steam_loaded) {
            return -1;
        }

#if defined(_WIN32) && defined(__GNUC__)
        // Using the C++ API here crashes when compiled with MinGW in windows,
        // hence I'm resorting to steam_api_flat.h functions
        uint64_t steam_id = SteamAPI_ISteamUser_GetSteamID((intptr_t) SteamUser());
        GRAPH *gr_avatar = gr_avatar_get(CSteamID(steam_id), params[0]);
#else
        GRAPH *gr_avatar = gr_avatar_get(SteamUser()->GetSteamID(), params[0]);
#endif
        if(!gr_avatar) {
            return -1;
        }

        return gr_avatar->code;
    }

    /* ---------------------------------------------------------------------- */

    int steam_friend_count(INSTANCE *my, int *params) {
        // Get the number of friends
        if(!steam_loaded) {
            return -1;
        }

        return SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
    }

    /* ---------------------------------------------------------------------- */

    int steam_friend_name(INSTANCE *my, int *params) {
        // Get a friend's name
        if(!steam_loaded) {
            return -1;
        }

        int friend_count = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
        if(params[0] >= friend_count) {
            return -1;
        }

        CSteamID friend_id = SteamFriends()->GetFriendByIndex(params[0], k_EFriendFlagImmediate);
        const char *name = SteamFriends()->GetFriendPersonaName(friend_id);

        int str_id = string_new(name);
        string_use(str_id);
        return str_id;
    }

    /* ---------------------------------------------------------------------- */

    int steam_friend_nickname(INSTANCE *my, int *params) {
        // Get the user-assigned nickname for a friend
        if(!steam_loaded) {
            return -1;
        }

        int friend_count = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
        if(params[0] >= friend_count) {
            return -1;
        }

        CSteamID friend_id = SteamFriends()->GetFriendByIndex(params[0], k_EFriendFlagImmediate);
        const char *name = SteamFriends()->GetPlayerNickname(friend_id);

        int str_id;
        if(name) {
            str_id = string_new(name);
        } else {
            str_id = string_new("");
        }

        string_use(str_id);
        return str_id;
    }

    /* ---------------------------------------------------------------------- */

    int steam_friend_avatar(INSTANCE *my, int *params) {
        // Get a friend's avatar image, given its size
        if(!steam_loaded) {
            return -1;
        }

        int friend_count = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
        if(params[0] >= friend_count) {
            return -1;
        }

        CSteamID friend_id = SteamFriends()->GetFriendByIndex(params[0], k_EFriendFlagImmediate);
        GRAPH *avatar = gr_avatar_get(friend_id, params[1]);
        if(!avatar) {
            return -1;
        }

        return avatar->code;
    }

    /* ---------------------------------------------------------------------- */

    void __pxtexport(mod_steam, module_initialize)() {
        if (!SteamAPI_Init()) {
            fprintf(stderr, "Steam Error: SteamAPI_Init - "
                            "Steam must be running to play this game\n");
            fflush(stderr);

            return;
        }

        // Get a few IDs from Steam
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

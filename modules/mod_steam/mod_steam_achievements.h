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

/* ----------------------------------------------------------------------------------------
 The code below is taken from the SteamWorks "Step by Step: Achievements" section
 The documentation states as of Nov 20th 2016:
    "The following code is game independant and can be added to your game as you see fit"
 Hence the copyright statement above.
---------------------------------------------------------------------------------------- */

#ifndef STEAM_ACHIEVEMENTS_H
#define STEAM_ACHIEVEMENTS_H

#include <steam_api.h>

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
struct Achievement_t {
    int m_eAchievementID;
    const char *m_pchAchievementID;
    char m_rgchName[128];
    char m_rgchDescription[256];
    bool m_bAchieved;
    int m_iIconImage;
};

class CSteamAchievements {
private:
    uint64 m_iAppID; // Our current AppID
    Achievement_t *m_pAchievements; // Achievements data
    int m_iNumAchievements; // The number of Achievements
    bool m_bInitialized; // Have we called Request stats and received the callback?

public:
    CSteamAchievements(Achievement_t *Achievements, int NumAchievements);
    ~CSteamAchievements();

    bool RequestStats();
    bool SetAchievement(const char* ID);

    STEAM_CALLBACK( CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
        m_CallbackUserStatsReceived );
    STEAM_CALLBACK( CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
        m_CallbackUserStatsStored );
    STEAM_CALLBACK( CSteamAchievements, OnAchievementStored,
        UserAchievementStored_t, m_CallbackAchievementStored );
};


#endif

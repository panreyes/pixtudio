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

#include <stdio.h>
#include <mod_steam_achievements.h>

/* ----------------------------------------------------------------------------------------
 The code below is taken from the SteamWorks "Step by Step: Achievements" section
 The documentation states as of Nov 20th 2016:
    "The following code is game independant and can be added to your game as you see fit"
 Hence the copyright statement above.
---------------------------------------------------------------------------------------- */

// The constructor initializes a number of members along with grabbing the AppID
// we are currently running as. In addition it hooks up the call back methods to
// handle asynchronous calls made to Steam. Finally it makes an initial call to
// RequestStats() to get stats and achievements for the current user.
CSteamAchievements::CSteamAchievements(Achievement_t *Achievements, int NumAchievements):
 m_iAppID( 0 ),
 m_bInitialized( false ),
 m_CallbackUserStatsReceived( this, &CSteamAchievements::OnUserStatsReceived ),
 m_CallbackUserStatsStored( this, &CSteamAchievements::OnUserStatsStored ),
 m_CallbackAchievementStored( this, &CSteamAchievements::OnAchievementStored ) {
     m_iAppID = SteamUtils()->GetAppID();
     m_pAchievements = Achievements;
     m_iNumAchievements = NumAchievements;
     RequestStats();
}

// This method basically wraps a call to SteamUserStats()->RequestCurrentStats()
// that is an asynchronous call to steam requesting the stats of the current user.
// This call needs to be made before you can set and stats or achievements.
// The initial call to this method is made in the constructor. You can call it
// again any time after that if you want to check on updated stats or achievements.
bool CSteamAchievements::RequestStats() {
    // Is Steam loaded? If not we can't get stats.
    if ( NULL == SteamUserStats() || NULL == SteamUser() ) {
        return false;
    }
    // Is the user logged on?  If not we can't get stats.
    if ( !SteamUser()->BLoggedOn() ) {
        return false;
    }
    // Request user stats.
    return SteamUserStats()->RequestCurrentStats();
}

// This method sets a given achievement to achieved and sends the results to Steam.
// You can set a given achievement multiple times so you don't need to worry about
// only setting achievements that aren't already set. This is an asynchronous call
// which will trigger two callbacks: OnUserStatsStored() and OnAchievementStored().
bool CSteamAchievements::SetAchievement(const char* ID) {
    // Have we received a call back from Steam yet?
    if (m_bInitialized) {
        SteamUserStats()->SetAchievement(ID);
        return SteamUserStats()->StoreStats();
    }
    // If not then we can't set achievements yet
    return false;
}

// This method is a callback that is called anytime you attempt to request stats.
// Stats are requested by using RequestStats(). The method updates the member
// variable m_Achievements to reflect the latest achievement data returned from Steam.
void CSteamAchievements::OnUserStatsReceived(UserStatsReceived_t *pCallback) {
    // we may get callbacks for other games' stats arriving, ignore them
    if ( m_iAppID == pCallback->m_nGameID ) {
        if ( k_EResultOK == pCallback->m_eResult ) {
            printf("Received stats and achievements from Steam\n");
            m_bInitialized = true;

            // load achievements
            for ( int iAch = 0; iAch < m_iNumAchievements; ++iAch ) {
                Achievement_t &ach = m_pAchievements[iAch];

                SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
                _snprintf(ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
                          SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID, "name"));
                _snprintf(ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
                          SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID, "desc"));
            }
        } else {
            char buffer[128];
            _snprintf( buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult );
            printf( "%s", buffer );
        }
    }
}

// This method is a callback that is called anytime you attempt to store stats on Steam
void CSteamAchievements::OnUserStatsStored(UserStatsStored_t *pCallback) {
    // we may get callbacks for other games' stats arriving, ignore them
    if (m_iAppID == pCallback->m_nGameID) {
        if (k_EResultOK == pCallback->m_eResult) {
            printf("Stored stats for Steam\n");
        } else {
            char buffer[128];
            _snprintf(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult );
            printf(buffer);
        }
    }
}

// This method is a callback that is called anytime Achievements are successfully stored on Steam
void CSteamAchievements::OnAchievementStored(UserAchievementStored_t *pCallback) {
     // we may get callbacks for other games' stats arriving, ignore them
     if (m_iAppID == pCallback->m_nGameID) {
          printf("Stored Achievement for Steam\n");
     }
}

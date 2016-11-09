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

static int Steam_Cargado_Ok = 0;

/* ---------------------------------------------------------------------- */
extern "C" {

    void SteamAPIDebugTextHook(int nSeverity, const char *pchDebugText) {
        printf( "%s\n", pchDebugText );
    }

    int steam_init(INSTANCE *my, int *params) {

        if (!SteamAPI_Init()) {
            fprintf(stderr, "Steam Error: SteamAPI_Init - Steam must be running to play this game\n");
            fflush(stderr);

            return 0;
        }


        if(params[0]>0){
            if (SteamAPI_RestartAppIfNecessary(params[0])) {
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

        char rgchCWD[1024];
        getcwd(rgchCWD, sizeof(rgchCWD));

        char rgchFullPath[1024];
    #if defined(_WIN32)
        _snprintf(rgchFullPath, sizeof(rgchFullPath), "%s\\%s", rgchCWD, "controller.vdf");
    #elif defined(OSX)
        // hack for now, because we do not have utility functions available for finding the resource
        // path
        // alternatively we could disable the SteamController init on OS X
        _snprintf(rgchFullPath, sizeof(rgchFullPath), "%s/steamworksexample.app/Contents/Resources/%s",
                  rgchCWD, "controller.vdf");
    #else
        snprintf(rgchFullPath, sizeof(rgchFullPath), "%s/%s", rgchCWD, "controller.vdf");
    #endif

        /*if (!SteamController()->Init())
        {
            printf("Steam Error: SteamController()->Init failed.   \n");

            //return 0;
        }*/

        Steam_Cargado_Ok = 1;

        fprintf(stdout, "Steam Init OK.\n");
        fflush(stdout);

        return 0;
    }

    /* ---------------------------------------------------------------------- */

    int steam_close(INSTANCE *my, int *params) {
        if (Steam_Cargado_Ok) {
            // Shutdown the SteamAPI
            SteamAPI_Shutdown();

            // Shutdown Steam CEG
            // c_Steamworks_TermCEGLibrary();
            return 0;
        }

        return -1;
    }

    /* ---------------------------------------------------------------------- */
}

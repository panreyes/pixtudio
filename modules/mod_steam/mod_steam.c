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

typedef int bool;
#define true 1
#define false 0

#include "pxtdl.h"
#include "stdio.h"
#include "steam_wrapper.h"
#include <unistd.h>

const uint32_t k_uAppIdInvalid =
    0x0; // reemplazar en un futuro por un id que recibiremos por parámetro!

#ifndef __MONOLITHIC__
#include "mod_steam_symbols.h"
#endif

int Steam_Cargado_Ok = 0;

/* ---------------------------------------------------------------------- */

int steam_init(INSTANCE *my, int *params) {

    if (c_SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid)) {
        printf("Steam Error: SteamAPI_RestartAppIfNecessary  \n");
        return 0;
    }

    if (!c_SteamAPI_Init()) {
        printf("Steam Error: SteamAPI_Init - Steam must be running to play this game   \n");

        return 0;
    }

    c_SetWarningMessageHook();

    if (!c_SteamUser_BLoggedOn()) {
        printf("Steam Error: Steam user is not logged in - Steam user must be logged in to play "
               "this game   \n");

        return 0;
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

    printf("Steam Init OK.   \n");

    // exit
    return 1;
}

/* ---------------------------------------------------------------------- */

int steam_close(INSTANCE *my, int *params) {
    if (Steam_Cargado_Ok) {
        // Shutdown the SteamAPI
        c_SteamAPI_Shutdown();

        // Shutdown Steam CEG
        // c_Steamworks_TermCEGLibrary();
        return 1;
    }

    return 0;
}

/* ---------------------------------------------------------------------- */

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

#ifdef __cplusplus

#include <string>
#include <cstdio>
#include <steam_api.h>
#include "steam_wrapper.h"

extern "C" {
	#undef STEAM_CALLBACK //This is defined for the C code.
#endif
	#include <stdlib.h>

	bool c_SteamAPI_Init()
	{
		return SteamAPI_Init();
	}

	void c_SteamAPI_Shutdown()
	{
		SteamAPI_Shutdown();
	}

	bool c_SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID)
	{
		return SteamAPI_RestartAppIfNecessary(unOwnAppID);
	}

	bool c_SteamUser_BLoggedOn()
	{
		return SteamUser()->BLoggedOn();
	}

	void SteamAPIDebugTextHook( int nSeverity, const char *pchDebugText )
	{
		printf( "%s\n", pchDebugText );
	}

	void c_SetWarningMessageHook()
	{
		SteamClient()->SetWarningMessageHook( &SteamAPIDebugTextHook );
	}
	
#ifdef __cplusplus
}
#endif
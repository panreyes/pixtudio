/*
 *  Copyright (C) 2023 Pablo Antonio Navarro Reyes <panreyes@panreyes.com>
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

#include "mod_epic.h"
#include <pxtdl.h>
#include <stdio.h>
#include <unistd.h>
#include <pxtrtm.h>
#include <stdlib.h>
#include <fileapi.h>
#include <locale>
#include <codecvt>
#include <vector>
#include <eos_sdk.h>
#include <eos_achievements.h>
#include <eos_auth.h>
#include <eos_logging.h>

#ifndef __MONOLITHIC__
#include "mod_epic_symbols.h"
#endif

/* ---------------------------------------------------------------------- */
extern "C" {
	// Not currently used, but keep it just in case
    // #include <mod_map.h>
    #include <xstrings.h>
    #include <dlvaracc.h>

    static int epic_api_ready = 0;
    static uint32_t epic_userid = 0;
	
	static EOS_HPlatform PlatformHandle = nullptr;
	static EOS_ProductUserId PlayerID = nullptr;  // Player ID
	static EOS_HAchievements AchievementsHandle = nullptr;
	static EOS_HConnect ConnectHandle = nullptr;
	static EOS_NotificationId AchievementsUnlockedNotificationId;
	static EOS_HAuth AuthInterface = nullptr;
	static EOS_Auth_Token* UserAuthToken = nullptr;


    DLVARFIXUP __pxtexport(mod_epic, globals_fixup)[] = {
        /* Name of global var, pointer to the data, size, #elements */
        {"epic_username", NULL, -1, -1},
        {NULL, NULL, -1, -1}
    };

    /* ---------------------------------------------------------------------- */
	/*                  INTERNAL FUNCTIONS                                    */
	/* ---------------------------------------------------------------------- */

	// ...
	
    /* ---------------------------------------------------------------------- */
	/*                  EOS CALLBACKS                                         */
	/* ---------------------------------------------------------------------- */
	
	void EOS_CALL UnlockAchievementCompleteCb(const EOS_Achievements_OnUnlockAchievementsCompleteCallbackInfo* Data ) {
		if(Data->ResultCode == EOS_EResult::EOS_Success) {
			fprintf(stdout, "Achievement unlocked succesfully!\n");
		} else {
			fprintf(stdout, "Could not unlock achievement...\n");
		}
		fflush(stdout);
	}
	
	void EOS_CALL LogMessage(const EOS_LogMessage* message) {
		fprintf(stdout, "EOSLOG: %s\n", message->Message);
		fflush(stdout);
	}
	
	void EOS_CALL ConnectLoginCompleteCb(const EOS_Connect_LoginCallbackInfo* Data)
	{	
		if (Data->ResultCode == EOS_EResult::EOS_Success)
		{
			PlayerID = Data->LocalUserId;
			fprintf(stdout, "Received ProductUserId!!!!\n");
			fflush(stdout);
			
			epic_api_ready = 1;
			
			fprintf(stdout, "Epic SDK Init OK.\n");
			fflush(stdout);
		} else {
			fprintf(stdout, "Connect failed :( \n");
			fflush(stdout);
		}
	}

	void EOS_CALL LoginCompleteCallbackFn(const EOS_Auth_LoginCallbackInfo* Data) {
		if (Data->ResultCode == EOS_EResult::EOS_Success)
		{
			fprintf(stdout, "Logged in!! LocalUserId %d\n",Data->LocalUserId);
			fflush(stdout);
			
			EOS_Auth_CopyUserAuthTokenOptions CopyTokenOptions = { 0 };
			CopyTokenOptions.ApiVersion = EOS_AUTH_COPYUSERAUTHTOKEN_API_LATEST;
			
			EOS_EResult Resultado = EOS_Auth_CopyUserAuthToken(AuthInterface, &CopyTokenOptions, Data->LocalUserId, &UserAuthToken);

			if (Resultado == EOS_EResult::EOS_Success){
				fprintf(stdout, "Copied UserAuthToken!!\n");
				fflush(stdout);
				
				EOS_Connect_Credentials Credentials;
				Credentials.ApiVersion = EOS_CONNECT_CREDENTIALS_API_LATEST;
				Credentials.Token = UserAuthToken->AccessToken;
				Credentials.Type = EOS_EExternalCredentialType::EOS_ECT_EPIC;

				EOS_Connect_LoginOptions Options = { 0 };
				Options.ApiVersion = EOS_CONNECT_LOGIN_API_LATEST;
				Options.Credentials = &Credentials;
				Options.UserLoginInfo = nullptr;

				EOS_Connect_Login(ConnectHandle, &Options, nullptr, ConnectLoginCompleteCb);
				EOS_Auth_Token_Release(UserAuthToken);
			} else {
				fprintf(stdout, "Could not CopyUserAuthToken. EOS disabled. ResultCode: %d\n", Data->ResultCode);
				fflush(stdout);
			}
		} else {
			fprintf(stdout, "Could not log in. EOS disabled. ResultCode: %d\n", Data->ResultCode);
			fprintf(stdout, "ResultCode %02x\n", Data->ResultCode);
			fprintf(stdout, "LocalUserId %02x\n", Data->LocalUserId);
			fflush(stdout);
		}
	}
	
    /* ---------------------------------------------------------------------- */
	/*               USER FUNCTIONS                                           */
	/* ---------------------------------------------------------------------- */

	/*
	  == How does EOS work.
		1. Get the player credentials through argv.
		2. Start the SDK with all the "params"
		3. Start the platform interface
		4. Start the interfaces "auth", "connect" and "achievements"
		5. Log in "auth"
		6. With the data returned by "auth", log in "connect".
		7. Call EOS_Platform_Tick every frame
		x. Unlock any achievements
		
	  == How to do it in DIV-like code
		1. Call epic_init with the required 9 parameters
		2. (TEMPORARY SOLUTION) Have a "resident" process call epic_tick every frame
		3. Unlock achievements with epic_achievement_unlock
	*/

    int epic_init(INSTANCE *my, int *params) {
        if(epic_api_ready) {
            return 1;
        }
		
		//params (9!)
		// 0: product name
		// 1: version
		// 2: encryptionkey
		// 3: clientid
		// 4: clientsecret
		// 5: productid
		// 6: sandboxid
		// 7: deploymentid
		// 8: AUTH_PASSWORD
        
        // Fetch those parameters
		const char *eos_product_name = string_get(params[0]);
		const char *eos_version = string_get(params[1]);
		const char *eos_encryption_key = string_get(params[2]);
		const char *eos_client_id = string_get(params[3]);
		const char *eos_client_secret = string_get(params[4]);
		const char *eos_product_id = string_get(params[5]);
		const char *eos_sandbox_id = string_get(params[6]);
		const char *eos_deployment_id = string_get(params[7]);
		const char *eos_auth_password = string_get(params[8]);
		
		// Init SDK, Platform, Player, Achievement interface
		
		// Init EOS SDK
		EOS_InitializeOptions SDKOptions = {};
		SDKOptions.ApiVersion = EOS_INITIALIZE_API_LATEST;
		SDKOptions.ProductName = eos_product_name;
		SDKOptions.ProductVersion = eos_version;

		EOS_EResult InitResult = EOS_Initialize(&SDKOptions);
		if (InitResult != EOS_EResult::EOS_Success)
		{
			for (int i = 0; i <= 8; i++) {
				string_discard(params[i]);
			}
			
			fprintf(stdout, "Epic SDK Init FAILED.\n");
			fflush(stdout);
			return 0;
		}
		fprintf(stdout, "Epic SDK Init OK.\n");
		fflush(stdout);

		EOS_Logging_SetCallback(LogMessage);
		EOS_Logging_SetLogLevel(EOS_ELogCategory::EOS_LC_ALL_CATEGORIES, EOS_ELogLevel::EOS_LOG_Verbose);

		// Init EOS Platform
		EOS_Platform_Options PlatformOptions = {};
		PlatformOptions.ApiVersion = EOS_PLATFORM_OPTIONS_API_LATEST;
		PlatformOptions.bIsServer = EOS_FALSE;
		PlatformOptions.Flags = EOS_PF_WINDOWS_ENABLE_OVERLAY_D3D9 | EOS_PF_WINDOWS_ENABLE_OVERLAY_D3D10 | EOS_PF_WINDOWS_ENABLE_OVERLAY_OPENGL;

		PlatformOptions.ProductId = eos_product_id;
		PlatformOptions.SandboxId = eos_sandbox_id;
		PlatformOptions.DeploymentId = eos_deployment_id;
		
		PlatformOptions.ClientCredentials.ClientId = eos_client_id;
		PlatformOptions.ClientCredentials.ClientSecret = eos_client_secret;
		
		PlatformHandle = EOS_Platform_Create(&PlatformOptions);

		if (PlatformHandle == nullptr)
		{
			for (int i = 0; i <= 7; i++) {
				string_discard(params[i]);
			}

			fprintf(stdout, "Epic SDK Platform Init FAILED.\n");
			fflush(stdout);
			return 0;
		}
		fprintf(stdout, "Epic Platform Init OK.\n");
		fflush(stdout);
		
		// Check if it was launched from the launcher
		if (EOS_Platform_CheckForLauncherAndRestart(PlatformHandle) != EOS_EResult::EOS_Success) {
			// We should leave the game right now!
		}
		
		// Init achievements
		AchievementsHandle = EOS_Platform_GetAchievementsInterface(PlatformHandle);
		if (AchievementsHandle == nullptr)
		{
			for (int i = 0; i <= 8; i++) {
				string_discard(params[i]);
			}

			fprintf(stdout, "Epic SDK Achievements Init FAILED.\n");
			fflush(stdout);
			return 0;
		}

		fprintf(stdout, "Epic Achievements Init OK.\n");
		fflush(stdout);
	
		// Init Auth
		AuthInterface = EOS_Platform_GetAuthInterface(PlatformHandle);
		if (AuthInterface == nullptr)
		{
			for (int i = 0; i <= 8; i++) {
				string_discard(params[i]);
			}

			fprintf(stdout, "Epic SDK Auth Init FAILED.\n");
			fflush(stdout);
			return 0;
		}
		
		fprintf(stdout, "Epic Auth Init OK.\n");
		fflush(stdout);
		
		// Init Connect
		ConnectHandle = EOS_Platform_GetConnectInterface(PlatformHandle);
		if (ConnectHandle == nullptr)
		{
			for (int i = 0; i <= 8; i++) {
				string_discard(params[i]);
			}

			fprintf(stdout, "Epic SDK Connect Init FAILED.\n");
			fflush(stdout);
			return 0;
		}
		
		fprintf(stdout, "Epic Connect Init OK.\n");
		fflush(stdout);
		
		// Do "auth"!
		EOS_Auth_Credentials Credentials;
		Credentials.ApiVersion = EOS_AUTH_CREDENTIALS_API_LATEST;
		Credentials.Token = eos_auth_password;
		Credentials.Type = EOS_ELoginCredentialType::EOS_LCT_ExchangeCode;
		
		EOS_Auth_LoginOptions LoginOptions;
		LoginOptions.ApiVersion = EOS_AUTH_LOGIN_API_LATEST;
		LoginOptions.Credentials = &Credentials;
		LoginOptions.ScopeFlags = EOS_EAuthScopeFlags::EOS_AS_BasicProfile;
		
		fprintf(stdout, "Trying to log in...\n");
		fflush(stdout);
		EOS_Auth_Login(AuthInterface, &LoginOptions, nullptr, LoginCompleteCallbackFn);

		for (int i = 0; i <= 8; i++) {
			string_discard(params[i]);
		}
        
        return 1;
    }
	
	// FIXME: Currently called from user code. To be done automatically in every frame.
	int epic_tick(INSTANCE *my, int *params) {
		EOS_Platform_Tick(PlatformHandle);
		return 1;
	}
	
	int epic_achievement_unlock(INSTANCE *my, int *params) {
        if(!epic_api_ready) {
            return 0;
        }
		
		if(PlayerID == nullptr){
			fprintf(stdout, "No se puede desbloquear logro: Sin PlayerID\n");
			fflush(stdout);
			return 0;
		}
		
        const char *achievement = string_get(params[0]);
		const char** achievementIdsArray = (const char**) malloc(1 * sizeof(const char*));
		achievementIdsArray[0] = achievement;
		
		EOS_Achievements_UnlockAchievementsOptions UnlockAchievementsOptions = {};
		UnlockAchievementsOptions.ApiVersion = EOS_ACHIEVEMENTS_UNLOCKACHIEVEMENTS_API_LATEST;
		UnlockAchievementsOptions.UserId = PlayerID;
		UnlockAchievementsOptions.AchievementsCount = 1;
		UnlockAchievementsOptions.AchievementIds = achievementIdsArray;

		EOS_Achievements_UnlockAchievements(AchievementsHandle, &UnlockAchievementsOptions, nullptr, UnlockAchievementCompleteCb);

		free(achievementIdsArray);

        string_discard(params[0]);
		
		// async function, always return 1
		return 1;
	}
		    
    /* ---------------------------------------------------------------------- */
	/*          PXT HOOKS                                                     */
	/* ---------------------------------------------------------------------- */

    void __pxtexport(mod_epic, module_initialize)() {
		// Nothing done. Keep it just in case
    }
	
    void __pxtexport( mod_epic, module_finalize )() {
        if(!epic_api_ready) {
            return;
        }
		
		EOS_Shutdown();
    }
}

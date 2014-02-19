/*
 *  Copyright © 2006-2011 SplinterGU (Fenix/Bennugd)
 *  Copyright © 2002-2006 Fenix Team (Fenix)
 *
 *  This file is part of Bennu - Game Development
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

/*
 * INCLUDES
 */

#include "SDL.h"
#include <stdio.h>

#include "bgdrtm.h"

/* ---------------------------------------------------------------------- */

static char * dcb_exts[] = { ".dcb", ".dat", ".bin", NULL };

static int standalone  = 0;  /* 1 only if this is an standalone interpreter   */
static int embedded    = 0;  /* 1 only if this is a stub with an embedded DCB */

/* ---------------------------------------------------------------------- */

/*
 *  FUNCTION : main
 *
 *  Main function
 *
 *  PARAMS:
 *      INT n: ERROR LEVEL to return to OS
 *
 *  RETURN VALUE:
 *      No value
 *
 */

int main( int argc, char *argv[] )
{
    char * filename = NULL, dcbname[ __MAX_PATH ], *ptr ;
    int i, j, ret = -1;
    file * fp = NULL;
    INSTANCE * mainproc_running;
    dcb_signature dcb_signature;
    
    SDL_Log ("BennuGD init\n");
    
    filename = "main.dcb";
	if(file_exists("main.dcb"))
        SDL_Log("main.dcb exists in APK\n");
    else {
        SDL_Log("main.dcb doesn't exist in APK, quitting\n");
        return 1;
    }
    
    // Remember to compile DCB with debug (bgdc -g) info!
    debug = 1;
	
    /* Initialization (modules needed before dcb_load) */
	
    string_init() ;
    init_c_type() ;
	
    /* Init application title for windowed modes */
	
    strcpy( dcbname, filename ) ;
    
    SDL_Log("Loading main.dcb...\n");
	
    /* First try to load directly (we expect myfile.dcb) */
    if ( !dcb_load( dcbname ) )
    {
        char ** dcbext = dcb_exts;
        int dcbloaded = 0;
        
        while ( dcbext && *dcbext )
        {
            strcpy( dcbname, filename ) ;
            strcat( dcbname, *dcbext ) ;
            if (( dcbloaded = dcb_load( dcbname ) ) ) break;
            dcbext++;
        }
        
        if ( !dcbloaded )
        {
            SDL_Log( "%s: doesn't exist or isn't version %d DCB compatible\n", filename, DCB_VERSION >> 8 ) ;
            return -1 ;
        }
    }
	
    /* If the dcb is not in debug mode */
	
    if ( dcb.data.NSourceFiles == 0 ) debug = 0;
	
    /* Initialization (modules needed after dcb_load) */
	
    sysproc_init() ;
	
    argv[0] = filename;
    bgdrtm_entry( argc, argv );
	
    if ( mainproc )
    {
        mainproc_running = instance_new( mainproc, NULL ) ;
        ret = instance_go_all() ;
    }
	
    bgdrtm_exit( ret );
	
    free( appexename        );
    free( appexepath        );
    free( appexefullpath    );
    free( appname           );
	
    return ret;
}

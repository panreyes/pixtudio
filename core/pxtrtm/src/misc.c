/*
 *  Copyright (C) 2014-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
 *  Copyright (C) 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright (C) 2002-2006 Fenix Team (Fenix)
 *  Copyright (C) 1999-2002 José Luis Cebrián Pagüe (Fenix)
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

/* --------------------------------------------------------------------------- */
/*
 * INCLUDES
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "pxtrtm.h"
#include "offsets.h"
#include "dcb.h"
#include "sysprocs_p.h"
#include "xstrings.h"

#include "fmath.h"

/* --------------------------------------------------------------------------- */

char *appname        = NULL;
char *appexename     = NULL;
char *appexepath     = NULL;
char *appexefullpath = NULL;

/* --------------------------------------------------------------------------- */

int debug_DCB = 0; /* 1 if running in debug mode      */
int debug = 0;

/* --------------------------------------------------------------------------- */

/* os versions */
#ifdef _WIN32
#define _OS_ID OS_WIN32
#endif

#ifdef __linux__
#define _OS_ID OS_LINUX
#endif

#ifdef TARGET_BEOS
#define _OS_ID OS_BEOS
#endif

#ifdef __APPLE__
#define _OS_ID OS_MACOS
#endif

#ifdef TARGET_GP32
#define _OS_ID OS_GP32
#endif

#ifdef TARGET_DC
#define _OS_ID OS_DC
#endif

#ifdef TARGET_BSD
#define _OS_ID OS_BSD
#endif

#ifdef TARGET_GP2X
#ifdef _OS_ID
#undef _OS_ID
#endif
#define _OS_ID OS_GP2X
#endif

#ifdef TARGET_GP2X_WIZ
#ifdef _OS_ID
#undef _OS_ID
#endif
#define _OS_ID OS_GP2X_WIZ
#endif

#ifdef TARGET_CAANOO
#ifdef _OS_ID
#undef _OS_ID
#endif
#define _OS_ID OS_CAANOO
#endif

#ifdef TARGET_DINGUX_A320
#ifdef _OS_ID
#undef _OS_ID
#endif
#define _OS_ID OS_DINGUX_A320
#endif

#ifdef TARGET_WII
#ifdef _OS_ID
#undef _OS_ID
#endif
#define _OS_ID OS_WII
#endif

#ifdef TARGET_PSP
#ifdef _OS_ID
#undef _OS_ID
#endif
#define _OS_ID OS_PSP
#endif

#if (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR))
#ifdef _OS_ID
#undef _OS_ID
#endif
#define _OS_ID OS_IOS
#endif

#ifdef __ANDROID__
#ifdef _OS_ID
#undef _OS_ID
#endif
#define _OS_ID OS_ANDROID
#endif

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : pxtrtm_strncmpi
 *
 *  Compare two strings (case-insensitive version)
 *
 *  PARAMS:
 *      str1    first string
 *      str2    second string
 *
 *  RETURN VALUE:
 *      Result of the comparison
 */

int pxtrtm_strncmpi(char *str1, char *str2, int sz) {
    while ((*str1 || *str2) && sz) {
#ifdef _WIN32
        if (toupper(*str1) != toupper(*str2)) {
            return toupper(*str1) - toupper(*str2);
        }
#else
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
#endif
        str1++;
        str2++;
        sz--;
    }

    return 0;
}

/* --------------------------------------------------------------------------- */

void pxtrtm_entry(int argc, char *argv[]) {
    int i;
    int *args = (int *)&GLODWORD(ARGV_TABLE);
    char *os_id;

    GLODWORD(ARGC) = argc;

    for (i = 0; i < argc && i < 32; i++) {
        args[i] = string_new(argv[i]);
        string_use(args[i]);
    }

    if ((os_id = getenv("OS_ID")))
        GLODWORD(OS_ID) = atol(os_id);
    else
        GLODWORD(OS_ID) = _OS_ID;

    init_cos_tables();
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : pxtrtm_exit
 *
 *  Exits from the program cleanly ending operations
 *
 *  PARAMS:
 *      INT n: ERROR LEVEL to return to OS
 *
 *  RETURN VALUE:
 *      No value
 *
 */

void pxtrtm_exit(int exit_code) {
    int n;

    /* Finalize all modules */
    if (module_finalize_count) {
        for (n = 0; n < module_finalize_count; n++) {
            module_finalize_list[n]();
        }
    }

    exit(exit_code);
}

/* --------------------------------------------------------------------------- */

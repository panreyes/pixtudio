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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgdrtm.h"
#include "bgddl.h"
#include "xstrings.h"

#include <SDL_log.h>
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR))
#include <SDL_stdinc.h>
#endif

#ifndef __MONOLITHIC__
#include "mod_say_symbols.h"
#endif

/* ---------------------------------------------------------------------- */

int modsay_say(INSTANCE *my, int *params) {
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR))
    char *converted;
    const char *msg = string_get(params[0]);

    converted = SDL_iconv_string("UTF-8", "ISO-8859-1", msg, SDL_strlen(msg) + 1);
    /* Show debugging info also in stdout */
    SDL_Log("%s\n", converted);
    string_discard(params[0]);
    SDL_free(converted);
#else
    printf("%s\n", string_get(params[0]));
    fflush(stdout);
    string_discard(params[0]);
#endif
    return 1;
}

/* ---------------------------------------------------------------------- */

int modsay_say_fast(INSTANCE *my, int *params) {
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR))
    char *converted;
    const char *msg = string_get(params[0]);

    converted = SDL_iconv_string("UTF-8", "ISO-8859-1", msg, SDL_strlen(msg) + 1);
    /* Show debugging info also in stdout */
    SDL_Log("%s\n", converted);
    string_discard(params[0]);
    SDL_free(converted);
#else
    printf("%s\n", string_get(params[0]));
    string_discard(params[0]);
#endif
    return 1;
}

/* ----------------------------------------------------------------- */

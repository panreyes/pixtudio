/*
 *  Copyright (C) 2015 Joseba García Etxebarria <joseba.gar@gmail.com>
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

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char locale[6];

int copy_locale_var(const char *varname, char *dest) {
    char *full_locale = getenv("LANG");

    if (full_locale != NULL) {
        uint8_t n = strlen(full_locale);
        if (n > 5) {
            n = 5;
        }

        memcpy(locale, full_locale, n);
        locale[n] = '\0';

        return 1;
    }

    return -1;
}

// get_locale implementation reading the LANG environment variable
// returns en_US on failure
const char *get_locale() {
    if (copy_locale_var("LANG", locale) > 0) {
        return (const char *)locale;
    } else if (copy_locale_var("LC_ALL", locale) > 0) {
        return (const char *)locale;
    }

    return "(-_-)";
}

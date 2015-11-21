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

#include <SDL.h>
//#include <android/configuration.h>
#include <jni.h>

char locale[6];

// get_locale Android implementation
const char *get_locale() {
    const char *lang, *country;
    jmethodID mid;
    JNIEnv *mEnv = SDL_AndroidGetJNIEnv();
    // Find the "Locale" class representation and get the default Locale
    jclass localeClass = (*mEnv)->FindClass(mEnv, "java/util/Locale");
    mid = (*mEnv)->GetStaticMethodID(mEnv, localeClass, "getDefault", "()Ljava/util/Locale;");
    if (!mid) {
        return "(-_-)";
    }

    jobject localeObject = (jobject)(*mEnv)->CallStaticObjectMethod(mEnv, localeClass, mid);

    // Call getLanguage() and store its representation
    mid = (*mEnv)->GetMethodID(mEnv, localeClass, "getLanguage", "()Ljava/lang/String;");
    if (mid) {
        jstring langString = (jstring)(*mEnv)->CallObjectMethod(mEnv, localeObject, mid);
        lang = (*mEnv)->GetStringUTFChars(mEnv, langString, NULL);
        if(strlen(lang) == 0) {
            memcpy(locale, "(-", 2);
        } else {
            memcpy(locale, lang, 2);
        }
        locale[2] = '_';
        (*mEnv)->ReleaseStringUTFChars(mEnv, langString, lang);
    }

    // Call getCountry() and store its representation
    mid = (*mEnv)->GetMethodID(mEnv, localeClass, "getCountry", "()Ljava/lang/String;");
    if (mid) {
        jstring countryString = (jstring)(*mEnv)->CallObjectMethod(mEnv, localeObject, mid);
        country = (*mEnv)->GetStringUTFChars(mEnv, countryString, NULL);
        if(strlen(country) == 0) {
            memcpy(locale+3, "-)", 2);
        } else {
            memcpy(locale+3, country, 2);
        }
        (*mEnv)->ReleaseStringUTFChars(mEnv, countryString, country);
    }

    // char termination byte
    locale[5] = '\0';

    return locale;
}

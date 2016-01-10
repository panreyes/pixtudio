/*
 *  Copyright (C) 2011-2015 Joseba Garcí­a Echebarria. All rights reserved.
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
#include <bgddl.h>
#include <xstrings.h>
#include <bgdrtm.h>
#include <curl/curl.h>
#include <SDL_thread.h>

#ifndef MAX_DOWNLOADS
#define MAX_DOWNLOADS 16
#endif

#ifndef __MONOLITHIC__
#include "mod_curl_symbols.h"
#endif

/* --------------------------------------------------------------------------- */

// Data used when downloading to memory
struct MemoryStruct {
    char *memory;
    int *strid;
    size_t size;
};

// Structure with the curl action data
typedef struct {
    CURL *curl;
    struct curl_httppost *formpost;
    struct curl_httppost *lastptr;
    struct MemoryStruct chunk; // Used when downloading to a string
    FILE *outfd;               // Used when downloading to a file
    int used;
} curl_info;

// Struct needed to launch the curl action in a separate thread
typedef struct {
    int *id;
    int *status;
    int (*fn)();
} bgdata;

curl_info download_info[MAX_DOWNLOADS];

/* --------------------------------------------------------------------------- */

// Find the first free curl_info index, return numeric index
int findindex() {
    int i = 0;

    for (i = 0; i < MAX_DOWNLOADS; i++) {
        if (download_info[i].used == 0) {
            // Initialize values, just in case they haven't been already
            download_info[i].formpost   = NULL;
            download_info[i].lastptr    = NULL;
            download_info[i].outfd      = NULL;
            download_info[i].chunk.size = 0;
            download_info[i].used       = 1;
            return i;
        }
    }

    return -1;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize          = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        /* out of memory! */
        fprintf(stderr, "not enough memory (realloc returned NULL)\n");
        exit(EXIT_FAILURE);
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

/* --------------------------------------------------------------------------- */

/**
 * PREP
 * Helper function preparing params
 **/

static bgdata *prep(int *params) {
    bgdata *t = (bgdata *)malloc(sizeof(bgdata));

    t->id     = (int *)params[0];
    t->status = (int *)params[1];

    return t;
}

/* --------------------------------------------------------------------------- */
/**
 * bgDoLoad
 * Helper function executed in the new thread
 **/

static int bgDoLoad(void *d) {
    bgdata *t = (bgdata *)d;
    *(t->status) = -2;
    *(t->status) = (*t->fn)(t->id);
    free(t);
    return 0;
}

/* --------------------------------------------------------------------------- */
// Maps curl_formadd
int bgd_curl_formadd(INSTANCE *my, int *params) {
    int retval = 0;

    if (params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;

    // Actually perform curl_formadd
    retval = curl_formadd(&download_info[params[0]].formpost, &download_info[params[0]].lastptr,
                          params[1], string_get(params[2]), params[3], string_get(params[4]),
                          CURLFORM_END);

    string_discard(params[2]);
    string_discard(params[4]);

    return retval;
}

// Maps curl_formfree
int bgd_curl_formfree(INSTANCE *my, int *params) {
    if (params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;

    // Actually perform curl_formfree
    curl_formfree(download_info[params[0]].formpost);

    return 0;
}

// Maps curl_easy_init
int bgd_curl_easy_init(INSTANCE *my, int *params) {
    int i;

    // Get the index of the connection
    if ((i = findindex()) == -1)
        return -1;

    download_info[i].curl = curl_easy_init();

    if (download_info[i].curl == NULL)
        return -1;

    return i;
}

// Maps curl_easy_cleanup
int bgd_curl_easy_cleanup(INSTANCE *my, int *params) {
    if (params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;

    download_info[params[0]].used = 0;

    curl_easy_cleanup(download_info[params[0]].curl);

    return 0;
}

// Maps curl_easy_setopt for options which require an integer
int bgd_curl_easy_setopt(INSTANCE *my, int *params) {
    if (params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;

    CURLcode retval;

    // Actually perform curl_easy_setopt
    switch (params[1]) {
        case CURLOPT_HTTPPOST:
            retval = curl_easy_setopt(download_info[params[0]].curl, CURLOPT_HTTPPOST,
                                      download_info[params[0]].formpost);
            break;

        default:
            retval = curl_easy_setopt(download_info[params[0]].curl, params[1], params[2]);
            break;
    }

    return (int)retval;
}

// Maps curl_easy_setopt for options which require a string
int bgd_curl_easy_setopt2(INSTANCE *my, int *params) {
    if (params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;

    CURLcode retval;

    // Actually perform curl_easy_setopt
    switch (params[1]) {
        // Handle some special cases
        case CURLOPT_WRITEDATA:
            // Point the output file pointer to the given location
            download_info[params[0]].outfd = fopen(string_get(params[2]), "wb");
            string_discard(params[2]);
            if (download_info[params[0]].outfd == NULL)
                return -1;

            retval = curl_easy_setopt(download_info[params[0]].curl, CURLOPT_WRITEDATA,
                                      download_info[params[0]].outfd);
            break;

        default:
            retval =
                curl_easy_setopt(download_info[params[0]].curl, params[1], string_get(params[2]));
            string_discard(params[2]);
            break;
    }

    return (int)retval;
}

// Maps curl_easy_setopt when downloading data to a string directly
int bgd_curl_easy_setopt3(INSTANCE *my, int *params) {
    if (params[0] == -1 || params[0] > MAX_DOWNLOADS)
        return -1;

    CURLcode retval;

    // Actually perform curl_easy_setopt
    switch (params[1]) {
        // When called with an integer, download to a string
        case CURLOPT_WRITEDATA:
            // Initialization
            download_info[params[0]].chunk.memory = malloc(1);

            // Set writefunction and writedata to the appropriate values
            curl_easy_setopt(download_info[params[0]].curl, CURLOPT_WRITEFUNCTION,
                             WriteMemoryCallback);
            download_info[params[0]].chunk.strid = (int *)params[2];
            retval = curl_easy_setopt(download_info[params[0]].curl, CURLOPT_WRITEDATA,
                                      (void *)&(download_info[params[0]].chunk));
            break;

        default:
            retval = -1;
            break;
    }

    return (int)retval;
}

// Actual perform function
int curl_perform(int id) {
    if (download_info[id].curl == NULL) {
        return -1;
    }

    int retval = 0;

    // Perform download, this function won't quit until it's done
    retval = curl_easy_perform(download_info[id].curl);

    // If downloading to a file, close its file descriptor
    if (download_info[id].outfd != NULL) {
        fclose(download_info[id].outfd);
    } else if (download_info[id].chunk.size > 0) {
        // Create the string for the user
        // printf("Output from CURL:\n%s\n", download_info[id].chunk.memory);
        *(download_info[id].chunk.strid) = string_new(download_info[id].chunk.memory);
        string_use(*(download_info[id].chunk.strid));

        // Free used memory
        free(download_info[id].chunk.memory);
    }

    return retval;
}

// Map curl_easy_perform
int bgd_curl_easy_perform(INSTANCE *my, int *params) {
    bgdata *t = prep(params);
    t->fn     = curl_perform;

    SDL_CreateThread(bgDoLoad, "PixTudio mod_curl thread", (void *)t);

    return 0;
}

// Initialize libcurl
void __bgdexport(mod_curl, module_initialize)() {
    curl_global_init(CURL_GLOBAL_ALL);
}

// Finalize libcurl
void __bgdexport(mod_curl, module_finalize)() {
    curl_global_cleanup();
}

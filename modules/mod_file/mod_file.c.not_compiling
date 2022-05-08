/*
 *  Copyright (C) 2014-2020 Joseba Echevarria García <joseba.gar@gmail.com>
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
#include <libgen.h>

#include "pxtdl.h"

#include "arrange.h"
#include "files.h"
#include "xstrings.h"
#include "dcb.h"
#include "varspace_file.h"
#include <stretchy_buffer.h>

#ifndef __MONOLITHIC__
#include "mod_file_symbols.h"
#endif

/* ----------------------------------------------------------------- */

static file **loaded_files  = NULL;

/*
 *  FUNCTION : find_free_fileID
 *
 *  Find a free file spot in given array.
 *  If no spots are available, return -1.
 *
 *  PARAMS:
 *      array to find free spot in
 *
 *  RETURN VALUE:
 *
 *      an integer with the position index, or -1 if an error occurred
 *
 */

static int find_free_fileID(file **where) {
    int32_t i = 0, len = 0;

    // Try to find an empty spot (the pointer should be NULL there)
    len = sb_count(where);
    for (i = 0; i < len; i++) {
        if (where[i] == NULL) {
            return i + 1;
        }
    }

    // None available => return -1
    return -1;
}

/* --------------------------------------------------------------------------- */

int modfile_save(INSTANCE *my, int *params) {
    file *fp;
    const char *filename;
    int result = 0;

    filename = string_get(params[0]);
    if (!filename)
        return 0;

    fp = file_open(filename, "wb0");
    if (fp) {
        result = savetypes(fp, (void *)params[1], (void *)params[2], params[3], 0);
        file_close(fp);
    }
    string_discard(params[0]);
    return result;
}

int modfile_load(INSTANCE *my, int *params) {
    file *fp;
    const char *filename;
    int result = 0;

    filename = string_get(params[0]);
    if (!filename)
        return 0;

    fp = file_open(filename, "rb0");
    if (fp) {
        result = loadtypes(fp, (void *)params[1], (void *)params[2], params[3], 0);
        file_close(fp);
    }
    string_discard(params[0]);
    return result;
}

int modfile_fopen(INSTANCE *my, int *params) {
    static char *ops[] = {"rb0", "r+b0", "wb0", "rb", "wb6"};
    file fd;
    int32_t id;

    if (params[1] < 0 || params[1] > 4) {
        params[0] = 0;
    }

    fd = file_open(string_get(params[0]), ops[params[1]]);
    string_discard(params[0]);
    if(!fd) {
        return 0;
    }

    // Store the given ID
    id = find_free_fileID(loaded_files);
    if (id == -1) {
        // Increase buffer size by 1
        sb_push(loaded_files, fd);
        id = sb_count(loaded_files);
    } else {
        loaded_files[id - 1] = fd;
    }

    return (int)id;
}

int modfile_fclose(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        file_close(loaded_files[params[0]]);
        loaded_files[params[0]] = NULL;
    }
    return 1;
}

int modfile_fread(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        return loadtypes(loaded_files[params[0]], (void *)params[1], (void *)params[2], params[3], 0);
    }

    // Read failed
    return 0;
}

int modfile_fwrite(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        return savetypes(loaded_files[params[0]], (void *) params[1], (void *) params[2], params[3], 0);
    }

    // Write failed
    return 0;
}

int modfile_freadC(INSTANCE *my, int *params) {
    if (params[2] >= 0 && params[2] < sb_count(loaded_files) && loaded_files[params[2]]) {
        return file_read(loaded_files[params[2]], (void *) params[0], params[1]);
    }

    // Read failed
    return 0;
}

int modfile_fwriteC(INSTANCE *my, int *params) {
    if (params[2] >= 0 && params[2] < sb_count(loaded_files) && loaded_files[params[2]]) {
        return file_write(loaded_files[params[2]], (void *) params[0], params[1]);
    }

    // Write failed
    return 0;
}

int modfile_fseek(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        return file_seek(loaded_files[params[0]], params[1], params[2]);
    }

    // Seek failed
    return -1;
}

int modfile_frewind(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        file_rewind(loaded_files[params[0]]);
        return 1;
    }

    return -1;
}

int modfile_ftell(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        return file_pos(loaded_files[params[0]]);
    }

    return -1;
}

int modfile_fflush(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        return file_flush(loaded_files[params[0]]);
    }

    return -1;
}

int modfile_filelength(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        return file_size(loaded_files[params[0]]);
    }

    return -1;
}

int modfile_fputs(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        char *str = (char *) string_get(params[1]);
        int r = file_puts(loaded_files[params[0]], str);
        if (str[strlen(str) - 1] != '\n') {
            file_puts(loaded_files[params[0]], "\r\n");
        }
        /*    int r = file_puts (loaded_files[params[0]], string_get(params[1])) ; */
        string_discard(params[1]);
        return r;
    }

    return -1;
}

int modfile_fgets(INSTANCE *my, int *params) {
    char buffer[1025];
    int len, done = 0;
    int str       = string_new("");

    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        while (!done) {
            len = file_gets(loaded_files[params[0]], buffer, sizeof(buffer) - 1);
            if (len < 1)
                break;

            if (buffer[len - 1] == '\r' || buffer[len - 1] == '\n') {
                len--;
                if (len && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n'))
                    len--;
                buffer[len] = '\0';
                done = 1;
            }
            string_concat(str, buffer);
        }
    }
    string_use(str);
    return str;
}

int modfile_file(INSTANCE *my, int *params) {
    char buffer[1025];
    int str = string_new("");
    file *f;
    int l;

    f = file_open(string_get(params[0]), "rb");
    string_discard(params[0]);

    if (f) {
        while (!file_eof(f)) {
            l         = file_read(f, buffer, sizeof(buffer) - 1);
            buffer[l] = '\0';
            if (l) {
                string_concat(str, buffer);
                buffer[0] = '\0';
            } else
                break;
        }
        file_close(f);
    }

    string_use(str);

    return str;
}

int modfile_feof(INSTANCE *my, int *params) {
    if (params[0] >= 0 && params[0] < sb_count(loaded_files) && loaded_files[params[0]]) {
        return file_eof(loaded_files[params[0]]s);
    }

    return 1;
}

int modfile_exists(INSTANCE *my, int *params) {
    int r = file_exists(string_get(params[0]));
    string_discard(params[0]);
    return r;
}

int modfile_remove(INSTANCE *my, int *params) {
    int r = file_remove(string_get(params[0]));
    string_discard(params[0]);
    return r;
}

int modfile_move(INSTANCE *my, int *params) {
    int r = file_move(string_get(params[0]), string_get(params[1]));
    string_discard(params[1]);
    string_discard(params[0]);
    return r;
}

int modfile_dirname(INSTANCE *my, int *params) {
    char *path = strdup(string_get(params[0]));
    string_discard(params[0]);
    int str_code = string_new(dirname(path));
    string_use(str_code);

    return str_code;
}

int modfile_basename(INSTANCE *my, int *params) {
    char *path = strdup(string_get(params[0]));
    string_discard(params[0]);
    int str_code = string_new(basename(path));
    string_use(str_code);

    return str_code;
}

/* --------------------------------------------------------------------------- */

void __pxtexport(mod_file, module_finalize)() {
    // Unload open files, if any
    n = sb_count(loaded_files);
    for (i = 0; i < n; i++) {
        file_close(i);
    }
    sb_free(loaded_files);
}
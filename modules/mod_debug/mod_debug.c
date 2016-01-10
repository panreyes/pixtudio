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

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <SDL.h>

#include "bgdcore.h"
#include "bgdrtm.h"
#include "bgddl.h"
#include "dlvaracc.h"

#include "dcb.h"
#include "instance.h"

#include "files.h"

#include "xstrings.h"
#include "libkey.h"
#include "libgrbase.h"
#include "librender.h"

// Networking stuff
#include <fcntl.h>
#ifdef WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#ifndef __MONOLITHIC__
#include "mod_debug_symbols.h"
#else
extern DLVARFIXUP __bgdexport(mod_debug, locals_fixup)[];
#endif

/* --------------------------------------------------------------------------- */

#ifndef _vsnprintf
#define _vsnprintf vsnprintf
#endif

#ifndef _snprintf
#define _snprintf snprintf
#endif

/* --------------------------------------------------------------------------- */

enum { PROCESS_ID = 0, FATHER, BIGBRO, SON, STATUS };

enum { SHIFTSTATUS = 0 };

/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */

#define MAXTEXT 5000

#define CHARWIDTH 6
#define CHARHEIGHT 8

#define CONSOLE_HISTORY 512
#define COMMAND_HISTORY 128

#define MAX_EXPRESSIONS 128

/* --------------------------------------------------------------------------- */

#define HELPTXT                                                                                    \
    "\033[38;2;0;192;0mProcess Info\033[0m\n"                                                      \
    "\033[38;2;0;192;192mINSTANCES       \033[0m  List all running processes\n"                    \
    "\033[38;2;0;192;192mGLOBALS         \033[0m  Show global vars with values\n"                  \
    "\033[38;2;0;192;192mLOCALS proc     \033[0m  Show a process's local vars\n"                   \
    "\033[38;2;0;192;192mPRIVATES proc   \033[0m  Show a process's private vars\n"                 \
    "\033[38;2;0;192;192mPUBLICS proc    \033[0m  Show a process's public vars\n"                  \
    "\n"                                                                                           \
    "\033[38;2;0;192;0mExecution Commands\033[0m\n"                                                \
    "\033[38;2;0;192;192mGO              \033[0m  Continue the execution\n"                        \
    "\033[38;2;0;192;192mTRACE           \033[0m  Execute one instruction and Debug\n"             \
    "\033[38;2;0;192;192mNEXTFRAME       \033[0m  Continue to next frame\n"                        \
    "\033[38;2;0;192;192mNEXTPROC        \033[0m  Continue to next process\n"                      \
    "\n"                                                                                           \
    "\033[38;2;0;192;0mBreakpoints\033[0m\n"                                                       \
    "\033[38;2;0;192;192mBREAK           \033[0m  List breakpoints\n"                              \
    "\033[38;2;0;192;192mBREAK proc      \033[0m  Set a breakpoint on process\n"                   \
    "\033[38;2;0;192;192mBREAKALL        \033[0m  Set breakpoints on all processes\n"              \
    "\033[38;2;0;192;192mBREAKALLTYPES   \033[0m  Set breakpoints on all processes types\n"        \
    "\033[38;2;0;192;192mDELETE proc     \033[0m  Delete a breakpoint\n"                           \
    "\033[38;2;0;192;192mDELETEALL       \033[0m  Delete all breakpoints on all processess\n"      \
    "\033[38;2;0;192;192mDELETEALLTYPES  \033[0m  Delete all breakpoints on all processess "       \
    "types\n"                                                                                      \
    "\n"                                                                                           \
    "\033[38;2;0;192;0mProcess Interaction\033[0m\n"                                               \
    "\033[38;2;0;192;192mRUN proc [args] \033[0m  Run a process\n"                                 \
    "\033[38;2;0;192;192mKILL proc       \033[0m  Kill a process\n"                                \
    "\033[38;2;0;192;192mWAKEUP proc     \033[0m  Wakeup a process\n"                              \
    "\033[38;2;0;192;192mSLEEP proc      \033[0m  Sleep a process\n"                               \
    "\033[38;2;0;192;192mFREEZE proc     \033[0m  Freeze a process\n"                              \
    "\033[38;2;0;192;192mKILLALL proc    \033[0m  Kill all process with criteria\n"                \
    "\033[38;2;0;192;192mWAKEUPALL proc  \033[0m  Wakeup all process with criteria\n"              \
    "\033[38;2;0;192;192mSLEEPALL proc   \033[0m  Sleep all process with criteria\n"               \
    "\033[38;2;0;192;192mFREEZEALL proc  \033[0m  Freeze all process with criteria\n"              \
    "\n"                                                                                           \
    "\033[38;2;0;192;0mMisc\033[0m\n"                                                              \
    "\033[38;2;0;192;192mSHOW expression \033[0m  Evaluate and show some expression\n"             \
    "\033[38;2;0;192;192mSHOW            \033[0m  List all expressions to show\n"                  \
    "\033[38;2;0;192;192mSHOWDEL ExpID   \033[0m  Delete an expression (by ID, use SHOW)\n"        \
    "\033[38;2;0;192;192mSHOWDELALL      \033[0m  Delete all expression\n"                         \
    "\033[38;2;0;192;192mSTRINGS         \033[0m  Show all strings in memory\n"                    \
    "\033[38;2;0;192;192mVARS            \033[0m  Show internals vars\n"                           \
    "\033[38;2;0;192;192mQUIT            \033[0m  Kill the program and exit\n"                     \
    "\n"                                                                                           \
    "\033[38;2;0;192;0mKeys\033[0m\n"                                                              \
    "\033[38;2;0;192;192mESC             \033[0m  Cancel command\n"                                \
    "\033[38;2;0;192;192mUP/DOWN         \033[0m  Command history navigation\n"                    \
    "\033[38;2;0;192;192mPGUP/PGDN       \033[0m  Page Up/Page Down\n"                             \
    "\033[38;2;0;192;192mALT+CURSORS     \033[0m  Console window size\n"                           \
    "\n"                                                                                           \
    "You can evaluate free expressions in the console, and you can see/change\n"                   \
    "local, public and private vars using the '.' operator\n"                                      \
    "(pe: 65535.X, MAIN.X, etc.)\n\n"

/* --------------------------------------------------------------------------- */

#define HOTKEYHELP_SIZE 50

#define HOTKEYHELP1                                                                                \
    "\033[38;2;0;0;192mF1:\033[38;2;0;0;0m?\x03\033[38;2;0;0;192mF2:\033[38;2;0;0;"                \
    "0mProcs\x03\033[38;2;0;0;192mF5:\033[38;2;0;0;0mGo\x03\033[38;2;0;0;192mF8:\033[38;2;0;0;"    \
    "0mTrace\x03\033[38;2;0;0;192mF10:\033[38;2;0;0;0mNFrame\x03\033[38;2;0;0;192mF11:\033[38;2;"  \
    "0;0;0mNProc"
#define HOTKEYHELP2                                                                                \
    "\033[38;2;0;0;192mF1:\033[38;2;0;0;0m?\x03\033[38;2;0;0;192mF2:\033[38;2;0;0;"                \
    "0mBrief\x03\033[38;2;0;0;192mF6:\033[38;2;0;0;0mProcs\x03\033[38;2;0;0;192mF9:\033[38;2;0;0;" \
    "0mBreak"
#define HOTKEYHELP3                                                                                \
    "\033[38;2;0;0;192mF1:\033[38;2;0;0;0m?\x03\033[38;2;0;0;192mF2:\033[38;2;0;0;"                \
    "0mBrief\x03\033[38;2;0;0;192mF3:\033[38;2;0;0;0mLoc\x03\033[38;2;0;0;192mF4:\033[38;2;0;0;"   \
    "0mPri\x03\033[38;2;0;0;192mF5:\033[38;2;0;0;0mPub\x03\033[38;2;0;0;192mF6:\033[38;2;0;0;"     \
    "0mTypes\x03\033[38;2;0;0;192mF9:\033[38;2;0;0;0mBrk"

/* --------------------------------------------------------------------------- */

#define N_CONSOLE_VARS (sizeof(console_vars) / sizeof(console_vars[0]))

#define CON_DWORD 0x0001
#define CON_DWORD_HEX 0x8001

/* --------------------------------------------------------------------------- */

/* Tipos de token */
#define IDENTIFIER 1
#define STRING 2
#define NUMBER 3
#define OPERATOR 4
#define NOTOKEN 5

/* --------------------------------------------------------------------------- */

static struct {
    int type;
    DCB_VAR var;
    double value;
    void *data;
    char name[256];
} result, lvalue;

static struct {
    enum { T_ERROR, T_VARIABLE, T_NUMBER, T_CONSTANT, T_STRING } type;
    char name[128];
    double code;
} token;

static const char *token_ptr;

/* --------------------------------------------------------------------------- */

/* Console contents */
static char *show_expression[MAX_EXPRESSIONS] = {NULL};
static int show_expression_count              = 0;
static int console_showcolor                  = 0xffffff;

/* --------------------------------------------------------------------------- */

static int debug_on_frame     = 0;
static int break_on_next_proc = 0;

/* --------------------------------------------------------------------------- */

static struct {
    char *name;
    void *value;
    int type;
} console_vars[] = {
    {"SHOW_COLOR", &console_showcolor, CON_DWORD_HEX},
    {"FILES", &opened_files, CON_DWORD},
    {"DEBUG_LEVEL", &debug, CON_DWORD},
};

/* --------------------------------------------------------------------------- */

static int console_sock;

/* --------------------------------------------------------------------------- */

static void eval_immediate();
static void eval_value();
static void eval_factor();
static void eval_subexpression();
static char *eval_expression(const char *here, int interactive);

static char *describe_type(DCB_TYPEDEF type, int from);
static char *show_value(DCB_TYPEDEF type, void *data);
static void show_struct(int num, char *title, int indent, void *data);
static void show_var(DCB_VAR var, char *name, void *data, char *title, int indent);

static int type_size(DCB_TYPEDEF orig);
static DCB_TYPEDEF reduce_type(DCB_TYPEDEF orig);
static void var2const();

static void console_do(const char *command);
int SetSocketBlockingEnabled(int fd, int blocking);

/* --------------------------------------------------------------------------- */

static int console_printf(const char *fmt, ...) {
    char text[MAXTEXT];
    char server_reply[2000];
    int retval = 0;

    va_list ap;
    va_start(ap, fmt);
    _vsnprintf(text, sizeof(text), fmt, ap);
    va_end(ap);
    text[sizeof(text) - 1] = 0;

    if (console_sock > -1) {
        // Print the line to the command line while we make the console
        // work again
        if (send(console_sock, text, strlen(text), 0) < 0) {
            fprintf(stderr, "Send failed for %s\n", text);
        } else {
            // Receive a reply from the server
            if (recv(console_sock, server_reply, 2000, 0) < 0) {
                fprintf(stderr, "recv failed\n");
            } else {
                if (strncmp(server_reply, "ACK", 3) == 0) {
                    retval = 1;
                }
            }
        }
    }

    return retval;
}

/* --------------------------------------------------------------------------- */

static char *describe_type(DCB_TYPEDEF type, int from) {
    static char buffer[512];
    int i;

    if (!from) {
        buffer[0] = 0;
    }

    switch (type.BaseType[from]) {
    case TYPE_ARRAY:
        for (i = from; type.BaseType[i] == TYPE_ARRAY; i++)
            ;
        describe_type(type, i);
        for (i = from; type.BaseType[i] == TYPE_ARRAY; i++)
            _snprintf(buffer + strlen(buffer), 512 - strlen(buffer), "[%d]", type.Count[i] - 1);
        break;

    case TYPE_STRUCT:
        strcat(buffer, "STRUCT");
        break;

    case TYPE_DWORD:
        strcat(buffer, "DWORD");
        break;

    case TYPE_INT:
        strcat(buffer, "INT");
        break;

    case TYPE_SHORT:
        strcat(buffer, "SHORT");
        break;

    case TYPE_WORD:
        strcat(buffer, "WORD");
        break;

    case TYPE_BYTE:
        strcat(buffer, "BYTE");
        break;

    case TYPE_SBYTE:
        strcat(buffer, "SIGNED BYTE");
        break;

    case TYPE_CHAR:
        strcat(buffer, "CHAR");
        break;

    case TYPE_STRING:
        strcat(buffer, "STRING");
        break;

    case TYPE_FLOAT:
        strcat(buffer, "FLOAT");
        break;

    case TYPE_POINTER:
        describe_type(type, from + 1);
        strcat(buffer, " POINTER");
        break;
    }

    return buffer;
}

/* --------------------------------------------------------------------------- */

static char *show_value(DCB_TYPEDEF type, void *data) {
    static char buffer[512];
    char *newbuffer;
    int subsize;
    unsigned int n;
    unsigned int count;

    switch (type.BaseType[0]) {
    case TYPE_ARRAY:
        count = type.Count[0];

        type    = reduce_type(type);
        subsize = type_size(type);
        if (type.BaseType[0] == TYPE_STRUCT) {
            return "";
        }
        newbuffer = (char *)malloc(512);
        strcpy(newbuffer, "= (");
        for (n = 0; n < count; n++) {
            if (n) {
                strcat(newbuffer, ", ");
            }
            show_value(type, data);
            if (strlen(newbuffer) + strlen(buffer) > 30) {
                strcat(newbuffer, "...");
                break;
            }
            strcat(newbuffer, buffer + 2);
            data = (uint8_t *)data + subsize;
        }
        strcat(newbuffer, ")");
        strcpy(buffer, newbuffer);
        free(newbuffer);
        return buffer;

    case TYPE_STRUCT:
        return "";

    case TYPE_STRING:
        _snprintf(buffer, 512, "= \"%s\"", string_get(*(uint32_t *)data));
        string_discard(*(uint32_t *)data);
        return buffer;

    case TYPE_BYTE:
        _snprintf(buffer, 512, "= %d", *(uint8_t *)data);
        return buffer;

    case TYPE_SBYTE:
        _snprintf(buffer, 512, "= %d", *(int8_t *)data);
        return buffer;

    case TYPE_CHAR:
        if (*(uint8_t *)data >= 32)
            _snprintf(buffer, 512, "= '%c'", *(uint8_t *)data);
        else
            _snprintf(buffer, 512, "= '\\x%02X'", *(uint8_t *)data);
        return buffer;

    case TYPE_FLOAT:
        _snprintf(buffer, 512, "= %g", *(float *)data);
        return buffer;

    case TYPE_WORD:
        _snprintf(buffer, 512, "= %d", *(uint16_t *)data);
        return buffer;

    case TYPE_DWORD:
        _snprintf(buffer, 512, "= %ud", *(uint32_t *)data);
        return buffer;

    case TYPE_SHORT:
        _snprintf(buffer, 512, "= %d", *(int16_t *)data);
        return buffer;

    case TYPE_INT:
        _snprintf(buffer, 512, "= %d", *(int *)data);
        return buffer;

    case TYPE_POINTER:
        _snprintf(buffer, 512, "= 0x%08X", *(uint32_t *)data);
        return buffer;

    default:
        return "?";
    }
}

/* --------------------------------------------------------------------------- */

static void show_struct(int num, char *title, int indent, void *data) {
    int n, count;
    DCB_VAR *vars;

    vars  = dcb.varspace_vars[num];
    count = dcb.varspace[num].NVars;

    for (n = 0; n < count; n++) {
        show_var(vars[n], 0, data ? (uint8_t *)data + vars[n].Offset : 0, title, indent);
    }
}

/* --------------------------------------------------------------------------- */

static void show_var(DCB_VAR var, char *name, void *data, char *title, int indent) {
    char spaces[indent + 1];

    memset(spaces, ' ', indent);
    spaces[indent] = 0;

    if (!name) {
        unsigned int code;

        name = "?";
        for (code = 0; code < dcb.data.NID; code++) {
            if (dcb.id[code].Code == var.ID) {
                name = (char *)dcb.id[code].Name;
                break;
            }
        }
    }

    if (data) {
        console_printf("%s%s %s %s %s", title, spaces, describe_type(var.Type, 0), name,
                       show_value(var.Type, data));
    } else {
        console_printf("%s%s %s %s", title, spaces, describe_type(var.Type, 0), name);
    }

    if (var.Type.BaseType[0] == TYPE_STRUCT) {
        show_struct(var.Type.Members, title, indent + 3, data);
        console_printf("%s%s END", title, spaces);
    }
}

/* --------------------------------------------------------------------------- */

/* Very simple tokenizer */

static void get_token() {
    char *ptr;
    unsigned int n;

    while (isspace(*token_ptr)) {
        token_ptr++;
    }

    if (!*token_ptr) {
        token.type = NOTOKEN;
        return;
    }

    /* Numbers */

    if (ISNUM(*token_ptr)) {
        const char *ptr;
        double num = 0, dec;
        int base   = 10;

        /* Hex/Bin/Octal numbers with the h/b/o sufix */
        ptr = token_ptr;
        while (ISNUM(*ptr) || (*ptr >= 'a' && *ptr <= 'f') || (*ptr >= 'A' && *ptr <= 'F')) {
            ptr++;
        }

        if (*ptr != 'h' && *ptr != 'H' && *ptr != 'o' && *ptr != 'O' &&
            (ptr[-1] == 'b' || ptr[-1] == 'B')) {
            ptr--;
        }

        if (*ptr == 'b' || *ptr == 'B') {
            base = 2;
        }
        if (*ptr == 'h' || *ptr == 'H') {
            base = 16;
        }
        if (*ptr == 'o' || *ptr == 'O') {
            base = 8;
        }

        token.code = 0; /* for ints values */

        /* Calculate the number value */

        while (ISNUM(*token_ptr) || (base > 10 && ISALNUM(*token_ptr))) {
            if (base == 2 && *token_ptr != '0' && *token_ptr != '1') {
                break;
            } else if (base == 8 && (*token_ptr < '0' || *token_ptr > '7')) {
                break;
            } else if (base == 10 && !ISNUM(*token_ptr)) {
                break;
            }
            if (base == 16 && !ISNUM(*token_ptr) &&
                (TOUPPER(*token_ptr) < 'A' || TOUPPER(*token_ptr) > 'F')) {
                break;
            }

            if (ISNUM(*token_ptr)) {
                num        = num * base + (*token_ptr - '0');
                token.code = token.code * base + (*token_ptr - '0');
                token_ptr++;
            }
            if (*token_ptr >= 'a' && *token_ptr <= 'f' && base > 10) {
                num        = num * base + (*token_ptr - 'a' + 10);
                token.code = token.code * base + (*token_ptr - 'a' + 10);
                token_ptr++;
            }
            if (*token_ptr >= 'A' && *token_ptr <= 'F' && base > 10) {
                num        = num * base + (*token_ptr - 'A' + 10);
                token.code = token.code * base + (*token_ptr - 'A' + 10);
                token_ptr++;
            }
        }
        token.type = NUMBER;
        token.code = (float)num;

        /* We have the integer part now - convert to int/float */

        if (*token_ptr == '.' && base == 10) {
            token_ptr++;
            if (!ISNUM(*token_ptr)) {
                token_ptr--;
            } else {
                dec = 1.0 / (double)base;
                while (ISNUM(*token_ptr) || (base > 100 && ISALNUM(*token_ptr))) {
                    if (ISNUM(*token_ptr))
                        num = num + dec * (*token_ptr++ - '0');
                    if (*token_ptr >= 'a' && *token_ptr <= 'f' && base > 10) {
                        num = num + dec * (*token_ptr++ - 'a' + 10);
                    }
                    if (*token_ptr >= 'A' && *token_ptr <= 'F' && base > 10) {
                        num = num + dec * (*token_ptr++ - 'A' + 10);
                    }
                    dec /= (double)base;
                }
                token.type = NUMBER;
                token.code = (float)num;
            }
        }

        /* Skip the base sufix */

        if (base == 16 && (*token_ptr == 'h' || *token_ptr == 'H')) {
            token_ptr++;
        }
        if (base == 8 && (*token_ptr == 'o' || *token_ptr == 'O')) {
            token_ptr++;
        }
        if (base == 2 && (*token_ptr == 'b' || *token_ptr == 'B')) {
            token_ptr++;
        }

        _snprintf(token.name, sizeof(token.name), "%g", token.code);
        return;
    }

    if (*token_ptr == '"' || *token_ptr == '\'') { /* String */
        char c     = *token_ptr++;
        token.type = STRING;
        ptr = token.name;
        while (*token_ptr && *token_ptr != c) {
            *ptr++ = *token_ptr++;
        }
        if (*token_ptr == c) {
            token_ptr++;
        }
        *ptr = 0;
        return;
    }

    ptr    = token.name;
    *ptr++ = TOUPPER(*token_ptr);
    if (ISWORDCHAR(*token_ptr++)) {
        while (ISWORDCHAR(*token_ptr)) {
            *ptr++ = TOUPPER(*token_ptr++);
        }
    }
    *ptr = 0;

    for (n = 0; n < dcb.data.NID; n++) {
        if (strcmp((char *)dcb.id[n].Name, token.name) == 0) {
            token.type = IDENTIFIER;
            token.code = dcb.id[n].Code;
            /*            strcpy( token.name, (char *)dcb.id[n].Name ) ; */
            return;
        }
    }

    token.type = OPERATOR;
}

/* --------------------------------------------------------------------------- */

static DCB_TYPEDEF reduce_type(DCB_TYPEDEF orig) {
    int n;
    for (n = 0; n < MAX_TYPECHUNKS - 1; n++) {
        orig.BaseType[n] = orig.BaseType[n + 1];
        orig.Count[n]    = orig.Count[n + 1];
    }
    return orig;
}

/* --------------------------------------------------------------------------- */

static void var2const() {
    while (result.type == T_VARIABLE && result.var.Type.BaseType[0] == TYPE_ARRAY) {
        result.var.Type = reduce_type(result.var.Type);
    }

    if (result.type == T_VARIABLE && result.var.Type.BaseType[0] == TYPE_STRING) {
        result.type = T_STRING;
        strncpy(result.name, string_get(*(int *)(result.data)), 127);
        result.name[127] = 0;
    }

    if (result.type == T_VARIABLE && result.var.Type.BaseType[0] == TYPE_FLOAT) {
        result.type  = T_CONSTANT;
        result.value = *(float *)(result.data);
    }

    if (result.type == T_VARIABLE &&
        (result.var.Type.BaseType[0] == TYPE_DWORD || result.var.Type.BaseType[0] == TYPE_INT)) {
        result.type  = T_CONSTANT;
        result.value = *(int *)(result.data);
    }

    if (result.type == T_VARIABLE &&
        (result.var.Type.BaseType[0] == TYPE_WORD || result.var.Type.BaseType[0] == TYPE_SHORT)) {
        result.type  = T_CONSTANT;
        result.value = *(int16_t *)(result.data);
    }

    if (result.type == T_VARIABLE &&
        (result.var.Type.BaseType[0] == TYPE_BYTE || result.var.Type.BaseType[0] == TYPE_SBYTE)) {
        result.type  = T_CONSTANT;
        result.value = *(int8_t *)(result.data);
    }

    if (result.type == T_VARIABLE && result.var.Type.BaseType[0] == TYPE_CHAR) {
        result.type = T_STRING;
        if (*(uint8_t *)result.data >= 32) {
            _snprintf(result.name, sizeof(result.name), "%c", *(uint8_t *)result.data);
        } else {
            _snprintf(result.name, sizeof(result.name), "\\x%02X", *(uint8_t *)result.data);
        }
    }
}

/* --------------------------------------------------------------------------- */

static int type_size(DCB_TYPEDEF orig) {
    unsigned int n, total;

    switch (orig.BaseType[0]) {
    case TYPE_ARRAY:
        return orig.Count[0] * type_size(reduce_type(orig));

    case TYPE_POINTER:
    case TYPE_STRING:
    case TYPE_DWORD:
    case TYPE_FLOAT:
    case TYPE_INT:
        return 4;

    case TYPE_WORD:
    case TYPE_SHORT:
        return 2;

    case TYPE_BYTE:
    case TYPE_SBYTE:
    case TYPE_CHAR:
        return 1;

    case TYPE_STRUCT:
        total = 0;
        for (n = 0; n < dcb.varspace[orig.Members].NVars; n++) {
            total += type_size(dcb.varspace_vars[orig.Members][n].Type);
        }
        return total;

    default:
        return 0;
    }
}

/* --------------------------------------------------------------------------- */

static void eval_local(DCB_PROC *proc, INSTANCE *i) {
    unsigned int n;

    for (n = 0; n < dcb.data.NLocVars; n++) {
        if (dcb.locvar[n].ID == token.code) {
            strcpy(result.name, token.name);
            result.type = T_VARIABLE;
            result.var  = dcb.locvar[n];
            result.data = (uint8_t *)i->locdata + dcb.locvar[n].Offset;
            get_token();
            return;
        }
    }

    for (n = 0; n < proc->data.NPriVars; n++) {
        if (proc->privar[n].ID == token.code) {
            strcpy(result.name, token.name);
            result.type = T_VARIABLE;
            result.var  = proc->privar[n];
            result.data = (uint8_t *)i->pridata + proc->privar[n].Offset;
            get_token();
            return;
        }
    }

    for (n = 0; n < proc->data.NPubVars; n++) {
        if (proc->pubvar[n].ID == token.code) {
            strcpy(result.name, token.name);
            result.type = T_VARIABLE;
            result.var  = proc->pubvar[n];
            result.data = (uint8_t *)i->pubdata + proc->pubvar[n].Offset;
            get_token();
            return;
        }
    }

    console_printf("\033[38;2;192;0;0mLocal or private or public variable not found\033[0m");
    result.type = T_ERROR;
}

/* --------------------------------------------------------------------------- */

static void eval_immediate() {
    unsigned int n;

    if (token.type == NUMBER) {
        result.type  = T_CONSTANT;
        result.value = token.code;
        get_token();
        return;
    }

    if (token.type == STRING) {
        result.type = T_STRING;
        _snprintf(result.name, sizeof(result.name), "%s", token.name);
        get_token();
        return;
    }

    if (token.type != IDENTIFIER) {
        console_printf("\033[38;2;192;0;0mNot a valid expression\033[0m");
        result.type = T_ERROR;
        return;
    }

    if (token.name[0] == '(') {
        get_token();
        eval_subexpression();
        if (token.name[0] != ')') {
            console_printf("\033[38;2;192;0;0mUnbalanced parens\033[0m");
            result.type = T_ERROR;
            return;
        }
        get_token();
        return;
    }

    if (token.name[0] == '-') {
        get_token();
        eval_immediate();
        var2const();
        if (result.type != T_CONSTANT) {
            console_printf("\033[38;2;192;0;0mOperand is not a number\033[0m");
            result.type = T_ERROR;
            return;
        }
        result.value = -result.value;
        _snprintf(result.name, sizeof(result.name), "%g", result.value);
        return;
    }

    for (n = 0; n < dcb.data.NGloVars; n++) {
        if (dcb.glovar[n].ID == token.code) {
            strcpy(result.name, token.name);
            result.type = T_VARIABLE;
            result.var  = dcb.glovar[n];
            result.data = (uint8_t *)globaldata + dcb.glovar[n].Offset;

            get_token();
            return;
        }
    }

    if (strcmp(token.name, "MAIN") == 0)
        token.code = dcb.proc[0].data.ID;

    for (n = 0; n < dcb.data.NProcs; n++) {
        if (dcb.proc[n].data.ID == token.code) {
            INSTANCE *i = first_instance;

            while (i) {
                if (i->proc->type == (int)n)
                    break;
                i = i->next;
            }
            if (!i) {
                console_printf("\033[38;2;192;0;0mNo instance of process %s is active\033[0m",
                               token.name);
                result.type = T_ERROR;
                return;
            }

            get_token();
            if (token.name[0] != '.') {
                console_printf("\033[38;2;192;0;0mInvalid use of a process name\033[0m");
                result.type = T_ERROR;
                return;
            }
            get_token();
            eval_local(&dcb.proc[n], i);
            return;
        }
    }

    console_printf("\033[38;2;192;0;0mVariable does not exist (%s)\033[0m", token.name);
    result.type = T_ERROR;
    return;
}

/* --------------------------------------------------------------------------- */

static void eval_value() {
    eval_immediate();
    if (result.type == T_ERROR)
        return;

    for (;;) {
        if (token.name[0] == '.') {
            DCB_VARSPACE *v;
            DCB_VAR *var;
            unsigned int n;

            var2const();
            if (result.type == T_CONSTANT) {
                INSTANCE *i;
                i = instance_get((int)result.value);
                if (!i) {
                    result.type = T_ERROR;
                    console_printf("\033[38;2;192;0;0mInstance %d does not exist\033[0m",
                                   (int)result.value);
                    return;
                }
                get_token();
                eval_local(&dcb.proc[i->proc->type], i);
                continue;
            }

            if (result.type != T_VARIABLE || result.var.Type.BaseType[0] != TYPE_STRUCT) {
                console_printf("\033[38;2;192;0;0m%s is not an struct\033[0m", result.name);
                result.type = T_ERROR;
                return;
            }
            get_token();
            if (token.type != IDENTIFIER) {
                console_printf("\033[38;2;192;0;0m%s is not a member\033[0m", token.name);
                result.type = T_ERROR;
                return;
            }

            v   = &dcb.varspace[result.var.Type.Members];
            var = dcb.varspace_vars[result.var.Type.Members];
            for (n = 0; n < v->NVars; n++) {
                if (var[n].ID == token.code)
                    break;
            }
            if (n == v->NVars) {
                console_printf("\033[38;2;192;0;0m%s is not a member\033[0m", token.name);
                result.type = T_ERROR;
                return;
            }

            result.type = T_VARIABLE;
            result.var  = var[n];
            result.data = (uint8_t *)result.data + var[n].Offset;
            strcat(result.name, ".");
            strcat(result.name, token.name);
            get_token();
            continue;
        }

        if (token.name[0] == '[') {
            DCB_VAR i    = result.var;
            void *i_data = result.data;
            char name[256];

            if (result.type != T_VARIABLE || result.var.Type.BaseType[0] != TYPE_ARRAY) {
                console_printf("\033[38;2;192;0;0m%s is not an array\033[0m", result.name);
                result.type = T_ERROR;
                return;
            }

            strcpy(name, result.name);
            get_token();
            eval_subexpression();
            if (result.type == T_ERROR) {
                return;
            }
            if (token.name[0] == ']') {
                get_token();
            }
            var2const();

            if (result.type != T_CONSTANT) {
                console_printf("\033[38;2;192;0;0m%s is not an integer\033[0m", result.name);
                result.type = T_ERROR;
                return;
            }
            if (result.value < 0) {
                console_printf("\033[38;2;192;0;0mIndex (%d) less than zero\033[0m", result.value);
                result.type = T_ERROR;
                return;
            }
            if (result.value >= i.Type.Count[0]) {
                console_printf("\033[38;2;192;0;0mIndex (%d) out of bounds\033[0m", result.value);
                result.type = T_ERROR;
                return;
            }

            result.type     = T_VARIABLE;
            result.var      = i;
            result.var.Type = reduce_type(i.Type);
            result.data = (uint8_t *)i_data + (int)result.value * type_size(result.var.Type);
            _snprintf(result.name, sizeof(result.name), "%s[%d]", name, (int)result.value);
            continue;
        }

        break;
    }
}

/* --------------------------------------------------------------------------- */

static void eval_factor() {
    double base = 1;
    int op      = 0;

    for (;;) {
        eval_value();
        if (result.type == T_ERROR) {
            return;
        }
        if (!strchr("*/%", token.name[0]) && !op) {
            return;
        }
        var2const();
        if (result.type != T_CONSTANT) {
            result.type = T_ERROR;
            console_printf("\033[38;2;192;0;0mOperand is not a number\033[0m");
            return;
        }
        if (!op) {
            op = 1;
        }
        if (op > 1 && !result.value) {
            result.type = T_ERROR;
            console_printf("\033[38;2;192;0;0mDivide by zero\033[0m");
            return;
        }
        if (op == 1) {
            base *= result.value;
        }
        if (op == 2) {
            base /= result.value;
        }
        if (op == 3) {
            base = (int)base % (int)result.value;
        }
        if (!strchr("*/%", token.name[0])) {
            result.type  = T_CONSTANT;
            result.value = base;
            _snprintf(result.name, sizeof(result.name), "%g", base);
            return;
        }
        op = (token.name[0] == '*') ? 1 : (token.name[0] == '/') ? 2 : 3;
        get_token();
    }
}

/* --------------------------------------------------------------------------- */

static void eval_subexpression() {
    double base = 0;
    int op      = 0;

    for (;;) {
        eval_factor();
        if (result.type == T_ERROR) {
            return;
        }
        if (token.name[0] != '+' && token.name[0] != '-' && !op) {
            return;
        }
        var2const();
        if (result.type != T_CONSTANT) {
            result.type = T_ERROR;
            console_printf("\033[38;2;192;0;0mOperand is not a number\033[0m");
            return;
        }
        if (!op) {
            op = 1;
        }
        base += op * result.value;
        if (token.name[0] != '+' && token.name[0] != '-') {
            result.type  = T_CONSTANT;
            result.value = base;
            _snprintf(result.name, sizeof(result.name), "%g", base);
            return;
        }
        op = (token.name[0] == '+') ? 1 : -1;
        get_token();
    }
}

/* --------------------------------------------------------------------------- */

static char *eval_expression(const char *here, int interactive) {
    static char buffer[1024];
    static char part[1024];

    while (*here == ' ') {
        here++;
    }

    token_ptr = here;
    get_token();
    eval_subexpression();

    if (token.type != NOTOKEN && token.name[0] != ',' && token.name[0] != '=') {
        if (result.type != T_ERROR) {
            console_printf("\033[38;2;192;0;0mInvalid expression\033[0m");
            result.type = T_ERROR;
        }
        return 0;
    }

    memset(part, 0, sizeof(buffer));
    strncpy(part, here, token_ptr - here - ((token.type != NOTOKEN) ? 1 : 0));

    if (result.type == T_CONSTANT) {
        _snprintf(buffer, 1024, "%s = %g", part, result.value);
        if (interactive) {
            console_printf("\033[0m%s", buffer);
        }
    } else if (result.type == T_STRING) {
        if (interactive) {
            console_printf("\033[0m%s = \"%s\"", part, result.name);
        }
    } else if (result.type == T_VARIABLE) {
        lvalue = result;

        if (token.name[0] == '=') {
            if (lvalue.type != T_VARIABLE) {
                strcpy(buffer, "Not an lvalue");
                if (interactive) {
                    console_printf("\033[38;2;192;0;0m%s\033[0m", buffer);
                }
                return buffer;
            }
            get_token();
            eval_subexpression();
            if (result.type == T_ERROR) {
                return "";
            }
            var2const();

            if ((lvalue.var.Type.BaseType[0] == TYPE_DWORD ||
                 lvalue.var.Type.BaseType[0] == TYPE_INT) &&
                result.type == T_CONSTANT)
                *(int *)(lvalue.data) = (int)result.value;
            else if ((lvalue.var.Type.BaseType[0] == TYPE_WORD ||
                      lvalue.var.Type.BaseType[0] == TYPE_SHORT) &&
                     result.type == T_CONSTANT)
                *(uint16_t *)(lvalue.data) = (uint16_t)result.value;
            else if ((lvalue.var.Type.BaseType[0] == TYPE_BYTE ||
                      lvalue.var.Type.BaseType[0] == TYPE_SBYTE) &&
                     result.type == T_CONSTANT)
                *(uint8_t *)(lvalue.data) = (uint8_t)result.value;
            else if (lvalue.var.Type.BaseType[0] == TYPE_CHAR && result.type == T_STRING) {
                if (*result.name == '\\' && *(result.name + 1) == 'x')
                    *(uint8_t *)(lvalue.data) = (uint8_t)strtol(result.name + 2, NULL, 16);
                else
                    *(uint8_t *)(lvalue.data) = (uint8_t) * (result.name);
            } else if (lvalue.var.Type.BaseType[0] == TYPE_FLOAT && result.type == T_CONSTANT)
                *(float *)(lvalue.data) = (float)result.value;
            else if (lvalue.var.Type.BaseType[0] == TYPE_STRING && result.type == T_STRING) {
                string_discard(*(uint32_t *)lvalue.data);
                *(uint32_t *)(lvalue.data) = string_new(result.name);
                string_use(*(uint32_t *)lvalue.data);
            } else {
                strcpy(buffer, "Invalid assignation");
                if (interactive) {
                    console_printf("\033[38;2;192;0;0m%s\033[0m", buffer);
                }
                return buffer;
            }
        }

        if (interactive) {
            show_var(lvalue.var, lvalue.name, lvalue.data, "", 0);
        } else {
            strcpy(buffer, part);
            strcat(buffer, " ");
            strcat(buffer, show_value(lvalue.var.Type, lvalue.data));
        }
    }

    if (token.name[0] == ',') {
        char *temporary = strdup(buffer);
        int size        = strlen(temporary);

        if (eval_expression(token_ptr, interactive) == 0) {
            free(temporary);
            return 0;
        }
        if (strlen(buffer) + size < 1020 && !interactive) {
            memmove(buffer + size + 2, buffer, strlen(buffer) + 1);
            memcpy(buffer, temporary, size);
            memcpy(buffer + size, ", ", 2);
        }
        free(temporary);
        return buffer;
    }

    return buffer;
}

/* --------------------------------------------------------------------------- */

static void console_instance_dump(INSTANCE *father, int indent) {
    INSTANCE *i, *next;
    PROCDEF *proc;
    DCB_PROC *dcbproc;
    char buffer[128];
    char line[128];
    int n, nid, bigbro, son;

    i = father;
    if (!father) {
        i = first_instance;
    }

    proc    = i->proc;
    dcbproc = &dcb.proc[proc->type];

    nid = LOCDWORD(mod_debug, i, PROCESS_ID);
    if (dcb.data.NSourceFiles && dcbproc->data.ID) {
        sprintf(buffer, "%s", getid_name(dcbproc->data.ID));
    } else {
        sprintf(buffer, "%s", (proc->type == 0) ? "MAIN" : "PROC");
    }

    line[0] = 0;
    for (n = 0; n < indent - 1; n++) {
        strcat(line, " \x03 ");
    }

    sprintf(line + strlen(line), " %-12s ", buffer);

    n = strlen(line) % 4;
    while (n && (n++ < 4)) {
        strcat(line, " ");
    }
    sprintf(line + strlen(line), "%7d", nid);

    if (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) {
        strcat(line, "[W]");
    }
    switch (LOCDWORD(mod_debug, i, STATUS) & ~STATUS_WAITING_MASK) {
    case STATUS_DEAD:
        strcat(line, "[D]");
        break;
    case STATUS_KILLED:
        strcat(line, "[K]");
        break;
    case STATUS_RUNNING:
        strcat(line, "   ");
        break;
    case STATUS_SLEEPING:
        strcat(line, "[S]");
        break;
    case STATUS_FROZEN:
        strcat(line, "[F]");
        break;
    }

    console_printf("\033[0m%s", line);

    if (!(son = LOCDWORD(mod_debug, i, SON))) {
        return;
    }

    next = instance_get(son);
    if (!next) {
        console_printf("\033[38;2;192;0;0m\12**PANIC**\7 SON %d does not exist\033[0m", son);
    }

    i = next;

    while (i) {
        proc    = i->proc;
        dcbproc = &dcb.proc[proc->type];

        if (LOCDWORD(mod_debug, i, SON)) {
            console_instance_dump(i, indent + 1);
        } else {
            nid = LOCDWORD(mod_debug, i, PROCESS_ID);
            if (dcb.data.NSourceFiles && dcbproc->data.ID) {
                sprintf(buffer, "%s", getid_name(dcbproc->data.ID));
            } else {
                sprintf(buffer, "%s", (proc->type == 0) ? "MAIN" : "PROC");
            }

            line[0] = 0;
            for (n = 0; n < indent; n++) {
                strcat(line, " \x03 ");
            }

            sprintf(line + strlen(line), " \x01\x02 %-12s ", buffer);

            n = strlen(line) % 4;
            while (n && (n++ < 4)) {
                strcat(line, " ");
            }
            sprintf(line + strlen(line), "%7d", nid);

            if (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) {
                strcat(line, "[W]");
            }
            switch (LOCDWORD(mod_debug, i, STATUS) & ~STATUS_WAITING_MASK) {
            case STATUS_DEAD:
                strcat(line, "[D]");
                break;
            case STATUS_KILLED:
                strcat(line, "[K]");
                break;
            case STATUS_RUNNING:
                strcat(line, "   ");
                break;
            case STATUS_SLEEPING:
                strcat(line, "[S]");
                break;
            case STATUS_FROZEN:
                strcat(line, "[F]");
                break;
            }
            console_printf("\033[0m%s", line);
        }

        if ((bigbro = LOCDWORD(mod_debug, i, BIGBRO))) {
            next = instance_get(bigbro);
            if (!next) {
                console_printf("\033[38;2;192;0;0m\12**PANIC**\7 BIGBRO %d does not exist\033[0m",
                               bigbro);
            }
            i = next;
        } else {
            break;
        }
    }
}

/* --------------------------------------------------------------------------- */
/* Muestra el árbol de instancias */

static void console_instance_dump_all() {
    INSTANCE *i;
    int father;

    console_printf("\033[38;2;0;192;0mINSTANCES TREE\033[0m\n\n");

    for (i = first_instance; i; i = i->next) {
        if (!(father = LOCDWORD(mod_debug, i, FATHER)) || !instance_get(father)) {
            console_instance_dump(i, 1);
        }
    }

    console_printf("\n");
}

/* --------------------------------------------------------------------------- */

static void console_instance_dump_all_brief() {
    INSTANCE *i;
    char status[30];
    int father;

    console_printf("\033[38;2;0;192;0mINSTANCES BRIEF LIST\033[0m\n\n");
    console_printf("\033[38;2;0;192;0mId         Father     Status        Name\033[0m\n");

    for (i = first_instance; i; i = i->next) {
        status[0] = '\0';
        if (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK)
            strcpy(status, "\033[38;2;128;128;128mwait\033[0m+");

        switch (LOCDWORD(mod_debug, i, STATUS) & ~STATUS_WAITING_MASK) {
        case STATUS_DEAD:
            strcat(status, "\033[38;2;192;192;0mdead\033[0m    ");
            break;
        case STATUS_KILLED:
            strcat(status, "\033[38;2;192;0;0mkilled\033[0m  ");
            break;
        case STATUS_SLEEPING:
            strcat(status, "\033[38;2;0;0;255msleeping\033[0m");
            break;
        case STATUS_FROZEN:
            strcat(status, "\033[38;2;0;192;192mfrozen\033[0m  ");
            break;
        case STATUS_RUNNING:
            strcat(status, "\033[38;2;0;255;0mrunning\033[0m ");
            break;
        }

        if (!(LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK))
            strcat(status, "     ");

        father = LOCDWORD(mod_debug, i, FATHER);

        console_printf("%-10d %s%-10d\033[0m %s \033[38;2;255;255;255m%s\033[0m\n",
                       LOCDWORD(mod_debug, i, PROCESS_ID),
                       instance_get(father) ? "" : "\033[38;2;192;0;0m", father, status,
                       (dcb.data.NSourceFiles && dcb.proc[i->proc->type].data.ID)
                           ? getid_name(dcb.proc[i->proc->type].data.ID)
                           : ((i->proc->type == 0) ? "Main" : "proc"));
    }

    console_printf("\n");
}

/* --------------------------------------------------------------------------- */

static int console_list_current                = 0;
static INSTANCE *console_list_current_instance = NULL;

#define WINDOW_LIST_COLS 40

/* --------------------------------------------------------------------------- */

static INSTANCE *findproc(INSTANCE *last, char *action, char *ptr) {
    INSTANCE *i = NULL;
    char *aptr;
    int procno = 0;
    int n;

    if (*ptr) {
        if (*ptr >= '0' && *ptr <= '9') {
            if (last)
                return NULL;
            procno = atoi(ptr);
            for (i = first_instance; i; i = i->next)
                if (LOCDWORD(mod_debug, i, PROCESS_ID) == procno)
                    break;
            if (!i) {
                console_printf("\033[38;2;192;0;0mInstance %d does not exist\033[0m", procno);
                return NULL;
            }
        } else {
            aptr = action;
            while (ISWORDCHAR(*ptr)) {
                *aptr++ = TOUPPER(*ptr);
                ptr++;
            }
            *aptr = 0;

            for (n = 0; n < (int)dcb.data.NID; n++)
                if (strcmp((char *)dcb.id[n].Name, action) == 0)
                    break;
            for (procno = 0; procno < (int)dcb.data.NProcs; procno++)
                if (dcb.proc[procno].data.ID == dcb.id[n].Code)
                    break;
            if (procno == (int)dcb.data.NProcs) {
                console_printf("\033[38;2;192;0;0mUnknown process %s\033[0m", action);
                return NULL;
            }
            for (i = last ? last->next : first_instance; i; i = i->next)
                if (i->proc->type == procno)
                    break;
            if (!i && !last) {
                console_printf("\033[38;2;192;0;0mNo instance of process %s created\033[0m",
                               action);
                return NULL;
            }
        }
    }

    return (i);
}

/* --------------------------------------------------------------------------- */

static void console_do(const char *command) {
    char *ptr, *aptr;
    char action[256];
    unsigned int var;
    int n, procno = 0;
    PROCDEF *p    = NULL;
    INSTANCE *i   = NULL;

    ptr = (char *)command;
    while (*ptr && *ptr != ' ')
        ptr++;
    strncpy(action, command, ptr - command);
    action[ptr - command] = 0;
    while (*ptr == ' ')
        ptr++;
    aptr = action;
    while (*aptr) {
        *aptr = TOUPPER(*aptr);
        aptr++;
    }

    /* Comandos */

    if (strcmp(action, "HELP") == 0) {
        console_printf(HELPTXT);
        return;
    }

    if (strcmp(action, "GO") == 0) {
        debug_mode         = 0;
        debug_on_frame     = 0;
        force_debug        = 0;
        debug_next         = 0;
        break_on_next_proc = 0;
        return;
    }

    if (strcmp(action, "NEXTFRAME") == 0) {
        break_on_next_proc = 0;
        debug_mode         = 0;
        debug_on_frame     = 1;
        force_debug        = 0;
        debug_next         = 0;
        break_on_next_proc = 0;
        return;
    }

    if (strcmp(action, "NEXTPROC") == 0) {
        debug_mode         = 0;
        debug_on_frame     = 0;
        force_debug        = 0;
        debug_next         = 0;
        break_on_next_proc = 1;
        return;
    }

    if (strcmp(action, "TRACE") == 0) {
        debug_mode         = 0;
        debug_on_frame     = 0;
        force_debug        = 0;
        debug_next         = 1;
        break_on_next_proc = 0;
        return;
    }

    if (strcmp(action, "BREAK") == 0) {
        if (*ptr) {
            if (*ptr >= '0' && *ptr <= '9') {
                procno = atoi(ptr);
                for (i = first_instance; i; i = i->next) {
                    if (LOCDWORD(mod_debug, i, PROCESS_ID) == procno) {
                        break;
                    }
                }
                if (!i) {
                    console_printf("\033[38;2;192;0;0mInstance %d does not exist\033[0m", procno);
                } else {
                    i->breakpoint = 1;
                    console_printf("\033[0mOK");
                }
            } else {
                aptr = action;
                while (ISWORDCHAR(*ptr)) {
                    *aptr++ = TOUPPER(*ptr);
                    ptr++;
                }
                *aptr = 0;

                if (*action) {
                    p = procdef_get_by_name(action);
                    if (!p) {
                        console_printf("\033[38;2;192;0;0mProcess type %d does not exist\033[0m",
                                       action);
                    } else {
                        p->breakpoint = 1;
                        console_printf("\033[0mOK");
                    }
                }
            }
        } else {
            int f = 0;
            for (n = 0; n < procdef_count; n++) {
                if (procs[n].breakpoint) {
                    if (!f) {
                        console_printf("\033[38;2;0;192;0mPROCESS TYPE BREAKPOINTS\033[0m\n\n");
                        f = 1;
                    }
                    console_printf("\033[0m%s\n", procs[n].name);
                }
            }
            if (f) {
                console_printf("\n");
            }

            f = 0;
            for (i = first_instance; i; i = i->next) {
                if (i->breakpoint) {
                    if (!f) {
                        console_printf("\033[38;2;0;192;0mPROCESS BREAKPOINTS\033[0m\n\n");
                        f = 1;
                    }
                    console_printf("\033[0m%d", LOCDWORD(mod_debug, i, PROCESS_ID));
                }
            }
            if (f) {
                console_printf("\n");
            }
        }
        return;
    }

    if (strcmp(action, "BREAKALL") == 0) {
        for (i = first_instance; i; i = i->next) {
            i->breakpoint = 1;
        }
        console_printf("\033[0mOK");
        return;
    }

    if (strcmp(action, "BREAKALLTYPES") == 0) {
        for (n = 0; n < procdef_count; n++) {
            procs[n].breakpoint = 1;
        }
        console_printf("\033[0mOK");
        return;
    }

    if (strcmp(action, "DELETEALL") == 0) {
        for (i = first_instance; i; i = i->next) {
            i->breakpoint = 0;
        }
        console_printf("\033[0mOK");
        return;
    }

    if (strcmp(action, "DELETEALLTYPES") == 0) {
        for (n = 0; n < procdef_count; n++) {
            procs[n].breakpoint = 0;
        }
        console_printf("\033[0mOK");
        return;
    }

    if (strcmp(action, "DELETE") == 0) {
        if (*ptr) {
            if (*ptr >= '0' && *ptr <= '9') {
                procno = atoi(ptr);
                for (i = first_instance; i; i = i->next) {
                    if (LOCDWORD(mod_debug, i, PROCESS_ID) == procno) {
                        break;
                    }
                }
                if (!i) {
                    console_printf("\033[38;2;192;0;0mInstance %d does not exist\033[0m", procno);
                } else {
                    i->breakpoint = 0;
                    console_printf("\033[0mOK");
                }
            } else {
                aptr = action;
                while (ISWORDCHAR(*ptr)) {
                    *aptr++ = TOUPPER(*ptr);
                    ptr++;
                }
                *aptr = 0;

                p = procdef_get_by_name(action);
                if (!p) {
                    console_printf("\033[38;2;192;0;0mProcess type %d does not exist\033[0m",
                                   procno);
                } else {
                    p->breakpoint = 0;
                    console_printf("\033[0mOK");
                }
            }
        }
        return;
    }

    if (strcmp(action, "STRINGS") == 0) {
        string_dump(console_printf);
        return;
    }

    if (strcmp(action, "INSTANCES") == 0) {
        console_instance_dump_all();
        return;
    }

    if (strcmp(action, "GLOBALS") == 0) {
        for (var = 0; var < dcb.data.NGloVars; var++) {
            DCB_VAR *v = &dcb.glovar[var];
            show_var(*v, 0, (uint8_t *)globaldata + v->Offset, "[GLO]", 0);
        }
        console_printf("\n");
        return;
    }

    if (strcmp(action, "LOCALS") == 0 || strcmp(action, "PRIVATES") == 0 ||
        strcmp(action, "PUBLICS") == 0) {
        int show_locals = action[0] == 'L';
        int show_public = action[0] == 'P' && action[1] == 'U';

        i = findproc(NULL, action, ptr);

        if (show_locals) {
            for (var = 0; var < dcb.data.NLocVars; var++) {
                DCB_VAR *v = &dcb.locvar[var];
                show_var(*v, 0, i ? (char *)i->locdata + v->Offset : 0, "[LOC]", 0);
            }
        } else if (show_public) {
            if (!i) {
                console_printf("\033[0mUse: PUBLICS process");
                return;
            }
            for (var = 0; var < dcb.proc[i->proc->type].data.NPubVars; var++) {
                DCB_VAR *v = &dcb.proc[i->proc->type].pubvar[var];

                /* Unnamed private vars are temporary params and loop
                   counters, and are ignored by this command */
                if ((int)v->ID >= 0) {
                    show_var(*v, 0, (char *)i->pubdata + v->Offset, "[PUB]", 0);
                }
            }
        } else {
            if (!i) {
                console_printf("\033[0mUse: PRIVATES process");
                return;
            }
            for (var = 0; var < dcb.proc[i->proc->type].data.NPriVars; var++) {
                DCB_VAR *v = &dcb.proc[i->proc->type].privar[var];

                /* Unnamed private vars are temporary params and loop
                   counters, and are ignored by this command */
                if ((int)v->ID >= 0) {
                    show_var(*v, 0, (char *)i->pridata + v->Offset, "[PRI]", 0);
                }
            }
        }
        console_printf("\n");
        return;
    }

    if (strcmp(action, "SHOW") == 0) {
        if (*ptr) {
            char *res = eval_expression(ptr, 0);

            if (!res || result.type == T_STRING) {
                console_printf("\033[38;2;192;0;0mInvalid argument\033[0m");
                return;
            }

            for (n = 0; n < MAX_EXPRESSIONS; n++) {
                if (show_expression[n] && !strcmp(show_expression[n], ptr)) {
                    console_printf("\033[38;2;192;0;0mAlready exists\033[0m");
                    return;
                }
            }

            for (n = 0; n < MAX_EXPRESSIONS; n++) {
                if (!show_expression[n]) {
                    show_expression[n] = strdup(ptr);
                    show_expression_count++;
                    console_printf("\033[0mOK");
                    return;
                }
            }

            console_printf("\033[38;2;192;0;0mNo more expressions are possibles\033[0m");
        } else {
            int nn = 0;
            for (n = 0; n < MAX_EXPRESSIONS; n++) {
                if (show_expression[n]) {
                    console_printf("%d: %s", n + 1, show_expression[n]);
                    nn++;
                }
            }

            if (!nn) {
                console_printf("\033[38;2;192;0;0mNo expressions availables\033[0m");
            }
        }

        return;
    }

    if (strcmp(action, "SHOWDEL") == 0) {
        if (*ptr) {
            char *p = ptr;

            while (ISNUM(*p)) {
                p++;
            }

            if (ISNUM(*ptr)) {
                int pos = atol(ptr) - 1;
                if (pos >= 0 && pos < MAX_EXPRESSIONS && show_expression[pos]) {
                    free(show_expression[pos]);
                    show_expression[pos] = NULL;
                    show_expression_count--;
                    console_printf("\033[0mOK");
                    return;
                }
            }
        }

        console_printf("\033[38;2;192;0;0mInvalid argument\033[0m");

        return;
    }

    if (strcmp(action, "SHOWDELALL") == 0) {
        for (n = 0; n < MAX_EXPRESSIONS; n++) {
            if (show_expression[n]) {
                free(show_expression[n]);
                show_expression[n] = NULL;
                show_expression_count--;
            }
        }
        console_printf("\033[0mOK");
        return;
    }

    if (strcmp(action, "VARS") == 0) {
        for (var = 0; var < N_CONSOLE_VARS; var++) {
            switch (console_vars[var].type) {
            case CON_DWORD:
                console_printf("\033[0m%s = %d\n", console_vars[var].name,
                               *(int *)console_vars[var].value);
                break;

            case CON_DWORD_HEX:
                console_printf("\033[0m%s = %08Xh\n", console_vars[var].name,
                               *(int *)console_vars[var].value);
                break;
            }
        }
        console_printf("\n");
        return;
    }

    if (strcmp(action, "RUN") == 0) {
        if (*ptr) {
            aptr = action;
            while (ISWORDCHAR(*ptr)) {
                *aptr++ = TOUPPER(*ptr);
                ptr++;
            }
            *aptr = 0;

            if (*action) {
                int i;
                INSTANCE *inst;
                p = procdef_get_by_name(action);
                if (p) {
                    token_ptr = ptr;
                    console_printf("\033[0m%s", ptr);
                    inst = instance_new(p, NULL);

                    for (i = 0; i < p->params; i++) {
                        int type = dcb.proc[p->type].privar[i].Type.BaseType[0];
                        get_token();
                        eval_subexpression();

                        if (result.type == T_VARIABLE) {
                            var2const();
                        }

                        switch (result.type) {
                        case T_CONSTANT:
                            switch (type) {
                            case TYPE_FLOAT:
                                PRIDWORD(inst, 4 * i) = *(int *)&result.value;
                                break;

                            case TYPE_INT:
                            case TYPE_DWORD:
                            case TYPE_POINTER:
                            case TYPE_SHORT:
                            case TYPE_WORD:
                            case TYPE_BYTE:
                            case TYPE_SBYTE:
                            case TYPE_CHAR:
                                PRIDWORD(inst, 4 * i) = (int)result.value;
                                break;

                            case TYPE_STRING:
                            default:
                                instance_destroy(inst);
                                console_printf("\033[38;2;192;0;0mInvalid argument %d\033[0m", i);
                                return;
                            }
                            break;

                        case T_STRING:
                            PRIDWORD(inst, 4 * i) = (int)string_new(result.name);
                            string_use(PRIDWORD(inst, 4 * i));
                            break;

                        case T_VARIABLE:
                        default:
                            instance_destroy(inst);
                            console_printf("\033[38;2;192;0;0mInvalid argument %d\033[0m", i);
                            return;
                        }
                    }
                    console_printf("\033[0mProcess %s is executed", p->name);
                } else {
                    console_printf("\033[38;2;192;0;0mProcess %s not found\033[0m", action);
                }
                return;
            }
        }
    }

    if (strcmp(action, "KILLALL") == 0 || strcmp(action, "SLEEPALL") == 0 ||
        strcmp(action, "WAKEUPALL") == 0 || strcmp(action, "FREEZEALL") == 0) {
        char act      = *action;
        int found     = 0;
        char *oaction = strdup(action);
        char *optr    = ptr;

        i = NULL;
        while ((i = findproc(i, action, ptr))) {
            found = 1;
            switch (act) {
            case 'K':
                LOCDWORD(mod_debug, i, STATUS) =
                    (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) | STATUS_KILLED;
                break;

            case 'W':
                LOCDWORD(mod_debug, i, STATUS) =
                    (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) | STATUS_RUNNING;
                break;

            case 'S':
                LOCDWORD(mod_debug, i, STATUS) =
                    (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) | STATUS_SLEEPING;
                break;

            case 'F':
                LOCDWORD(mod_debug, i, STATUS) =
                    (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) | STATUS_FROZEN;
                break;
            }
            strcpy(action, oaction);
            ptr = optr;
        }

        if (oaction) {
            free(oaction);
        }
        if (found) {
            console_printf("\033[0mOK");
        }
        return;
    }

    if (strcmp(action, "KILL") == 0 || strcmp(action, "SLEEP") == 0 ||
        strcmp(action, "WAKEUP") == 0 || strcmp(action, "FREEZE") == 0) {
        char act = *action;
        i = findproc(NULL, action, ptr);
        if (!i) {
            return;
        }

        switch (act) {
        case 'K':
            LOCDWORD(mod_debug, i, STATUS) =
                (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) | STATUS_KILLED;
            break;

        case 'W':
            LOCDWORD(mod_debug, i, STATUS) =
                (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) | STATUS_RUNNING;
            break;

        case 'S':
            LOCDWORD(mod_debug, i, STATUS) =
                (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) | STATUS_SLEEPING;
            break;

        case 'F':
            LOCDWORD(mod_debug, i, STATUS) =
                (LOCDWORD(mod_debug, i, STATUS) & STATUS_WAITING_MASK) | STATUS_FROZEN;
            break;
        }
        console_printf("\033[0mOK");
        return;
    }

    if (strcmp(action, "QUIT") == 0) {
        bgdrtm_exit(1);
        return;
    }

    /* Variables del ENGINE */

    for (var = 0; var < N_CONSOLE_VARS; var++) {
        if (strcmp(console_vars[var].name, action) == 0) {
            switch (console_vars[var].type) {
            case CON_DWORD:
                if (*ptr) {
                    while (*ptr == '=' || *ptr == ' ') {
                        ptr++;
                    }
                    eval_expression(ptr, 0);
                    if (result.type != T_ERROR) {
                        *(int *)console_vars[var].value = (int)result.value;
                    }
                }
                console_printf("\033[0m%s = %d", console_vars[var].name,
                               *(int *)console_vars[var].value);
                return;

            case CON_DWORD_HEX:
                if (*ptr) {
                    while (*ptr == '=' || *ptr == ' ') {
                        ptr++;
                    }
                    eval_expression(ptr, 0);
                    if (result.type != T_ERROR) {
                        *(int *)console_vars[var].value = (int)result.value;
                    }
                }
                console_printf("\033[0m%s = %08Xh\n", console_vars[var].name,
                               *(int *)console_vars[var].value);
                return;
            }
        }
    }

    /* Expresiones */

    eval_expression(command, 1);
}

/* ----------------------- */
/* Hotkey for exit (ALT+X) */
/* ----------------------- */

static int force_exit_cb(SDL_Keysym k) {
    exit_value = 0;
    must_exit  = 1;
    return 1;
}

/* ----------------------- */
/* Handle network commands */
/* ----------------------- */

static int handle_network_commands() {
    // Inform the debug server that
    // we can now accept commands
    if (send(console_sock, "DBGON", 5, 0) < 0) {
        debug_mode         = 0;
        force_debug        = 0;
        break_on_next_proc = 0;
        fprintf(stderr, "Debug mode cannot activate since "
                        "debugger is not connected\n");
        return -1;
    } else {
        int retval;
        char server_msg[2000];

        retval = recv(console_sock, server_msg, 2000, 0);
        while (retval > 0) {
            printf("server_msg: '%s'\n", server_msg);
            console_do(server_msg);
            // TODO: Handle all the rest processes
            if (strcmp(server_msg, "GO") == 0) {
                break;
            }
            retval = recv(console_sock, server_msg, 2000, 0);
        }

        if (retval == 0) {
            printf("Debug server disconnected\n");
        }
    }

    return 1;
}

/* --------------------------------------- */
/* Hotkeys for activate/deactivate console */
/* --------------------------------------- */

static int debug_mode_handler_cb(SDL_Keysym k) {
    int retval = -1;

    if (dcb.data.NSourceFiles) {
        if (console_sock > -1) {
            debug_mode  = 1;
            force_debug = 1;
            SetSocketBlockingEnabled(console_sock, 1);
            retval = handle_network_commands();
            SetSocketBlockingEnabled(console_sock, 0);
            debug_mode         = 0;
            force_debug        = 0;
            break_on_next_proc = 0;
        }

        return retval;

        // We should handle all these commands over the network
        //        if ( debug_mode ) {
        //            // Get command from network
        //            SetSocketBlockingEnabled(console_sock, 1);
        //            if(recv(console_sock, network_cmd, 2000, 0) > 0) {
        //                printf("Got command: '%s'\n", network_cmd);
        //            }
        //            SetSocketBlockingEnabled(console_sock, 0);
        //            if ( k.sym == SDLK_F1 ) {
        //                console_do( "HELP" );
        //                return 1;
        //            }

        //            if ( k.mod & ( KMOD_LSHIFT | KMOD_RSHIFT ) ) {
        //                if ( k.sym == SDLK_F2 ) {
        //                    console_instance_dump_all_brief();
        //                    return 1;
        //                }

        //                if ( console_list_current_instance && console_list_current == 1 ) {
        //                    if ( k.sym == SDLK_F3 ) {
        //                        int id = LOCDWORD( mod_debug, console_list_current_instance,
        //                        PROCESS_ID ) ;
        //                        console_printf( "\033[38;2;0;192;0m%s (%d) LOCALS\033[0m\n\n",
        //                                ( dcb.data.NSourceFiles &&
        //                                dcb.proc[console_list_current_instance->proc->type].data.ID
        //                                ) ? getid_name(
        //                                dcb.proc[console_list_current_instance->proc->type].data.ID
        //                                ) : (( console_list_current_instance->proc->type == 0 ) ?
        //                                "Main" : "proc" ),
        //                                id
        //                                      );
        //                        sprintf( cmd, "LOCALS %d", id ) ;
        //                        console_do( cmd );
        //                        return 1;
        //                    }

        //                    if ( k.sym == SDLK_F4 ) {
        //                        int id = LOCDWORD( mod_debug, console_list_current_instance,
        //                        PROCESS_ID ) ;
        //                        console_printf( "\033[38;2;0;192;0m%s (%d) PRIVATES\033[0m\n\n",
        //                                ( dcb.data.NSourceFiles &&
        //                                dcb.proc[console_list_current_instance->proc->type].data.ID
        //                                ) ? getid_name(
        //                                dcb.proc[console_list_current_instance->proc->type].data.ID
        //                                ) : (( console_list_current_instance->proc->type == 0 ) ?
        //                                "Main" : "proc" ),
        //                                id
        //                                      );
        //                        sprintf( cmd, "PRIVATES %d", id ) ;
        //                        console_do( cmd );
        //                        return 1;
        //                    }

        //                    if ( k.sym == SDLK_F5 ) {
        //                        int id = LOCDWORD( mod_debug, console_list_current_instance,
        //                        PROCESS_ID ) ;
        //                        console_printf( "\033[38;2;0;192;0m%s (%d) PUBLICS\033[0m\n\n",
        //                                ( dcb.data.NSourceFiles &&
        //                                dcb.proc[console_list_current_instance->proc->type].data.ID
        //                                ) ? getid_name(
        //                                dcb.proc[console_list_current_instance->proc->type].data.ID
        //                                ) : (( console_list_current_instance->proc->type == 0 ) ?
        //                                "Main" : "proc" ),
        //                                id
        //                                      );
        //                        sprintf( cmd, "PUBLICS %d", id ) ;
        //                        console_do( cmd );
        //                        return 1;
        //                    }
        //                }

        //                if ( k.sym == SDLK_F6 ) {
        //                    console_list_current ^= 1;
        //                    return 1;
        //                }
        //            }

        //            if ( k.sym == SDLK_F2 ) {
        //                console_instance_dump_all() ;
        //                return 1;
        //            }

        //            if ( !( k.mod & ( KMOD_LSHIFT | KMOD_RSHIFT ) ) ) {
        //                if ( k.sym == SDLK_F5 ) {
        //                    console_do( "GO" );
        //                    return 1;
        //                }

        //                if ( k.sym == SDLK_F8 ) {
        //                    console_do( "TRACE" );
        //                    return 1;
        //                }

        //                if ( k.sym == SDLK_F10 ) {
        //                    console_do( "NEXTFRAME" );
        //                    return 1;
        //                }

        //                if ( k.sym == SDLK_F11 ) {
        //                    console_do( "NEXTPROC" );
        //                    return 1;
        //                }
        //            }

        //            if ( !( k.mod & KMOD_LALT ) ) {
        //                console_getkey( k.sym, k.sym ) ;
        //            }
        //            return 1;
        //        }
    }

    return 0;
}

/* --------------------------------------------------------------------------- */

static int moddebug_trace(INSTANCE *my, int *params) {
    debug = params[0];
    return 0;
}

/* --------------------------------------------------------------------------- */

/** Returns true on success, or false if there was an error */
int SetSocketBlockingEnabled(int fd, int blocking) {
    if (fd < 0) {
        return -1;
    }

#ifdef WIN32
    unsigned long mode = blocking ? 0 : 1;
    return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? 0 : -1;
#else
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        return -1;
    }
    flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    return (fcntl(fd, F_SETFL, flags) == 0) ? 0 : -1;
#endif
}

/* --------------------------------------------------------------------------- */

void __bgdexport(mod_debug, process_exec_hook)(INSTANCE *r) {
    if (break_on_next_proc) {
        debug_next         = 1;
        break_on_next_proc = 0;
    }
}

/* --------------------------------------------------------------------------- */

void __bgdexport(mod_debug, module_initialize)() {
    if (dcb.data.NSourceFiles) {
        hotkey_add(KMOD_LALT, SDLK_x, force_exit_cb);
        hotkey_add(KMOD_LALT, SDLK_c, debug_mode_handler_cb);

        // Create socket
        console_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (console_sock == -1) {
            fprintf(stderr, "Could not create socket\n");
        }
        printf("Socket created\n");

        struct sockaddr_in server;

        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_family      = AF_INET;
        server.sin_port        = htons(8888);

        // Connect to remote server
        if (connect(console_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
            fprintf(stderr, "connect failed. Error\n");
            return;
        }

        printf("Connected\n");
        sleep(1);

        // Make the socket nonblocking so that we can read all the info
        // the server wants to send us
        SetSocketBlockingEnabled(console_sock, 0);

        int retval;
        char server_reply[2000];
        while ((retval = recv(console_sock, server_reply, 2000, 0)) > 0) {
            printf("%s\n", server_reply);
        }

        SetSocketBlockingEnabled(console_sock, 1);
    }
}

/* --------------------------------------------------------------------------- */

void __bgdexport(mod_debug, module_finalize)() {
    if (console_sock > -1) {
#ifdef WIN32
        closesocket(console_sock);
#else
        close(console_sock);
#endif
    }
}

/* --------------------------------------------------------------------------- */

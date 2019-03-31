/*
 *  Copyright (C) 2014-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
 *  Copyright (C) 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright (C) 2006-2012 Titonus
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

/* ---------------------------------------------------------- */

#include "pxtdl.h"
#include "xstrings.h"

#include <libsocket.h>
#include <stdint.h>

/* ---------------------------------------------------------- */
int mod_fsock_init(INSTANCE *my, intptr_t *params) {
    return libsocket_init(params[0]);
}

/* ---------------------------------------------------------- */

int mod_fsock_quit(INSTANCE *my, intptr_t *params) {
    return libsocket_quit();
}

/* ---------------------------------------------------------- */

int mod_fsock_geterror(INSTANCE *my, intptr_t *params) {
    return libsocket_geterror();
}

/* ---------------------------------------------------------- */

int mod_fsock_getfdsetsize(INSTANCE *my, intptr_t *params) {
    return libsocket_getfdsetsize();
}

/* ---------------------------------------------------------- */

int mod_fsock_tcpopen(INSTANCE *my, intptr_t *params) {
    return libsocket_tcpopen();
}

/* ---------------------------------------------------------- */

int mod_fsock_udpopen(INSTANCE *my, intptr_t *params) {
    return libsocket_udpopen();
}

/* ---------------------------------------------------------- */

int mod_fsock_setblock(INSTANCE *my, intptr_t *params) {
    return libsocket_setblock(params[0], params[1]);
}

/* ---------------------------------------------------------- */

int mod_fsock_close(INSTANCE *my, intptr_t *params) {
    return libsocket_close(params[0]);
}

/* ---------------------------------------------------------- */

int mod_fsock_bind(INSTANCE *my, intptr_t *params) {
    // Ensure that the given port number is in the range (1-65535)
    if (params[1] < 1 || params[1] > UINT16_MAX) {
        return -1;
    }

    return libsocket_bind(params[0], (uint16_t)params[1]);
}

/* ---------------------------------------------------------- */

int mod_fsock_listen(INSTANCE *my, intptr_t *params) {
    return libsocket_listen(params[0], params[1]);
}

/* ---------------------------------------------------------- */

int mod_fsock_accept_tcp(INSTANCE *my, intptr_t *params) {
    return libsocket_accept_tcp(params[0], (int *)params[1], (int *)params[2]);
}

/* ---------------------------------------------------------- */

int mod_fsock_connect_tcp(INSTANCE *my, intptr_t *params) {
    // Ensure that the given port number is in the range (1-65535)
    if (params[2] < 1 || params[2] > UINT16_MAX) {
        return -1;
    }

    return libsocket_connect_tcp(params[0], (char *)string_get(params[1]), (uint16_t)params[2]);
}

/* ---------------------------------------------------------- */

int mod_fsock_select_socketset(INSTANCE *my, intptr_t *params) {
    return libsocket_select_socketset(params[0], params[1], params[2], params[3]);
}

/* ---------------------------------------------------------- */

int mod_fsock_send_tcp(INSTANCE *my, intptr_t *params) {
    return libsocket_send_tcp(params[0], (void *)params[1], (size_t)params[2]);
}

/* ---------------------------------------------------------- */

int mod_fsock_send_udp(INSTANCE *my, intptr_t *params) {
    char *data = (char *)params[1];
    char *ip = (char *)string_get(params[3]);
    if (params[4] < 1 || params[4] > UINT16_MAX) {
        return -1;
    }

    return libsocket_send_udp(params[0], (void *)data, (size_t)params[2], ip, params[4]);
}

/* ---------------------------------------------------------- */

int mod_fsock_recv_tcp(INSTANCE *my, intptr_t *params) {
    return libsocket_recv_tcp(params[0], (void *)params[1], params[2]);
}

/* ---------------------------------------------------------- */

int mod_fsock_recv_udp(INSTANCE *my, intptr_t *params) {
    return libsocket_recv_udp(params[0], (void *)params[1], params[2], (int *)params[3],
                              (int *)params[4]);
}

/* ---------------------------------------------------------- */

void mod_fsock_fdzero(INSTANCE *my, intptr_t *params) {
    return libsocket_fdzero(params[0]);
}

/* ---------------------------------------------------------- */

int mod_fsock_fdset(INSTANCE *my, intptr_t *params) {
    return libsocket_fdset(params[0], params[1]);
}

/* ---------------------------------------------------------- */

int mod_fsock_fdclr(INSTANCE *my, intptr_t *params) {
    return libsocket_fdclr(params[0], params[1]);
}

/* ---------------------------------------------------------- */

int mod_fsock_fdisset(INSTANCE *my, intptr_t *params) {
    return libsocket_fdisset(params[0], params[1]);
}

/* ---------------------------------------------------------- */

int mod_fsock_check_socketset(INSTANCE *my, intptr_t *params) {
    return libsocket_check_socketset(params[0], params[1], params[2], params[3]);
}

/* ---------------------------------------------------------- */

int mod_fsock_get_iphost(INSTANCE *my, intptr_t *params) {
    int info_str_code;

    info_str_code = string_new(libsocket_get_iphost(params[0]));
    string_use(info_str_code);
    return info_str_code;
}

/* ---------------------------------------------------------- */

int mod_fsock_get_ipstr(INSTANCE *my, intptr_t *params) {
    int info_str_code;

    info_str_code = string_new(libsocket_get_ipstr(*(int *)params[0]));

    string_use(info_str_code);
    return info_str_code;
}

/* --------------------------------------------------------------------------- */

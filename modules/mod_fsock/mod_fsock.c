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

#include "bgddl.h"
#include "xstrings.h"

#include <libsocket.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* ---------------------------------------------------------- */
// Inicializamos librería WinSock (version 2) - Devuelve 0 si no hubo error
int mod_fsock_init(INSTANCE *my, int *params) {
    return libsocket_init(params[0]);
}

/* ---------------------------------------------------------- */
// Apaga la librería WinSock (devuelve 0 si fue correcto)

int mod_fsock_quit(INSTANCE *my, int *params) {
    return libsocket_quit();
}

/* ---------------------------------------------------------- */
// Devuelve código error (ver doc. API correspondiente) de la última llamada fsock

int mod_fsock_geterror(INSTANCE *my, int *params) {
    return libsocket_geterror();
}

/* ---------------------------------------------------------- */
// Devuelve la cantidad maxima de fds posibles de crear

int mod_fsock_getfdsetsize(INSTANCE *my, int *params) {
    return libsocket_getfdsetsize();
}

/* ---------------------------------------------------------- */
// Create and return a TCP socket - Returns -1 on error

int mod_fsock_tcpopen(INSTANCE *my, int *params) {
    return libsocket_tcpopen();
}

/* ---------------------------------------------------------- */
// Create and return a UDP socket - Returns -1 on error

int mod_fsock_udpopen(INSTANCE *my, int *params) {
    return libsocket_udpopen();
}

/* ---------------------------------------------------------- */
// Establece si un socket es bloqueante o no (llamar inmediatamente después de crear el socket)
// Las llamadas de conexión, aceptación, envío y recepción de un socket no bloqueante pueden
// retornar sin haber completado la operación, asegurarse con select

int mod_fsock_setblock(INSTANCE *my, int *params) {
    return libsocket_set(params[0], params[1]);
}

/* ---------------------------------------------------------- */
// Cierra un socket TCP/UDP (si fue correcto devuelve 0)

int mod_fsock_close(INSTANCE *my, int *params) {
    return libsocket_close(params[0]);
}

/* ---------------------------------------------------------- */
// Asociamos el socket (TCP o UDP) dado con el puerto especificado (si fue correcto devuelve 0)

int mod_fsock_bind(INSTANCE *my, int *params) {
    // Ensure that the given port number is in the range (1-65535)
    if(params[1] < 1 || params[1] > UINT16_MAX) {
        return -1;
    }

    return libsocket_bind(params[0], (uint16_t)params[1]);
}

/* ---------------------------------------------------------- */
// Fijamos el nº de peticiones que puede tener el socket anteriormente asociado (binded)

int mod_fsock_listen(INSTANCE *my, int *params) {
    return libsocket_listen(params[0], params[1]);
}

/* ---------------------------------------------------------- */
// Acepta una petición de conexión del socket dado y devuelve su socket a usar

int tcpsock_accept(INSTANCE *my, int *params) {
    int socket;
    struct timeval timeout;
    fd_set readfds;
    struct sockaddr_in addr;
    unsigned int addrlen;

    FD_ZERO(&readfds);
    FD_SET(params[0], &readfds);
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;

    if (select(FD_SETSIZE, &readfds, NULL, NULL, &timeout) > 0) {
        addrlen = sizeof(addr);
        socket = accept(params[0], (struct sockaddr *)&addr, &addrlen);
        if (socket != -1) {
            *(int *)params[1] = addr.sin_addr.s_addr; // ip
            *(int *)params[2] = ntohs(addr.sin_port); // puerto
        }
    } else {
        socket = -1;
    }

    return socket;
}

/* ---------------------------------------------------------- */
// Realiza una petición de conexión a la dirección IP/Host y puerto dado
// con el socket dado determinado y devuelve 0 si fue correcto

int tcpsock_connect(INSTANCE *my, int *params) {
    return libsocket_connect(params[0], (char *)string_get(params[1]));
}

/* ---------------------------------------------------------- */
// Realiza un select sobre el socket set indicado devolviendo
// el número de sockets que tienen actividad
// SÍ MODIFICA LOS SOCKETSETS PARA LUEGO COMPROBAR QUÉ SOCKETS TUVIERON ACTIVIDAD

int fsock_select(INSTANCE *my, int *params) {
    struct timeval timeout;
    int nlResultado     = -1;
    fd_set *fdTemporal1 = NULL, *fdTemporal2 = NULL, *fdTemporal3 = NULL;

    if ((params[0] >= 0) && (params[0] < g_num_socket_sets)) {
        fdTemporal1 = &socketsets[params[0]];
    }

    if ((params[1] >= 0) && (params[1] < g_num_socket_sets)) {
        fdTemporal2 = &socketsets[params[1]];
    }

    if ((params[2] >= 0) && (params[2] < g_num_socket_sets)) {
        fdTemporal3 = &socketsets[params[2]];
    }

    timeout.tv_sec  = params[3] / 1000;
    timeout.tv_usec = params[3] % 1000;

    nlResultado = select(FD_SETSIZE, fdTemporal1, fdTemporal2, fdTemporal3, &timeout);

    return (nlResultado);
}

/* ---------------------------------------------------------- */
// Envía un puntero de un tamaño determinado a través del socket TCP dado

int tcpsock_send(INSTANCE *my, int *params) {
    char *envio = (char *)params[1];
    return (send(params[0], (void *)envio, params[2], 0));
}

/* ---------------------------------------------------------- */
// Envía un puntero de un tamaño determinado a través del socket UDP dado

int udpsock_send(INSTANCE *my, int *params) {
    char *envio = (char *)params[1];
    char *ip    = (char *)string_get(params[3]);
    struct sockaddr_in info_conexion;
    info_conexion.sin_family      = AF_INET;
    info_conexion.sin_port        = htons(params[4]);
    info_conexion.sin_addr.s_addr = inet_addr(ip);

    return (sendto(params[0], (void *)envio, params[2], 0, (SOCKADDR *)&info_conexion,
                   sizeof(info_conexion)));
}

/* ---------------------------------------------------------- */
// Recibe un puntero de un tamaño determinado a través del socket TCP dado

int tcpsock_recv(INSTANCE *my, int *params) {
    return (recv(params[0], (void *)params[1], params[2], 0));
}

/* ---------------------------------------------------------- */
// Recibe un puntero de un tamaño determinado a través del socket UDP dado

int udpsock_recv(INSTANCE *my, int *params) {

    struct sockaddr_in info_conexion;
    int bytesRecibidos;
    unsigned int tamanoInfoConexion;

    bytesRecibidos = recvfrom(params[0], (void *)params[1], params[2], 0,
                              (SOCKADDR *)&info_conexion, &tamanoInfoConexion);

    if (params[0] != -1) {
        *(int *)params[3] = info_conexion.sin_addr.s_addr; // ip
        *(int *)params[4] = ntohs(info_conexion.sin_port); // puerto
    }

    return bytesRecibidos;
}

/* ---------------------------------------------------------- */
// Inicia o vacia el socket set indicado

void mod_fsock_fdzero(INSTANCE *my, int *params) {
    return libsocket_fdzero(params[0]);
}

/* ---------------------------------------------------------- */
// Añade un socket al socket set indicado

int mod_fsock_fdset(INSTANCE *my, int *params) {
    return libsocket_fdset(params[0], params[1]);
}

/* ---------------------------------------------------------- */
// Elimina un socket del socket set indicado

int mod_fsock_fdclr(INSTANCE *my, int *params) {
    return libsocket_fdclr(params[0], params[1]);
}

/* ---------------------------------------------------------- */
// Chequea si un socket tiene evento disponible

int mod_fsock_fdisset(INSTANCE *my, int *params) {
    return libsocket_fdisset(params[0], params[1]);
}

/* ---------------------------------------------------------- */
// Comprueba si hay actividad en el socket set indicado devolviendo
// el número de sockets que tienen actividad
// NO MODIFICA LOS SOCKETSETS PARA COMPROBAR LUEGO QUE SOCKETS TUVIERON ACTIVIDAD

int fsock_socketset_check(INSTANCE *my, int *params) {
    int check;
    struct timeval timeout;
    fd_set fdTemporal1, fdTemporal2, fdTemporal3;

    timeout.tv_sec  = params[3] / 1000;
    timeout.tv_usec = params[3] % 1000;

    if ((params[0] >= 0) && (params[0] < g_num_socket_sets)) {
        memcpy(&fdTemporal1, &socketsets[params[0]], sizeof(fdTemporal1));
    } else {
        FD_ZERO(&fdTemporal1);
    }

    if ((params[1] >= 0) && (params[1] < g_num_socket_sets)) {
        memcpy(&fdTemporal2, &socketsets[params[1]], sizeof(fdTemporal2));
    } else {
        FD_ZERO(&fdTemporal2);
    }

    if ((params[2] >= 0) && (params[2] < g_num_socket_sets)) {
        memcpy(&fdTemporal3, &socketsets[params[2]], sizeof(fdTemporal3));
    } else {
        FD_ZERO(&fdTemporal3);
    }

    check = select(FD_SETSIZE, &fdTemporal1, &fdTemporal2, &fdTemporal3, &timeout);

    return check;
}

/* ---------------------------------------------------------- */
// Returns a string with with the hostname or IP address of the
// machine running the code
// If params[0] == 0 the hostname is returned
// If params[0] != 0 (the documented value is 1) the host IP is
//                   returned

int mod_fsock_get_iphost(INSTANCE *my, int *params) {
    int info_str_code;
    char host[80];
    struct hostent *phe;
    struct in_addr addr;

    gethostname(host, sizeof(host));
    phe = gethostbyname(host);
    memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));

    if (!params[0]) {
        info_str_code = string_new(host);
    } else {
        info_str_code = string_new(inet_ntoa(addr));
    }

    string_use(info_str_code);
    return info_str_code;
}

/* ---------------------------------------------------------- */
// Return a string with the IP address given by the
// dword * ip parameter that some functions use

int mod_fsock_get_ipstr(INSTANCE *my, int *params) {
    int info_str_code;
    struct in_addr addr;

    addr.s_addr = *(int *)params[0];

    info_str_code = string_new(inet_ntoa(addr));

    string_use(info_str_code);
    return info_str_code;
}

/* --------------------------------------------------------------------------- */

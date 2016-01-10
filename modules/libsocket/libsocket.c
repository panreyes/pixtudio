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

/*
 * This librarry implements a very simple network library
 * by abstracting OS implementations so that they behave
 * simmilarly to how the Unix socket implementations do.
 * Both Unix-style sockets and Windows winsock are
 * supported.
 */

#include "bgddl.h"
#include "xstrings.h"

#ifdef WIN32
#include <winsock.h>
#else
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/ipc.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#endif
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libsocket.h"

/* ---------------------------------------------------------- */
// Initialize socket library - Returns 0 on success
int libsocket_init(int num_socket_sets) {
    int retval = 0;

#ifdef WIN32
    WSADATA wsaData;
    retval = (WSAStartup(MAKEWORD(2, 2), &wsaData));
#endif

    // Use given number of socketsets if valid, global value otherwise
    if ((num_socket_sets > 0)) {
        g_num_socket_sets = num_socket_sets;
    }

    socketsets = (fd_set *)malloc(sizeof(fd_set) * g_num_socket_sets);
    if (socketsets == NULL) {
        return -1;
    }
    memset(socketsets, 0x0, sizeof(fd_set) * g_num_socket_sets);

#ifndef WIN32
    fd_count = (int *)malloc(sizeof(int) * g_num_socket_sets);
    if (!fd_count) {
        free(socketsets);
        return -1;
    }
#endif

    return retval;
}

/* ---------------------------------------------------------- */
// Close sockets library - Returns 0 on success

int libsocket_quit() {
    if (socketsets != NULL) {
        free(socketsets);
        socketsets = NULL;
    }

#ifdef WIN32
    return (WSACleanup());
#else
    if (fd_count) {
        free(fd_count);
        fd_count = NULL;
    }
    return 0;
#endif
}

/* ---------------------------------------------------------- */
// Returns error code of the last call to the fsock API
// The Windows error values are detailed here:
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms740668%28v=vs.85%29.aspx
// The Linux/Unix error values are detailed here:
// TODO: Find a list of sockets errno values (it should match the windows counterpart,
//       but who knows...)

int libsocket_geterror() {
#ifdef WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

/* ---------------------------------------------------------- */
// Return the maximum number of FDs that can be created

int libsocket_getfdsetsize() {
    return FD_SETSIZE;
}

/* ---------------------------------------------------------- */
// Create and return a TCP socket - Returns -1 on error

int libsocket_tcpopen() {
    return (socket(AF_INET, SOCK_STREAM, 0));
}

/* ---------------------------------------------------------- */
// Create and return a UDP socket - Returns -1 on error

int libsocket_udpopen() {
    return (socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
}

/* ---------------------------------------------------------- */
// Set the socket as blocking or nonblocking (call immediately
// after creating it).
// The connection, accept, send and reception of data in a
// non-blocking socket can return without their associated
// operation being complete. You can ensure they are with select

int libsocket_setblock(int fd, u_long ulVal) {
#ifdef WIN32
    return (ioctlsocket(fd, FIONBIO, &ulVal));
#else
    return (fcntl(fd, O_NONBLOCK, ulVal));
#endif
}

/* ---------------------------------------------------------- */
// Close a TCP/UDP socket - Returns 0 on success

int libsocket_close(int fd) {
    shutdown(fd, 0);

#ifdef WIN32
    return (closesocket(fd));
#else
    return (close(fd));
#endif
}

/* ---------------------------------------------------------- */
// Bind the given TCP/UDP socket to the given port
// Returns 0 on success

int libsocket_bind(int socket, uint16_t port) {
    struct sockaddr_in connection_info;
    connection_info.sin_family      = AF_INET;
    connection_info.sin_port        = htons(port);
    connection_info.sin_addr.s_addr = INADDR_ANY;

    return (bind(socket, (SOCKADDR *)&connection_info, sizeof(connection_info)));
}

/* ---------------------------------------------------------- */
// Set the number of petitions that the previously
// binded socket can have

int libsocket_listen(int socket, int backlog) {
    return (listen(socket, backlog));
}

/* ---------------------------------------------------------- */
// Acepta una petición de conexión del socket dado y devuelve su socket a usar

int tcpsock_accept(INSTANCE *my, int *params) {
    int socket;
    struct timeval timeout;
    fd_set readfds;
    struct sockaddr_in addr;
#ifdef WIN32
    int addrlen;
#else
    unsigned int addrlen;
#endif

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

int libsocket_connect(int socket, char *ip) {
    struct sockaddr_in connection_info;
    connection_info.sin_family      = AF_INET;
    connection_info.sin_port        = htons(params[2]);
    connection_info.sin_addr.s_addr = inet_addr(ip);

    return (connect(socket, (SOCKADDR *)&connection_info, sizeof(connection_info)));
}

/* ---------------------------------------------------------- */
// Realiza un select sobre el socket set indicado devolviendo
// el número de sockets que tienen actividad
// SÍ MODIFICA LOS SOCKETSETS PARA LUEGO COMPROBAR QUE SOCKETS TUVIERON ACTIVIDAD

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
#ifdef WIN32
    int tamanoInfoConexion;
#else
    unsigned int tamanoInfoConexion;
#endif

    bytesRecibidos = recvfrom(params[0], (void *)params[1], params[2], 0,
                              (SOCKADDR *)&info_conexion, &tamanoInfoConexion);

    if (params[0] != -1) {
        *(int *)params[3] = info_conexion.sin_addr.s_addr; // ip
        *(int *)params[4] = ntohs(info_conexion.sin_port); // puerto
    }

    return bytesRecibidos;
}

/* ---------------------------------------------------------- */
// Initialize or empty given socket set

void libsocket_fdzero(int n) {
    FD_ZERO(&socketsets[n]);
#ifndef WIN32
    fd_count[n] = 0;
#endif
}

/* ---------------------------------------------------------- */
// Add a socket to the given socket set

int libsocket_fdset(int n, int fd) {
    FD_SET(fd, &socketsets[n]);
#ifdef WIN32
    return socketsets[n].fd_count;
#else
    return fd_count[n]++;
#endif
}

/* ---------------------------------------------------------- */
// Clear a socket from the given socket set

int libsocket_fdclr(int n, int fd) {
    FD_CLR(fd, &socketsets[n]);
#ifdef WIN32
    return socketsets[n].fd_count;
#else
    return fd_count[n]--;
#endif
}

/* ---------------------------------------------------------- */
// Check if a socket has an available event

int libsocket_fdisset(int n, int fd) {
    return (FD_ISSET(fd, &socketsets[n]));
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

/* --------------------------------------------------------------------------- */

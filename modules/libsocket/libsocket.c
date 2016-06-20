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

#include "pxtdl.h"
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
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "libsocket.h"

/* ---------------------------------------------------------- */

#define SOCKADDR struct sockaddr
#pragma pack()

/* ---------------------------------------------------------- */

fd_set *socketsets    = NULL;
int g_num_socket_sets = 32;
#ifndef WIN32
int *fd_count = NULL;
#endif

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
// Accept a connection request for the given socket and return
// its associated socket

int libsocket_accept_tcp(int insock, int *ip, int *port) {
    int outsock;
    struct timeval timeout;
    fd_set readfds;
    struct sockaddr_in addr;
#ifdef WIN32
    int addrlen;
#else
    unsigned int addrlen;
#endif

    FD_ZERO(&readfds);
    FD_SET(insock, &readfds);
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;

    if (select(FD_SETSIZE, &readfds, NULL, NULL, &timeout) > 0) {
        addrlen = sizeof(addr);
        outsock = accept(insock, (struct sockaddr *)&addr, &addrlen);
        if (outsock != -1) {
            *ip   = addr.sin_addr.s_addr;
            *port = ntohs(addr.sin_port);
        }
    } else {
        outsock = -1;
    }

    return outsock;
}

/* ---------------------------------------------------------- */
// Try to connect to the given IP/Host on the given port and
// socket.
// Returns 0 on success

int libsocket_connect_tcp(int socket, char *ip, uint16_t port) {
    struct sockaddr_in connection_info;
    connection_info.sin_family      = AF_INET;
    connection_info.sin_port        = htons(port);
    connection_info.sin_addr.s_addr = inet_addr(ip);

    return (connect(socket, (SOCKADDR *)&connection_info, sizeof(connection_info)));
}

/* ---------------------------------------------------------- */
// Call select on the given socket set and return the number
// of active sockets
// THIS FUNCTION MODIFIES THE SOCKETSETS TO CHECK WHICH ONES
// WERE ACTIVE

int libsocket_select_socketset(int id_readss, int id_writess, int id_errorss, int wait_time) {
    struct timeval timeout;
    int retval             = -1;
    fd_set *read_socketset = NULL, *write_socketset = NULL, *error_socketset = NULL;

    if ((id_readss >= 0) && (id_readss < g_num_socket_sets)) {
        read_socketset = &socketsets[id_readss];
    }

    if ((id_writess >= 0) && (id_writess < g_num_socket_sets)) {
        write_socketset = &socketsets[id_writess];
    }

    if ((id_errorss >= 0) && (id_errorss < g_num_socket_sets)) {
        error_socketset = &socketsets[id_errorss];
    }

    timeout.tv_sec  = wait_time / 1000;
    timeout.tv_usec = wait_time % 1000;

    retval = select(FD_SETSIZE, read_socketset, write_socketset, error_socketset, &timeout);

    return (retval);
}

/* ---------------------------------------------------------- */
// Send sized data from the given pointer over the given
// TCP socket

int libsocket_send_tcp(int socket, void *data, size_t len) {
    return (send(socket, data, len, 0));
}

/* ---------------------------------------------------------- */
// Envía un puntero de un tamaño determinado a través del socket UDP dado

int libsocket_send_udp(int socket, void *data, size_t len, char *ip, uint16_t port) {
    struct sockaddr_in connection_info;
    connection_info.sin_family      = AF_INET;
    connection_info.sin_port        = htons(port);
    connection_info.sin_addr.s_addr = inet_addr(ip);

    return (sendto(socket, data, len, 0, (SOCKADDR *)&connection_info, sizeof(connection_info)));
}

/* ---------------------------------------------------------- */
// Receive sized data from the given pointer over the given
// TCP socket

int libsocket_recv_tcp(int socket, void *dest, size_t len) {
    return (recv(socket, dest, len, 0));
}

/* ---------------------------------------------------------- */
// Receive sized data from the given pointer over the given
// UDP socket
// TODO: Test this routine when socket != -1

int libsocket_recv_udp(int socket, void *dest, size_t len, int *ip, int *port) {
    struct sockaddr_in connection_info;
    int received_bytes;
#ifdef WIN32
    int connection_info_size;
#else
    unsigned int connection_info_size = sizeof(connection_info);
#endif

    received_bytes =
        recvfrom(socket, dest, len, 0, (SOCKADDR *)&connection_info, &connection_info_size);

    if (socket != -1) {
        *ip   = connection_info.sin_addr.s_addr; // ip
        *port = ntohs(connection_info.sin_port); // puerto
    }

    return received_bytes;
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
// Call select on the given socket set and return the number
// of active sockets
// THIS FUNCTION DOES NOT MODIFY THE SOCKETSETS TO CHECK WHICH
// ONES WERE ACTIVE

int libsocket_check_socketset(int id_readss, int id_writess, int id_errorss, int wait_time) {
    int check;
    struct timeval timeout;
    fd_set read_socketset, write_socketset, error_socketset;

    if ((id_readss >= 0) && (id_readss < g_num_socket_sets)) {
        memcpy(&read_socketset, &socketsets[id_readss], sizeof(read_socketset));
    } else {
        FD_ZERO(&read_socketset);
    }

    if ((id_writess >= 0) && (id_writess < g_num_socket_sets)) {
        memcpy(&write_socketset, &socketsets[id_writess], sizeof(write_socketset));
    } else {
        FD_ZERO(&write_socketset);
    }

    if ((id_errorss >= 0) && (id_errorss < g_num_socket_sets)) {
        memcpy(&error_socketset, &socketsets[id_errorss], sizeof(error_socketset));
    } else {
        FD_ZERO(&error_socketset);
    }

    timeout.tv_sec  = wait_time / 1000;
    timeout.tv_usec = wait_time % 1000;

    check = select(FD_SETSIZE, &read_socketset, &write_socketset, &error_socketset, &timeout);

    return check;
}

/* ---------------------------------------------------------- */

char *libsocket_get_iphost(int flag) {
    char host[80];
    struct hostent *phe;
    struct in_addr addr;

    gethostname(host, sizeof(host));

    if (!flag) {
        return strdup(host);
    } else {
        phe = gethostbyname(host);
        memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
        return inet_ntoa(addr);
    }
}

/* ---------------------------------------------------------- */

char *libsocket_get_ipstr(uint32_t _s_addr) {
    struct in_addr addr;

    addr.s_addr = _s_addr;

    return inet_ntoa(addr);
}

/* --------------------------------------------------------------------------- */

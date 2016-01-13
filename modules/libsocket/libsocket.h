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

#ifndef __LIBSOCKET_H
#define __LIBSOCKET_H

#include <stdlib.h>
#include <stdint.h>
#ifdef WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#include <sys/select.h>
#endif

/* ---------------------------------------------------------- */

int libsocket_init(int num_socket_sets);
int libsocket_quit();
int libsocket_geterror();
int libsocket_getfdsetsize();
int libsocket_tcpopen();
int libsocket_udpopen();
int libsocket_setblock(int fd, u_long ulVal);
int libsocket_close(int fd);
int libsocket_bind(int fd, uint16_t port);
int libsocket_listen(int socket, int backlog);
int libsocket_accept_tcp(int insock, int *ip, int *port);
int libsocket_connect_tcp(int socket, char *ip, uint16_t port);
int libsocket_send_tcp(int socket, void *data, size_t len);
int libsocket_send_udp(int socket, void *data, size_t len, char *ip, uint16_t port);
int libsocket_recv_tcp(int socket, void *dest, size_t len);
int libsocket_recv_udp(int socket, void *dest, size_t len, int *ip, int *port);
void libsocket_fdzero(int n);
int libsocket_fdset(int n, int fd);
int libsocket_fdclr(int n, int fd);
int libsocket_fdisset(int n, int fd);
int libsocket_select_socketset(int id_readss, int id_writess, int id_errorss, int wait_time);
int libsocket_check_socketset(int id_readss, int id_writess, int id_errorss, int wait_time);
char *libsocket_get_iphost(int flag);
char *libsocket_get_ipstr(uint32_t s_addr);

#endif

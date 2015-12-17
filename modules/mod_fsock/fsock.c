/*
 * fsock library (aka tcpsock) by Titonus & SplinterGU
 */

/* ---------------------------------------------------------- */

#include "bgddl.h"
#include "xstrings.h"

#include <unistd.h>
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

#define SOCKADDR struct sockaddr

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ---------------------------------------------------------- */

#pragma pack()

/* ---------------------------------------------------------- */

fd_set* socketsets = NULL;
int gnNumSocketSets = 32;
#ifndef WIN32
int *fd_count =  NULL;
#endif

/* ---------------------------------------------------------- */
// Inicializamos librería WinSock (version 2) - Devuelve 0 si no hubo error

int fsock_init( INSTANCE * my, int * params ) {
    int nlRetorno = 0;

#ifdef WIN32
    WSADATA wsaData;
    nlRetorno = ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) );
#endif

    if (( params[0] > 0 ) ) {
        gnNumSocketSets = params[0];
    }
    socketsets = ( fd_set* ) malloc( sizeof( fd_set ) * gnNumSocketSets );
    if ( socketsets == NULL ) {
        return -1;
    }

#ifndef WIN32
    fd_count = ( int * ) malloc( sizeof( int ) * gnNumSocketSets );
    if ( !fd_count ) {
        free( socketsets );
        return -1;
    }
#endif

    memset( socketsets, 0x0, sizeof( fd_set )*gnNumSocketSets );

    return nlRetorno;
}

/* ---------------------------------------------------------- */
// Apaga la librería WinSock (devuelve 0 si fue correcto)

int fsock_quit( INSTANCE * my, int * params ) {
    if ( socketsets != NULL ) {
        free( socketsets );
        socketsets = NULL;
    }

#ifdef WIN32
    return ( WSACleanup() );
#else
    if ( fd_count ) {
        free( fd_count );
        fd_count = NULL;
    }
    return 0;
#endif
}

/* ---------------------------------------------------------- */
// Devuelve código error (ver doc. API correspondiente) de la última llamada fsock

int fsock_geterror( INSTANCE * my, int * params ) {
#ifdef WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

/* ---------------------------------------------------------- */
// Devuelve la cantidad maxima de fds posibles de crear

int fsock_getfdsetsize( INSTANCE * my, int * params ) {
    return FD_SETSIZE;
}

/* ---------------------------------------------------------- */
// Crea un socket TCP y lo devuelve (-1 es error)

int tcpsock_open( INSTANCE * my, int * params ) {
    return ( socket( AF_INET, SOCK_STREAM, 0 ) );
}

/* ---------------------------------------------------------- */
// Crea un socket UDP y lo devuelve (-1 es error)

int udpsock_open( INSTANCE * my, int * params ) {
    return ( socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ) );
}

/* ---------------------------------------------------------- */
// Establece si un socket es bloqueante o no (llamar inmediatamente después de crear el socket)
// Las llamadas de conexión, aceptación, envío y recepción de un socket no bloqueante pueden
// retornar sin haber completado la operación, asegurarse con select

int fsock_setblock( INSTANCE * my, int * params ) {
    u_long ulVal = params[1];

#ifdef WIN32
    return ( ioctlsocket( params[0], FIONBIO, &ulVal ) );
#else
    return ( fcntl( params[0], O_NONBLOCK, ulVal ) );
#endif
}

/* ---------------------------------------------------------- */
// Cierra un socket TCP/UDP (si fue correcto devuelve 0)

int fsock_close( INSTANCE * my, int * params ) {
    shutdown( params[0], 0 );

#ifdef WIN32
    return ( closesocket( params[0] ) );
#else
    return ( close( params[0] ) );
#endif
}

/* ---------------------------------------------------------- */
// Asociamos el socket (TCP o UDP) dado con el puerto especificado (si fue correcto devuelve 0)

int fsock_bind( INSTANCE * my, int * params ) {
    struct sockaddr_in info_conexion;
    info_conexion.sin_family = AF_INET;
    info_conexion.sin_port = htons( params[1] );
    info_conexion.sin_addr.s_addr = INADDR_ANY;

    return ( bind( params[0], ( SOCKADDR* )&info_conexion, sizeof( info_conexion ) ) );
}

/* ---------------------------------------------------------- */
// Fijamos el nº de peticiones que puede tener el socket anteriormente asociado (binded)

int tcpsock_listen( INSTANCE * my, int * params ) {
    return ( listen( params[0], params[1] ) );
}

/* ---------------------------------------------------------- */
// Acepta una petición de conexión del socket dado y devuelve su socket a usar

int tcpsock_accept( INSTANCE * my, int * params ) {
    int socket;
    struct timeval timeout;
    fd_set readfds;
    struct sockaddr_in addr;
    unsigned int addrlen;

    FD_ZERO( &readfds );
    FD_SET( params[0], &readfds );
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    if ( select( FD_SETSIZE, &readfds, NULL, NULL, &timeout ) > 0 ) {
        addrlen = sizeof( addr );
        socket = accept( params[0], ( struct sockaddr * ) & addr, &addrlen );
        if ( socket != -1 ) {
            *( int * )params[1] = addr.sin_addr.s_addr; //ip
            *( int * )params[2] = ntohs( addr.sin_port ); //puerto
        }
    } else {
        socket = -1;
    }

    return socket;
}

/* ---------------------------------------------------------- */
// Realiza una petición de conexión a la dirección IP/Host y puerto dado
// con el socket dado determinado y devuelve 0 si fue correcto

int tcpsock_connect( INSTANCE * my, int * params ) {
    char* ip = ( char* )string_get( params[1] );
    struct sockaddr_in info_conexion;
    info_conexion.sin_family = AF_INET;
    info_conexion.sin_port = htons( params[2] );
    info_conexion.sin_addr.s_addr = inet_addr( ip );

    return ( connect( params[0], ( SOCKADDR* )&info_conexion, sizeof( info_conexion ) ) );
}

/* ---------------------------------------------------------- */
// Realiza un select sobre el socket set indicado devolviendo
// el número de sockets que tienen actividad
// SÍ MODIFICA LOS SOCKETSETS PARA LUEGO COMPROBAR QUE SOCKETS TUVIERON ACTIVIDAD

int fsock_select( INSTANCE * my, int * params ) {
    struct timeval timeout;
    int nlResultado = -1;
    fd_set *fdTemporal1 = NULL, *fdTemporal2 = NULL, *fdTemporal3 = NULL;

    if (( params[0] >= 0 ) && ( params[0] < gnNumSocketSets ) ) {
        fdTemporal1 = &socketsets[params[0]];
    }

    if (( params[1] >= 0 ) && ( params[1] < gnNumSocketSets ) ) {
        fdTemporal2 = &socketsets[params[1]];
    }

    if (( params[2] >= 0 ) && ( params[2] < gnNumSocketSets ) ) {
        fdTemporal3 = &socketsets[params[2]];
    }

    timeout.tv_sec = params[3] / 1000;
    timeout.tv_usec = params[3] % 1000;

    nlResultado = select( FD_SETSIZE, fdTemporal1, fdTemporal2, fdTemporal3, &timeout );

    return ( nlResultado );
}

/* ---------------------------------------------------------- */
// Envía un puntero de un tamaño determinado a través del socket TCP dado

int tcpsock_send( INSTANCE * my, int * params ) {
    char *envio = ( char* )params[1];
    return ( send( params[0], ( void* )envio, params[2], 0 ) );
}

/* ---------------------------------------------------------- */
// Envía un puntero de un tamaño determinado a través del socket UDP dado

int udpsock_send( INSTANCE * my, int * params ) {
    char *envio = ( char* )params[1];
    char* ip = ( char* )string_get( params[3] );
    struct sockaddr_in info_conexion;
    info_conexion.sin_family = AF_INET;
    info_conexion.sin_port = htons( params[4] );
    info_conexion.sin_addr.s_addr = inet_addr( ip );

    return ( sendto( params[0], ( void* )envio, params[2], 0, ( SOCKADDR* )&info_conexion, sizeof( info_conexion ) ) );
}

/* ---------------------------------------------------------- */
// Recibe un puntero de un tamaño determinado a través del socket TCP dado

int tcpsock_recv( INSTANCE * my, int * params ) {
    return ( recv( params[0], ( void* )params[1], params[2], 0 ) );
}

/* ---------------------------------------------------------- */
// Recibe un puntero de un tamaño determinado a través del socket UDP dado

int udpsock_recv( INSTANCE * my, int * params ) {

    struct sockaddr_in info_conexion;
    int bytesRecibidos;
    unsigned int tamanoInfoConexion;

    bytesRecibidos = recvfrom( params[0], ( void* )params[1], params[2], 0, ( SOCKADDR* ) & info_conexion, &tamanoInfoConexion );

    if ( params[0] != -1 )
    {
        *( int * ) params[3] = info_conexion.sin_addr.s_addr; //ip
        *( int * ) params[4] = ntohs( info_conexion.sin_port ); //puerto
    }

    return bytesRecibidos;
}

/* ---------------------------------------------------------- */
// Inicia o vacia el socket set indicado

void fsock_fdzero( INSTANCE * my, int * params ) {
    FD_ZERO( &socketsets[params[0]] );
#ifndef WIN32
    fd_count[params[0]] = 0;
#endif
}

/* ---------------------------------------------------------- */
// Añade un socket al socket set indicado

int fsock_fdset( INSTANCE * my, int * params ) {
    FD_SET( params[1], &socketsets[params[0]] );
#ifdef WIN32
    return socketsets[params[0]].fd_count;
#else
    return fd_count[params[0]]++;
#endif
}

/* ---------------------------------------------------------- */
// Elimina un socket del socket set indicado

int fsock_fdclr( INSTANCE * my, int * params ) {
    FD_CLR( params[1], &socketsets[params[0]] );
#ifdef WIN32
    return socketsets[params[0]].fd_count;
#else
    return fd_count[params[0]]--;
#endif
}

/* ---------------------------------------------------------- */
// Chequea si un socket tiene evento disponible

int fsock_fdisset( INSTANCE * my, int * params ) {
    return ( FD_ISSET( params[1], &socketsets[params[0]] ) );
}

/* ---------------------------------------------------------- */
// Comprueba si hay actividad en el socket set indicado devolviendo
// el número de sockets que tienen actividad
// NO MODIFICA LOS SOCKETSETS PARA COMPROBAR LUEGO QUE SOCKETS TUVIERON ACTIVIDAD

int fsock_socketset_check( INSTANCE * my, int * params ) {
    int check;
    struct timeval timeout;
    fd_set fdTemporal1, fdTemporal2, fdTemporal3;

    timeout.tv_sec = params[3] / 1000;
    timeout.tv_usec = params[3] % 1000;

    if (( params[0] >= 0 ) && ( params[0] < gnNumSocketSets ) ) {
        memcpy( &fdTemporal1, &socketsets[params[0]], sizeof( fdTemporal1 ) );
    } else {
        FD_ZERO( &fdTemporal1 );
    }

    if (( params[1] >= 0 ) && ( params[1] < gnNumSocketSets ) ) {
        memcpy( &fdTemporal2, &socketsets[params[1]], sizeof( fdTemporal2 ) );
    } else {
        FD_ZERO( &fdTemporal2 );
    }

    if (( params[2] >= 0 ) && ( params[2] < gnNumSocketSets ) ) {
        memcpy( &fdTemporal3, &socketsets[params[2]], sizeof( fdTemporal3 ) );
    } else {
        FD_ZERO( &fdTemporal3 );
    }

    check = select( FD_SETSIZE, &fdTemporal1, &fdTemporal2, &fdTemporal3, &timeout );

    return check;
}

/* ---------------------------------------------------------- */
// Devuelve el nombre del host del PC o la dirección IP de la máquina
// que lo ejecuta según se especifique (0 o 1 respectivamente)

int fsock_get_iphost( INSTANCE * my, int * params ) {
    int texto;
    char host[80];
    struct hostent *phe;
    struct in_addr addr;

    gethostname( host, sizeof( host ) );
    phe = gethostbyname( host );
    memcpy( &addr, phe->h_addr_list[0], sizeof( struct in_addr ) );

    if ( !params[0] ) {
        texto = string_new( host );
    } else {
        texto = string_new( inet_ntoa( addr ) ) ;
    }

    string_use( texto ) ;
    return texto;
}

/* ---------------------------------------------------------- */
// Devuelve la cadena con la dirección IP dada por el parámetro
// dword * ip que algunas funciones usan

int fsock_get_ipstr( INSTANCE * my, int * params ) {
    int texto;
    struct in_addr addr;

    addr.s_addr = *( int * ) params[0];

    texto = string_new( inet_ntoa( addr ) );

    string_use( texto );
    return texto;

}

/* --------------------------------------------------------------------------- */

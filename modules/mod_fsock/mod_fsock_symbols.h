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

#ifndef __FSOCK_SYMBOLS_H
#define __FSOCK_SYMBOLS_H

#include <bgddl.h>

#ifndef __PXTB__
extern int mod_fsock_init( INSTANCE * my, int * params );
extern int mod_fsock_geterror( INSTANCE * my, int * params );
extern int mod_fsock_getfdsetsize( INSTANCE * my, int * params );
extern int mod_fsock_tcpopen( INSTANCE * my, int * params );
extern int mod_fsock_udpopen( INSTANCE * my, int * params );
extern int mod_fsock_setblock( INSTANCE * my, int * params );
extern int mod_fsock_close( INSTANCE * my, int * params );
extern int mod_fsock_bind( INSTANCE * my, int * params );
extern int mod_fsock_listen( INSTANCE * my, int * params );
extern int mod_fsock_accept_tcp( INSTANCE * my, int * params );
extern int mod_fsock_connect_tcp( INSTANCE * my, int * params );
extern int mod_fsock_select_socketset( INSTANCE * my, int * params );
extern int mod_fsock_send_tcp( INSTANCE * my, int * params );
extern int mod_fsock_send_udp( INSTANCE * my, int * params );
extern int mod_fsock_recv_tcp( INSTANCE * my, int * params );
extern int mod_fsock_recv_udp( INSTANCE * my, int * params );
extern int mod_fsock_check_socketset( INSTANCE * my, int * params );
extern void mod_fsock_fdzero( INSTANCE * my, int * params );
extern int mod_fsock_fdset( INSTANCE * my, int * params );
extern int mod_fsock_fdclr( INSTANCE * my, int * params );
extern int mod_fsock_get_iphost( INSTANCE * my, int * params );
extern int mod_fsock_get_ipstr( INSTANCE * my, int * params );
extern int mod_fsock_quit( INSTANCE * my, int * params );
extern int mod_fsock_fdisset( INSTANCE * my, int * params );
#endif

DLSYSFUNCS  __bgdexport( mod_fsock, exported_functions )[] = {
    FUNC( "FSOCK_INIT"           , "I"    , TYPE_DWORD , mod_fsock_init             ),
    FUNC( "FSOCK_GETERROR"       , ""     , TYPE_DWORD , mod_fsock_geterror         ),
    FUNC( "FSOCK_GETFDSETSIZE"   , ""     , TYPE_DWORD , mod_fsock_getfdsetsize     ),
    FUNC( "TCPSOCK_OPEN"         , ""     , TYPE_DWORD , mod_fsock_tcpopen          ),
    FUNC( "UDPSOCK_OPEN"         , ""     , TYPE_DWORD , mod_fsock_udpopen          ),
    FUNC( "FSOCK_SETBLOCK"       , "II"   , TYPE_DWORD , mod_fsock_setblock         ),
    FUNC( "FSOCK_CLOSE"          , "I"    , TYPE_DWORD , mod_fsock_close            ),
    FUNC( "FSOCK_BIND"           , "II"   , TYPE_DWORD , mod_fsock_bind             ),
    FUNC( "TCPSOCK_LISTEN"       , "II"   , TYPE_DWORD , mod_fsock_listen           ),
    FUNC( "TCPSOCK_ACCEPT"       , "IPP"  , TYPE_DWORD , mod_fsock_accept_tcp       ),
    FUNC( "TCPSOCK_CONNECT"      , "ISI"  , TYPE_DWORD , mod_fsock_connect_tcp      ),
    FUNC( "FSOCK_SELECT"         , "IIII" , TYPE_DWORD , mod_fsock_select_socketset ),
    FUNC( "TCPSOCK_SEND"         , "IPI"  , TYPE_DWORD , mod_fsock_send_tcp         ),
    FUNC( "UDPSOCK_SEND"         , "IPISI", TYPE_DWORD , mod_fsock_send_udp         ),
    FUNC( "TCPSOCK_RECV"         , "IPI"  , TYPE_DWORD , mod_fsock_recv_tcp         ),
    FUNC( "UDPSOCK_RECV"         , "IPIPP", TYPE_DWORD , mod_fsock_recv_udp         ),
    FUNC( "FSOCK_SOCKETSET_CHECK", "IIII" , TYPE_DWORD , mod_fsock_check_socketset  ),
    FUNC( "FSOCK_SOCKETSET_FREE" , "I"    , TYPE_DWORD , mod_fsock_fdzero           ),
    FUNC( "FSOCK_SOCKETSET_ADD"  , "II"   , TYPE_DWORD , mod_fsock_fdset            ),
    FUNC( "FSOCK_SOCKETSET_DEL"  , "II"   , TYPE_DWORD , mod_fsock_fdclr            ),
    FUNC( "FSOCK_GET_IPHOST"     , "I"    , TYPE_STRING, mod_fsock_get_iphost       ),
    FUNC( "FSOCK_GET_IPSTR"      , "P"    , TYPE_STRING, mod_fsock_get_ipstr        ),
    FUNC( "FSOCK_QUIT"           , ""     , TYPE_DWORD , mod_fsock_quit             ),
    FUNC( "FSOCK_FDZERO"         , "I"    , TYPE_DWORD , mod_fsock_fdzero           ),
    FUNC( "FSOCK_FDSET"          , "II"   , TYPE_DWORD , mod_fsock_fdset            ),
    FUNC( "FSOCK_FDCLR"          , "II"   , TYPE_DWORD , mod_fsock_fdclr            ),
    FUNC( "FSOCK_FDISSET"        , "II"   , TYPE_DWORD , mod_fsock_fdisset          ),
    FUNC( 0, 0, 0, 0 )
};

#endif

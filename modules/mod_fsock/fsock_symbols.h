/*
 * fsock library (aka tcpsock) by Titonus & SplinterGU
 */

/* ---------------------------------------------------------- */

#ifndef __FSOCK_SYMBOLS_H
#define __FSOCK_SYMBOLS_H

#include <bgddl.h>

#ifndef __PXTB__
extern int fsock_init( INSTANCE * my, int * params );
extern int fsock_geterror( INSTANCE * my, int * params );
extern int fsock_getfdsetsize( INSTANCE * my, int * params );
extern int tcpsock_open( INSTANCE * my, int * params );
extern int udpsock_open( INSTANCE * my, int * params );
extern int fsock_setblock( INSTANCE * my, int * params );
extern int fsock_close( INSTANCE * my, int * params );
extern int fsock_bind( INSTANCE * my, int * params );
extern int tcpsock_listen( INSTANCE * my, int * params );
extern int tcpsock_accept( INSTANCE * my, int * params );
extern int tcpsock_connect( INSTANCE * my, int * params );
extern int fsock_select( INSTANCE * my, int * params );
extern int tcpsock_send( INSTANCE * my, int * params );
extern int udpsock_send( INSTANCE * my, int * params );
extern int tcpsock_recv( INSTANCE * my, int * params );
extern int udpsock_recv( INSTANCE * my, int * params );
extern int fsock_socketset_check( INSTANCE * my, int * params );
extern void fsock_fdzero( INSTANCE * my, int * params );
extern int fsock_fdset( INSTANCE * my, int * params );
extern int fsock_fdclr( INSTANCE * my, int * params );
extern int fsock_get_iphost( INSTANCE * my, int * params );
extern int fsock_get_ipstr( INSTANCE * my, int * params );
extern int fsock_quit( INSTANCE * my, int * params );
extern int fsock_fdisset( INSTANCE * my, int * params );
#endif

DLSYSFUNCS  __bgdexport( fsock, exported_functions )[] = {
    FUNC( "FSOCK_INIT"           , "I"    , TYPE_DWORD , fsock_init            ),
    FUNC( "FSOCK_GETERROR"       , ""     , TYPE_DWORD , fsock_geterror        ),
    FUNC( "FSOCK_GETFDSETSIZE"   , ""     , TYPE_DWORD , fsock_getfdsetsize    ),
    FUNC( "TCPSOCK_OPEN"         , ""     , TYPE_DWORD , tcpsock_open          ),
    FUNC( "UDPSOCK_OPEN"         , ""     , TYPE_DWORD , udpsock_open          ),
    FUNC( "FSOCK_SETBLOCK"       , "II"   , TYPE_DWORD , fsock_setblock        ),
    FUNC( "FSOCK_CLOSE"          , "I"    , TYPE_DWORD , fsock_close           ),
    FUNC( "FSOCK_BIND"           , "II"   , TYPE_DWORD , fsock_bind            ),
    FUNC( "TCPSOCK_LISTEN"       , "II"   , TYPE_DWORD , tcpsock_listen        ),
    FUNC( "TCPSOCK_ACCEPT"       , "IPP"  , TYPE_DWORD , tcpsock_accept        ),
    FUNC( "TCPSOCK_CONNECT"      , "ISI"  , TYPE_DWORD , tcpsock_connect       ),
    FUNC( "FSOCK_SELECT"         , "IIII" , TYPE_DWORD , fsock_select          ),
    FUNC( "TCPSOCK_SEND"         , "IPI"  , TYPE_DWORD , tcpsock_send          ),
    FUNC( "UDPSOCK_SEND"         , "IPISI", TYPE_DWORD , udpsock_send          ),
    FUNC( "TCPSOCK_RECV"         , "IPI"  , TYPE_DWORD , tcpsock_recv          ),
    FUNC( "UDPSOCK_RECV"         , "IPIPP", TYPE_DWORD , udpsock_recv          ),
    FUNC( "FSOCK_SOCKETSET_CHECK", "IIII" , TYPE_DWORD , fsock_socketset_check ),
    FUNC( "FSOCK_SOCKETSET_FREE" , "I"    , TYPE_DWORD , fsock_fdzero          ),
    FUNC( "FSOCK_SOCKETSET_ADD"  , "II"   , TYPE_DWORD , fsock_fdset           ),
    FUNC( "FSOCK_SOCKETSET_DEL"  , "II"   , TYPE_DWORD , fsock_fdclr           ),
    FUNC( "FSOCK_GET_IPHOST"     , "I"    , TYPE_STRING, fsock_get_iphost      ),
    FUNC( "FSOCK_GET_IPSTR"      , "P"    , TYPE_STRING, fsock_get_ipstr       ),
    FUNC( "FSOCK_QUIT"           , ""     , TYPE_DWORD , fsock_quit            ),
    FUNC( "FSOCK_FDZERO"         , "I"    , TYPE_DWORD , fsock_fdzero          ),
    FUNC( "FSOCK_FDSET"          , "II"   , TYPE_DWORD , fsock_fdset           ),
    FUNC( "FSOCK_FDCLR"          , "II"   , TYPE_DWORD , fsock_fdclr           ),
    FUNC( "FSOCK_FDISSET"        , "II"   , TYPE_DWORD , fsock_fdisset         ),

    { 0, 0, 0, 0 }
};

#endif

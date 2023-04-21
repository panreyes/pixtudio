#ifndef __MOD_TMX_SYMBOLS
#define __MOD_TMX_SYMBOLS

/* ----------------------------------------------------------------- */

#include "pxtdl.h"

/* ----------------------------------------------------------------- */

#ifndef __PXTB__
int mod_tmx_load_map(INSTANCE * my, int * params);
int mod_tmx_get_map_width(INSTANCE * my, int * params);
int mod_tmx_get_map_height(INSTANCE * my, int * params);
int mod_tmx_unload_map(INSTANCE * my, int * params);
#endif

/* ----------------------------------------------------------------- */

DLCONSTANT  __pxtexport( mod_tmx, constants_def)[] =
{
    { NULL                      , 0             , 0                     }
} ;

/* Functions declaration                                             */

DLSYSFUNCS  __pxtexport(mod_tmx, exported_functions)[] =
{
    FUNC( "TMX_LOAD"               , "S"    , TYPE_INT , mod_tmx_load_map                   ),
    FUNC( "TMX_UNLOAD"             , "I"    , TYPE_INT , mod_tmx_unload_map                 ),
    FUNC( "TMX_GET_MAP_WIDTH"      , "I"    , TYPE_DWORD , mod_tmx_get_map_width            ),
    FUNC( "TMX_GET_MAP_HEIGHT"     , "I"    , TYPE_DWORD , mod_tmx_get_map_height           ),
    FUNC( 0                 , 0         , 0                , 0                                 )
};

/* ----------------------------------------------------------------- */

#endif

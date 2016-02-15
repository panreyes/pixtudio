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

#ifndef __MODMAP_SYMBOLS_H
#define __MODMAP_SYMBOLS_H

#include <pxtdl.h>

#ifndef __PXTB__
extern int modmap_map_block_copy( INSTANCE * my, int * params );
extern int modmap_map_put( INSTANCE * my, int * params );
extern int modmap_map_xput( INSTANCE * my, int * params );
extern int modmap_map_xputnp( INSTANCE * my, int * params );
extern int modmap_new_map( INSTANCE * my, int * params );
extern int modmap_new_map_extend( INSTANCE * my, int * params );
extern int modmap_new_map_extend( INSTANCE * my, int * params );
extern int modmap_map_clear( INSTANCE * my, int * params );
extern int modmap_map_clone( INSTANCE * my, int * params );
extern int modmap_map_name( INSTANCE * my, int * params );
extern int modmap_map_set_name( INSTANCE * my, int * params );
extern int modmap_map_exists( INSTANCE * my, int * params );
extern int modmap_map_xputnp( INSTANCE * my, int * params );
extern int modmap_unload_map( INSTANCE * my, int * params );
extern int modmap_unload_map( INSTANCE * my, int * params );
extern int modmap_load_map( INSTANCE * my, int * params );
extern int modmap_bgload_map( INSTANCE * my, int * params );
extern int modmap_save_map( INSTANCE * my, int * params );
extern int modmap_map_buffer( INSTANCE * my, int * params );
extern int modmap_fpg_add( INSTANCE * my, int * params );
extern int modmap_fpg_new( INSTANCE * my, int * params );
extern int modmap_fpg_exists( INSTANCE * my, int * params );
extern int modmap_load_fpg( INSTANCE * my, int * params );
extern int modmap_bgload_fpg( INSTANCE * my, int * params );
extern int modmap_save_fpg( INSTANCE * my, int * params );
extern int modmap_unload_fpg( INSTANCE * my, int * params );
extern int modmap_unload_fpg( INSTANCE * my, int * params );
extern int modmap_rgb_depth( INSTANCE * my, int * params );
extern int modmap_rgba_depth( INSTANCE * my, int * params );
extern int modmap_get_rgb_depth( INSTANCE * my, int * params );
extern int modmap_get_rgba_depth( INSTANCE * my, int * params );
extern int modmap_rgb( INSTANCE * my, int * params );
extern int modmap_rgba( INSTANCE * my, int * params );
extern int modmap_rgb_depth( INSTANCE * my, int * params );
extern int modmap_rgba_depth( INSTANCE * my, int * params );
extern int modmap_rgba( INSTANCE * my, int * params );
extern int modmap_rgba_depth( INSTANCE * my, int * params );
extern int modmap_get_rgb( INSTANCE * my, int * params );
extern int modmap_get_rgba( INSTANCE * my, int * params );
extern int modmap_get_rgb_depth( INSTANCE * my, int * params );
extern int modmap_get_rgba_depth( INSTANCE * my, int * params );
extern int modmap_get_rgba( INSTANCE * my, int * params );
extern int modmap_get_rgba_depth( INSTANCE * my, int * params );
extern int modmap_fade( INSTANCE * my, int * params );
extern int modmap_fade_in( INSTANCE * my, int * params );
extern int modmap_fade_out( INSTANCE * my, int * params );
extern int modmap_fade_in( INSTANCE * my, int * params );
extern int modmap_fade_out( INSTANCE * my, int * params );
extern int modmap_graphic_set( INSTANCE * my, int * params );
extern int modmap_graphic_info( INSTANCE * my, int * params );
extern int modmap_graphic_info( INSTANCE * my, int * params );
extern int modmap_graphic_set( INSTANCE * my, int * params );
extern int modmap_graphic_info( INSTANCE * my, int * params );
extern int modmap_colormod_set( INSTANCE * my, int * params );
extern int modmap_get_point( INSTANCE * my, int * params );
extern int modmap_set_point( INSTANCE * my, int * params );
extern int modmap_set_center( INSTANCE * my, int * params );
extern int modmap_load_fnt( INSTANCE * my, int * params );
extern int modmap_bgload_fnt( INSTANCE * my, int * params );
extern int modmap_unload_fnt( INSTANCE * my, int * params );
extern int modmap_save_fnt( INSTANCE * my, int * params );
extern int modmap_fnt_new( INSTANCE * my, int * params );
extern int modmap_fnt_new_charset( INSTANCE * my, int * params );
extern int modmap_fnt_new_from_bitmap( INSTANCE * my, int * params );
extern int modmap_fnt_new_charset( INSTANCE * my, int * params );
extern int modmap_fnt_new_from_bitmap( INSTANCE * my, int * params );
extern int modmap_load_ttf(INSTANCE *my, int *params);
extern int modmap_load_bdf( INSTANCE * my, int * params );
extern int modmap_bgload_bdf( INSTANCE * my, int * params );
extern int modmap_get_glyph( INSTANCE * my, int * params );
extern int modmap_set_glyph( INSTANCE * my, int * params );
extern int modmap_set_ttf_size( INSTANCE * my, int * params );
extern int modmap_load_png( INSTANCE * my, int * params );
extern int modmap_bgload_png( INSTANCE * my, int * params );
extern int modmap_load_pcx( INSTANCE * my, int * params );
extern int modmap_bgload_pcx( INSTANCE * my, int * params );
extern int modmap_save_png( INSTANCE * my, int * params );

extern void __pxtexport( mod_map, module_initialize )();
extern void __pxtexport( mod_map, module_finalize )();
#endif

#define G_WIDTH         0
#define G_HEIGHT        1
#define G_CENTER_X      2
#define G_X_CENTER      2
#define G_CENTER_Y      3
#define G_Y_CENTER      3
#define G_PITCH         4
#define G_DEPTH         5
#define B_CLEAR         0x00000001
#define CHARSET_ISO8859 0
#define CHARSET_CP850   1
#define NFB_FIXEDWIDTH  1

DLCONSTANT __pxtexport( mod_map, constants_def )[] = {
    { "G_WIDTH"          , TYPE_INT, G_WIDTH             },
    { "G_HEIGHT"         , TYPE_INT, G_HEIGHT            },
    { "G_CENTER_X"       , TYPE_INT, G_CENTER_X          },
    { "G_X_CENTER"       , TYPE_INT, G_X_CENTER          },
    { "G_CENTER_Y"       , TYPE_INT, G_CENTER_Y          },
    { "G_Y_CENTER"       , TYPE_INT, G_Y_CENTER          },
    { "G_PITCH"          , TYPE_INT, G_PITCH             },
    { "G_DEPTH"          , TYPE_INT, G_DEPTH             },

    { "B_CLEAR"          , TYPE_INT, B_CLEAR             },

    { "CHARSET_ISO8859"  , TYPE_INT, CHARSET_ISO8859     },
    { "CHARSET_CP850"    , TYPE_INT, CHARSET_CP850       },

    { "NFB_VARIABLEWIDTH", TYPE_INT, 0                  },
    { "NFB_FIXEDWIDTH"   , TYPE_INT, NFB_FIXEDWIDTH      },

    { NULL               , 0       , 0                   }
} ;

DLSYSFUNCS  __pxtexport( mod_map, exported_functions )[] = {
    /* Bitmaps */
    FUNC( "MAP_BLOCK_COPY"      , "IIIIIIIIII"  , TYPE_INT      , modmap_map_block_copy     ),
    FUNC( "MAP_PUT"             , "IIIII"       , TYPE_INT      , modmap_map_put            ),
    FUNC( "MAP_XPUT"            , "IIIIIIII"    , TYPE_INT      , modmap_map_xput           ),
    FUNC( "MAP_NEW"             , "III"         , TYPE_INT      , modmap_new_map            ),
    FUNC( "MAP_NEW"             , "IIII"        , TYPE_INT      , modmap_new_map_extend     ),
    FUNC( "MAP_CLEAR"           , "III"         , TYPE_INT      , modmap_map_clear          ),
    FUNC( "MAP_CLONE"           , "II"          , TYPE_INT      , modmap_map_clone          ),
    FUNC( "MAP_NAME"            , "II"          , TYPE_STRING   , modmap_map_name           ),
    FUNC( "MAP_SET_NAME"        , "IIS"         , TYPE_INT      , modmap_map_set_name       ),
    FUNC( "MAP_EXISTS"          , "II"          , TYPE_INT      , modmap_map_exists         ),
    FUNC( "MAP_XPUTNP"          , "IIIIIIIIII"  , TYPE_INT      , modmap_map_xputnp         ),
    FUNC( "MAP_DEL"             , "II"          , TYPE_INT      , modmap_unload_map         ),
    FUNC( "MAP_UNLOAD"          , "II"          , TYPE_INT      , modmap_unload_map         ),
    FUNC( "MAP_LOAD"            , "S"           , TYPE_INT      , modmap_load_map           ),
    FUNC( "MAP_LOAD"            , "SP"          , TYPE_INT      , modmap_bgload_map         ),
    FUNC( "MAP_SAVE"            , "IIS"         , TYPE_INT      , modmap_save_map           ),
    FUNC( "MAP_BUFFER"          , "II"          , TYPE_POINTER  , modmap_map_buffer         ),

    /* FPGs */
    FUNC( "FPG_ADD"             , "IIII"        , TYPE_INT      , modmap_fpg_add            ),
    FUNC( "FPG_NEW"             , ""            , TYPE_INT      , modmap_fpg_new            ),
    FUNC( "FPG_EXISTS"          , "I"           , TYPE_INT      , modmap_fpg_exists         ),
    FUNC( "FPG_LOAD"            , "S"           , TYPE_INT      , modmap_load_fpg           ),
    FUNC( "FPG_LOAD"            , "SP"          , TYPE_INT      , modmap_bgload_fpg         ),
    FUNC( "FPG_SAVE"            , "IS"          , TYPE_INT      , modmap_save_fpg           ),
    FUNC( "FPG_DEL"             , "I"           , TYPE_INT      , modmap_unload_fpg         ),
    FUNC( "FPG_UNLOAD"          , "I"           , TYPE_INT      , modmap_unload_fpg         ),

    FUNC( "RGB"                 , "BBBI"        , TYPE_INT      , modmap_rgb_depth          ),
    FUNC( "RGBA"                , "BBBBI"       , TYPE_INT      , modmap_rgba_depth         ),
    FUNC( "RGB_GET"             , "IPPPI"       , TYPE_INT      , modmap_get_rgb_depth      ),
    FUNC( "RGBA_GET"            , "IPPPPI"      , TYPE_INT      , modmap_get_rgba_depth     ),

    FUNC( "RGB"                 , "BBB"         , TYPE_INT      , modmap_rgb                ),
    FUNC( "RGBA"                , "BBBB"        , TYPE_INT      , modmap_rgba               ),
    FUNC( "RGB_GET"             , "IPPP"        , TYPE_INT      , modmap_get_rgb            ),
    FUNC( "RGBA_GET"            , "IPPPP"       , TYPE_INT      , modmap_get_rgba           ),

    FUNC( "FADE"                , "IIII"        , TYPE_INT      , modmap_fade               ),
    FUNC( "FADE_IN"             , ""            , TYPE_INT      , modmap_fade_in            ),
    FUNC( "FADE_OUT"            , ""            , TYPE_INT      , modmap_fade_out           ),

    /* Graphic information */
    FUNC( "MAP_INFO_SET"        , "IIII"        , TYPE_INT      , modmap_graphic_set        ),
    FUNC( "MAP_INFO_GET"        , "III"         , TYPE_INT      , modmap_graphic_info       ),
    FUNC( "MAP_INFO"            , "III"         , TYPE_INT      , modmap_graphic_info       ),
    FUNC( "GRAPHIC_SET"         , "IIII"        , TYPE_INT      , modmap_graphic_set        ),
    FUNC( "GRAPHIC_INFO"        , "III"         , TYPE_INT      , modmap_graphic_info       ),

    /* Color modulation */
    FUNC( "MAP_COLORMOD_SET"    , "IIIII"       , TYPE_INT      , modmap_colormod_set       ),

    /* Control points */
    FUNC( "POINT_GET"           , "IIIPP"       , TYPE_INT      , modmap_get_point          ),
    FUNC( "POINT_SET"           , "IIIII"       , TYPE_INT      , modmap_set_point          ),

    FUNC( "CENTER_SET"          , "IIII"        , TYPE_INT      , modmap_set_center         ),

    /* Fonts */
    FUNC( "FNT_LOAD"            , "S"           , TYPE_INT      , modmap_load_fnt           ),
    FUNC( "FNT_LOAD"            , "SP"          , TYPE_INT      , modmap_bgload_fnt         ),
    FUNC( "FNT_UNLOAD"          , "I"           , TYPE_INT      , modmap_unload_fnt         ),
    FUNC( "FNT_SAVE"            , "IS"          , TYPE_INT      , modmap_save_fnt           ),
    FUNC( "FNT_NEW"             , "I"           , TYPE_INT      , modmap_fnt_new            ),
    FUNC( "FNT_NEW"             , "II"          , TYPE_INT      , modmap_fnt_new_charset    ),
    FUNC( "FNT_NEW"             , "IIIIIIII"    , TYPE_INT      , modmap_fnt_new_from_bitmap),

    FUNC( "TTF_LOAD"            , "S"           , TYPE_INT      , modmap_load_ttf           ),
    FUNC( "TTF_SET_SIZE"        , "II"          , TYPE_INT      , modmap_set_ttf_size       ),

    FUNC( "BDF_LOAD"            , "S"           , TYPE_INT      , modmap_load_bdf           ),
    FUNC( "BDF_LOAD"            , "SP"          , TYPE_INT      , modmap_bgload_bdf         ),

    FUNC( "GLYPH_GET"           , "II"          , TYPE_INT      , modmap_get_glyph          ),
    FUNC( "GLYPH_SET"           , "IIII"        , TYPE_INT      , modmap_set_glyph          ),

    /* Image loading */
    FUNC( "PNG_LOAD"            , "S"           , TYPE_INT      , modmap_load_png           ),
    FUNC( "PNG_LOAD"            , "SP"          , TYPE_INT      , modmap_bgload_png         ),
    FUNC( "PCX_LOAD"            , "S"           , TYPE_INT      , modmap_load_pcx           ),
    FUNC( "PCX_LOAD"            , "SP"          , TYPE_INT      , modmap_bgload_pcx         ),

    /* Image saving */
    FUNC( "PNG_SAVE"            , "IIS"         , TYPE_INT      , modmap_save_png           ),

    FUNC( 0                     , 0             , 0             , 0 )
};

/* --------------------------------------------------------------------------- */

char * __pxtexport( mod_map, module_dependencies )[] = {
    "libgrbase",
    "libvideo",
    "libblit",
    "libfont",
    NULL
};

#endif

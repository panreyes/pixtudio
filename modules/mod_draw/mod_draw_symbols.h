/*
 *  Copyright Â© 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright Â© 2002-2006 Fenix Team (Fenix)
 *  Copyright Â© 1999-2002 JosÃ© Luis CebriÃ¡n PagÃ¼e (Fenix)
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

#ifndef __MODDRAW_SYMBOLS_H
#define __MODDRAW_SYMBOLS_H

#include <bgddl.h>

#ifndef __PXTB__
extern int moddraw_drawing_map( INSTANCE * my, int * params );
extern int moddraw_drawing_color( INSTANCE * my, int * params );
extern int moddraw_line( INSTANCE * my, int * params );
extern int moddraw_rect( INSTANCE * my, int * params );
extern int moddraw_box( INSTANCE * my, int * params );
extern int moddraw_circle( INSTANCE * my, int * params );
extern int moddraw_fcircle( INSTANCE * my, int * params );
extern int moddraw_bezier( INSTANCE * my, int * params );
extern int moddraw_drawing_at( INSTANCE * my, int * params );
extern int moddraw_delete_drawing( INSTANCE * my, int * params );
extern int moddraw_move_drawing( INSTANCE * my, int * params );
extern int moddraw_drawing_alpha( INSTANCE * my, int * params );
extern int moddraw_drawing_stipple( INSTANCE * my, int * params );
extern int moddraw_put_pixel( INSTANCE * my, int * params );
extern int moddraw_get_pixel( INSTANCE * my, int * params );
extern int moddraw_map_get_pixel( INSTANCE * my, int * params );
extern int moddraw_map_put_pixel( INSTANCE * my, int * params );
#endif
DLSYSFUNCS __bgdexport( mod_draw, functions_exports )[] = {
    FUNC( "DRAWING_MAP"     , "II"          , TYPE_INT  , moddraw_drawing_map       ),
    FUNC( "DRAWING_COLOR"   , "I"           , TYPE_INT  , moddraw_drawing_color     ),
    FUNC( "DRAW_LINE"       , "IIII"        , TYPE_INT  , moddraw_line              ),
    FUNC( "DRAW_RECT"       , "IIII"        , TYPE_INT  , moddraw_rect              ),
    FUNC( "DRAW_BOX"        , "IIII"        , TYPE_INT  , moddraw_box               ),
    FUNC( "DRAW_CIRCLE"     , "III"         , TYPE_INT  , moddraw_circle            ),
    FUNC( "DRAW_FCIRCLE"    , "III"         , TYPE_INT  , moddraw_fcircle           ),
    FUNC( "DRAW_CURVE"      , "IIIIIIIII"   , TYPE_INT  , moddraw_bezier            ),
    FUNC( "DRAWING_Z"       , "I"           , TYPE_INT  , moddraw_drawing_at        ),
    FUNC( "DELETE_DRAW"     , "I"           , TYPE_INT  , moddraw_delete_drawing    ),
    FUNC( "MOVE_DRAW"       , "III"         , TYPE_INT  , moddraw_move_drawing      ),
    FUNC( "DRAWING_ALPHA"   , "I"           , TYPE_INT  , moddraw_drawing_alpha     ),
    FUNC( "DRAWING_STIPPLE" , "I"           , TYPE_INT  , moddraw_drawing_stipple   ),
    FUNC( "PUT_PIXEL"       , "III"         , TYPE_INT  , moddraw_put_pixel         ),
    FUNC( "GET_PIXEL"       , "II"          , TYPE_INT  , moddraw_get_pixel         ),
    FUNC( "MAP_GET_PIXEL"   , "IIII"        , TYPE_INT  , moddraw_map_get_pixel     ),
    FUNC( "MAP_PUT_PIXEL"   , "IIIII"       , TYPE_INT  , moddraw_map_put_pixel     ),
    FUNC( NULL              , NULL          , 0         , NULL                      )
};

char * __bgdexport( mod_draw, modules_dependency )[] = {
    "libgrbase",
    "librender",
    "libdraw",
    NULL
};

#endif

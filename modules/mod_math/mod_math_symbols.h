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

#ifndef __MODMATH_H
#define __MODMATH_H

#include <bgddl.h>

#ifndef __PXTB__
extern int math_abs( INSTANCE * my, int * params );
extern int math_pow( INSTANCE * my, int * params );
extern int math_sqrt( INSTANCE * my, int * params );
extern int math_cos( INSTANCE * my, int * params );
extern int math_sin( INSTANCE * my, int * params );
extern int math_tan( INSTANCE * my, int * params );
extern int math_acos( INSTANCE * my, int * params );
extern int math_asin( INSTANCE * my, int * params );
extern int math_atan( INSTANCE * my, int * params );
extern int math_atan2( INSTANCE * my, int * params );
extern int math_atan2( INSTANCE * my, int * params );
extern int math_isinf( INSTANCE * my, int * params );
extern int math_isnan( INSTANCE * my, int * params );
extern int math_finite( INSTANCE * my, int * params );
extern int math_fget_angle( INSTANCE * my, int * params );
extern int math_fget_dist( INSTANCE * my, int * params );
extern int math_near_angle( INSTANCE * my, int * params );
extern int math_get_distx( INSTANCE * my, int * params );
extern int math_get_disty( INSTANCE * my, int * params );
#endif

DLCONSTANT __bgdexport( mod_math, constants_def )[] = {
    { "PI"  , TYPE_INT  , 180000    },
    { NULL  , 0         , 0         }
} ;

DLSYSFUNCS __bgdexport( mod_math, functions_exports )[] = {
    FUNC( "ABS"         , "F"       , TYPE_FLOAT    , math_abs          ),
    FUNC( "POW"         , "FF"      , TYPE_FLOAT    , math_pow          ),
    FUNC( "SQRT"        , "F"       , TYPE_FLOAT    , math_sqrt         ),

    FUNC( "COS"         , "F"       , TYPE_FLOAT    , math_cos          ),
    FUNC( "SIN"         , "F"       , TYPE_FLOAT    , math_sin          ),
    FUNC( "TAN"         , "F"       , TYPE_FLOAT    , math_tan          ),
    FUNC( "ACOS"        , "F"       , TYPE_FLOAT    , math_acos         ),
    FUNC( "ASIN"        , "F"       , TYPE_FLOAT    , math_asin         ),
    FUNC( "ATAN"        , "F"       , TYPE_FLOAT    , math_atan         ),
    FUNC( "ATAN2"       , "FF"      , TYPE_FLOAT    , math_atan2        ),

    FUNC( "ISINF"       , "F"       , TYPE_INT      , math_isinf        ),
    FUNC( "ISNAN"       , "F"       , TYPE_INT      , math_isnan        ),
    FUNC( "FINITE"      , "F"       , TYPE_INT      , math_finite       ),

    FUNC( "FGET_ANGLE"  , "IIII"    , TYPE_INT      , math_fget_angle   ),
    FUNC( "FGET_DIST"   , "IIII"    , TYPE_INT      , math_fget_dist    ),
    FUNC( "NEAR_ANGLE"  , "III"     , TYPE_INT      , math_near_angle   ),
    FUNC( "GET_DISTX"   , "II"      , TYPE_INT      , math_get_distx    ),
    FUNC( "GET_DISTY"   , "II"      , TYPE_INT      , math_get_disty    ),

    FUNC( 0             , 0         , 0             , 0                 )
};

#endif

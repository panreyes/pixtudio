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

#ifndef __MODSTRING_H
#define __MODSTRING_H

#include <bgddl.h>

#ifndef __PXTB__
extern int modstring_strlen( INSTANCE * my, int * params );
extern int modstring_strlen( INSTANCE * my, int * params );
extern int modstring_strupper( INSTANCE * my, int * params );
extern int modstring_strlower( INSTANCE * my, int * params );
extern int modstring_strcasecmp( INSTANCE * my, int * params );
extern int modstring_substr( INSTANCE * my, int * params );
extern int modstring_substr2( INSTANCE * my, int * params );
extern int modstring_substr2( INSTANCE * my, int * params );
extern int modstring_strfind( INSTANCE * my, int * params );
extern int modstring_strfindSSI( INSTANCE * my, int * params );
extern int modstring_strfindSSI( INSTANCE * my, int * params );
extern int modstring_lpad( INSTANCE * my, int * params );
extern int modstring_rpad( INSTANCE * my, int * params );
extern int modstring_itos( INSTANCE * my, int * params );
extern int modstring_ftos( INSTANCE * my, int * params );
extern int modstring_stoi( INSTANCE * my, int * params );
extern int modstring_stof( INSTANCE * my, int * params );
extern int modstring_asc( INSTANCE * my, int * params );
extern int modstring_chr( INSTANCE * my, int * params );
extern int modstring_trim( INSTANCE * my, int * params );
extern int modstring_strrev( INSTANCE * my, int * params );
extern int modstring_formatI( INSTANCE * my, int * params );
extern int modstring_formatF( INSTANCE * my, int * params );
extern int modstring_formatFI( INSTANCE * my, int * params );
extern int modstring_formatFI( INSTANCE * my, int * params );
#endif

DLSYSFUNCS  __bgdexport( mod_string, functions_exports )[] = {
    FUNC( "STRLEN"     , "S"   , TYPE_INT   , modstring_strlen     ),
    FUNC( "LEN"        , "S"   , TYPE_INT   , modstring_strlen     ),
    FUNC( "UCASE"      , "S"   , TYPE_STRING, modstring_strupper   ),
    FUNC( "LCASE"      , "S"   , TYPE_STRING, modstring_strlower   ),
    FUNC( "STRCASECMP" , "SS"  , TYPE_INT   , modstring_strcasecmp ),
    FUNC( "SUBSTR"     , "SII" , TYPE_STRING, modstring_substr     ),
    FUNC( "SUBSTR"     , "SI"  , TYPE_STRING, modstring_substr2    ),
    FUNC( "FIND"       , "SS"  , TYPE_INT   , modstring_strfind    ),
    FUNC( "FIND"       , "SSI" , TYPE_INT   , modstring_strfindSSI ),
    FUNC( "LPAD"       , "SI"  , TYPE_STRING, modstring_lpad       ),
    FUNC( "RPAD"       , "SI"  , TYPE_STRING, modstring_rpad       ),
    FUNC( "ITOA"       , "I"   , TYPE_STRING, modstring_itos       ),
    FUNC( "FTOA"       , "F"   , TYPE_STRING, modstring_ftos       ),
    FUNC( "ATOI"       , "S"   , TYPE_INT   , modstring_stoi       ),
    FUNC( "ATOF"       , "S"   , TYPE_FLOAT , modstring_stof       ),
    FUNC( "ASC"        , "S"   , TYPE_BYTE  , modstring_asc        ),
    FUNC( "CHR"        , "I"   , TYPE_STRING, modstring_chr        ),
    FUNC( "TRIM"       , "S"   , TYPE_STRING, modstring_trim       ),
    FUNC( "STRREV"     , "S"   , TYPE_STRING, modstring_strrev     ),
    FUNC( "FORMAT"     , "I"   , TYPE_STRING, modstring_formatI    ),
    FUNC( "FORMAT"     , "F"   , TYPE_STRING, modstring_formatF    ),
    FUNC( "FORMAT"     , "FI"  , TYPE_STRING, modstring_formatFI   ),
    FUNC( 0            , 0     , 0          , 0                    )
};

#endif

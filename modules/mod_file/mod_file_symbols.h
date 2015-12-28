/*
 *  Copyright (C) 2014-2015 Joseba García Etxebarria <joseba.gar@gmail.com>
 *  Copyright (C) 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright (C) 2002-2006 Fenix Team (Fenix)
 *  Copyright (C) 1999-2002 José Luis Cebrián Pagüe (Fenix)
 *
 *  This file is part of PixTudio
 *
 *  Bennu is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Bennu is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __MODFILE_H
#define __MODFILE_H

#include <bgddl.h>

#ifndef __PXTB__
extern int modfile_save( INSTANCE * my, int * params );
extern int modfile_load( INSTANCE * my, int * params );
extern int modfile_fopen( INSTANCE * my, int * params );
extern int modfile_fclose( INSTANCE * my, int * params );
extern int modfile_fread( INSTANCE * my, int * params );
extern int modfile_freadC( INSTANCE * my, int * params );
extern int modfile_fwrite( INSTANCE * my, int * params );
extern int modfile_fwriteC( INSTANCE * my, int * params );
extern int modfile_fseek( INSTANCE * my, int * params );
extern int modfile_frewind( INSTANCE * my, int * params );
extern int modfile_ftell( INSTANCE * my, int * params );
extern int modfile_fflush( INSTANCE * my, int * params );
extern int modfile_filelength( INSTANCE * my, int * params );
extern int modfile_fputs( INSTANCE * my, int * params );
extern int modfile_fgets( INSTANCE * my, int * params );
extern int modfile_feof( INSTANCE * my, int * params );
extern int modfile_file( INSTANCE * my, int * params );
extern int modfile_exists( INSTANCE * my, int * params );
extern int modfile_remove( INSTANCE * my, int * params );
extern int modfile_move( INSTANCE * my, int * params );
extern int modfile_dirname( INSTANCE * my, int * params );
extern int modfile_basename( INSTANCE * my, int * params );
#endif

DLCONSTANT  __bgdexport( mod_file, constants_def)[] = {
    { "O_READ"      , TYPE_INT, 0  },
    { "O_READWRITE" , TYPE_INT, 1  },
    { "O_RDWR"      , TYPE_INT, 1  },
    { "O_WRITE"     , TYPE_INT, 2  },
    { "O_ZREAD"     , TYPE_INT, 3  },
    { "O_ZWRITE"    , TYPE_INT, 4  },

    { "SEEK_SET"    , TYPE_INT, 0  },
    { "SEEK_CUR"    , TYPE_INT, 1  },
    { "SEEK_END"    , TYPE_INT, 2  },

    { NULL          , 0       , 0  }
} ;

DLSYSFUNCS  __bgdexport( mod_file, exported_functions)[] = {
    FUNC( "SAVE"        , "SV++" , TYPE_INT         , modfile_save        ),
    FUNC( "LOAD"        , "SV++" , TYPE_INT         , modfile_load        ),
    FUNC( "FOPEN"       , "SI"   , TYPE_INT         , modfile_fopen       ),
    FUNC( "FCLOSE"      , "I"    , TYPE_INT         , modfile_fclose      ),
    FUNC( "FREAD"       , "IV++" , TYPE_INT         , modfile_fread       ),
    FUNC( "FREAD"       , "PII"  , TYPE_INT         , modfile_freadC      ),
    FUNC( "FWRITE"      , "IV++" , TYPE_INT         , modfile_fwrite      ),
    FUNC( "FWRITE"      , "PII"  , TYPE_INT         , modfile_fwriteC     ),
    FUNC( "FSEEK"       , "III"  , TYPE_INT         , modfile_fseek       ),
    FUNC( "FREWIND"     , "I"    , TYPE_UNDEFINED   , modfile_frewind     ),
    FUNC( "FTELL"       , "I"    , TYPE_INT         , modfile_ftell       ),
    FUNC( "FFLUSH"      , "I"    , TYPE_INT         , modfile_fflush      ),
    FUNC( "FLUSH"       , "I"    , TYPE_INT         , modfile_fflush      ),
    FUNC( "FLENGTH"     , "I"    , TYPE_INT         , modfile_filelength  ),
    FUNC( "FPUTS"       , "IS"   , TYPE_INT         , modfile_fputs       ),
    FUNC( "FGETS"       , "I"    , TYPE_STRING      , modfile_fgets       ),
    FUNC( "FEOF"        , "I"    , TYPE_INT         , modfile_feof        ),
    FUNC( "FILE"        , "S"    , TYPE_STRING      , modfile_file        ),
    FUNC( "FEXISTS"     , "S"    , TYPE_INT         , modfile_exists      ),
    FUNC( "FILE_EXISTS" , "S"    , TYPE_INT         , modfile_exists      ),
    FUNC( "FREMOVE"     , "S"    , TYPE_INT         , modfile_remove      ),
    FUNC( "FMOVE"       , "SS"   , TYPE_INT         , modfile_move        ),

    FUNC( "DIRNAME"     , "S"    , TYPE_STRING      , modfile_dirname     ),
    FUNC( "BASENAME"    , "S"    , TYPE_STRING      , modfile_basename    ),

    FUNC( 0             , 0      , 0                , 0                   )
};

#endif

/*
 *  Copyright (C) 2014-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
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

#pragma once

#include <pxtdl.h>

#ifndef __PXTB__
extern int modtime_get_timer( INSTANCE * my, intptr_t * params );
extern int modtime_time( INSTANCE * my, intptr_t * params );
extern int modtime_ftime( INSTANCE * my, intptr_t * params );

extern void __pxtexport( mod_time, module_initialize )();
extern void __pxtexport( mod_time, module_finalize )();
#endif

DLSYSFUNCS __pxtexport( mod_time, exported_functions )[] = {
    FUNC( "GET_TIMER"   , ""    , TYPE_INT      , modtime_get_timer ),
    FUNC( "TIME"        , ""    , TYPE_INT      , modtime_time      ),
    FUNC( "FTIME"       , "SI"  , TYPE_STRING   , modtime_ftime     ),

    FUNC( 0             , 0     , 0             , 0                 )
};

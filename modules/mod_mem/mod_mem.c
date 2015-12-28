/*
 *  Copyright (C) 2014-2015 Joseba García Etxebarria <joseba.gar@gmail.com>
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

#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* WIN32 INCLUDES */
#ifdef WIN32
#include <windows.h>
#include <winbase.h>
#include <windef.h>
#endif

/* LINUX INCLUDES */
#ifdef __linux__
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <ctype.h>
#define KERNELC_V_1 2
#define KERNELC_V_2 3
#define KERNELC_V_3 16
#endif

/* OS X/iOS INCLUDES */
#ifdef __APPLE__
#include <sys/sysctl.h>
#endif

/* BSD INCLUDES */
#ifdef TARGET_BSD
#include <unistd.h>
#include <sys/utsname.h>
#include <ctype.h>
#endif

#include "bgddl.h"

#ifndef __MONOLITHIC__
#include "mod_mem_symbols.h"
#endif

/*
 * Dynamic memory
 */

/* Linux utility function */

#ifdef __linux__
static int kernel_version_type( void )
{
    struct utsname sysinf;
    int kernel_v[3];
    int i, t, fv = 0;

    if ( uname( &sysinf ) == -1 )
        return -1;

    bzero(( int* )kernel_v, sizeof( int )*3 );

    for ( i = 0, t = 0; i <= 2; i++ )
    {
        if ( sysinf.release[t] )
        {
            kernel_v[i] = atoi( &sysinf.release[t] );
            while ( sysinf.release[++t] && sysinf.release[t] != '.' )
                ;
            t++;
        }
    }

    if ( !fv && kernel_v[0] > KERNELC_V_1 ) fv = 1;
    if ( !fv && kernel_v[0] < KERNELC_V_1 ) fv = 2;
    if ( !fv && kernel_v[1] > KERNELC_V_2 ) fv = 1;
    if ( !fv && kernel_v[1] < KERNELC_V_2 ) fv = 2;
    if ( !fv && kernel_v[2] > KERNELC_V_3 ) fv = 1;
    if ( !fv && kernel_v[2] < KERNELC_V_3 ) fv = 2;

    return fv;
}
#endif

/* MEMORY_FREE()
 *  Returns the number of free bytes (physycal memory only)
 *  This value is intended only for informational purposes
 *  and may or may not be an approximation.
 */

int modmem_memory_free( INSTANCE * my, int * params )
{
#ifdef WIN32
    MEMORYSTATUS mem ;
    GlobalMemoryStatus( &mem ) ;
    return mem.dwAvailPhys ;

#elif defined(__linux__)
    /* Linux and other Unix (?) */
    struct sysinfo meminf;
    int fv;

    if ( sysinfo( &meminf ) == -1 ) return -1;

    if ( !( fv = kernel_version_type() ) ) return -1;

    if ( fv == 1 )
        return meminf.freeram * meminf.mem_unit;
    else
        return meminf.freeram;

    return -1;

#else
    return 0; //TODO

#endif
}

/* MEMORY_TOTAL();
 *  Return total number of bytes of physical memory
 */

int modmem_memory_total( INSTANCE * my, int * params )
{
#ifdef WIN32
    MEMORYSTATUS mem ;
    GlobalMemoryStatus( &mem ) ;
    return mem.dwTotalPhys ;

#elif defined(__linux__)
    /* Linux and other Unix (?) */
    struct sysinfo meminf;
    int fv;

    if ( sysinfo( &meminf ) == -1 ) return -1;

    if ( !( fv = kernel_version_type() ) ) return -1;

    if ( fv == 1 )
        return meminf.totalram * meminf.mem_unit;
    else
        return meminf.totalram;

    return -1;

#elif defined(__APPLE__)
    uint64_t total = 0;

    size_t size = sizeof(total);
    if( !sysctlbyname("hw.memsize", &total, &size, NULL, 0) ) {
        if(total > INT_MAX) {
            // We overflowed here
            fprintf(stderr, "Warning: MEMORY_TOTAL returning %dB of memory, real total is %llu\n", INT_MAX, total);
            return INT_MAX;
        } else {
            return (int)total;
        }
    }

    return -1;
#else
    return 0; //TODO

#endif
}

int modmem_memcmp( INSTANCE * my, int * params )
{
    return ( memcmp(( void * )params[0], ( void * )params[1], params[2] ) ) ;
}

int modmem_memmove( INSTANCE * my, int * params )
{
    memmove(( void * )params[0], ( void * )params[1], params[2] ) ;
    return 1 ;
}

int modmem_memcopy( INSTANCE * my, int * params )
{
    memcpy(( void * )params[0], ( void * )params[1], params[2] ) ;
    return 1 ;
}

int modmem_memset( INSTANCE * my, int * params )
{
    memset(( void * )params[0], params[1], params[2] ) ;
    return 1 ;
}

int modmem_memsetw( INSTANCE * my, int * params )
{
    uint16_t * ptr = ( uint16_t * )params[0] ;
    const uint16_t b = params[1] ;
    int n ;

    for ( n = params[2] ; n ; n-- ) *ptr++ = b ;
    return 1 ;
}

int modmem_memseti( INSTANCE * my, int * params )
{
    uint32_t * ptr = ( uint32_t * )params[0] ;
    const uint32_t b = params[1] ;
    int n ;

    for ( n = params[2] ; n ; n-- ) *ptr++ = b ;
    return 1 ;
}

int modmem_calloc( INSTANCE * my, int * params )
{
    return (( int ) calloc( params[0], params[1] ) ) ;
}

int modmem_alloc( INSTANCE * my, int * params )
{
    return (( int ) malloc( params[0] ) ) ;
}

int modmem_realloc( INSTANCE * my, int * params )
{
    return (( int )realloc(( void * )params[0], params[1] ) ) ;
}

int modmem_free( INSTANCE * my, int * params )
{
    free(( void * )params[0] ) ;
    return 1 ;
}

/* ---------------------------------------------------------------------- */

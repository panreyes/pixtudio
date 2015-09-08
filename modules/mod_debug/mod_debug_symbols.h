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

#ifndef __MODDEBUG_SYMBOLS_H
#define __MODDEBUG_SYMBOLS_H

#include <bgddl.h>

#ifdef __PXTB__
char * __bgdexport( mod_debug, modules_dependency )[] =
{
    "libkey",
    "librender",
    NULL
};
#else
extern DLVARFIXUP __bgdexport( mod_debug, locals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_debug, globals_fixup )[];
extern void __bgdexport( mod_debug, process_exec_hook )( INSTANCE * r );
extern void __bgdexport( mod_debug, module_initialize )();
extern char * __bgdexport( mod_debug, modules_dependency )[];
#endif


#endif

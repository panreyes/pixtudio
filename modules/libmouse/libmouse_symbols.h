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

#ifndef __MOUSE_H
#define __MOUSE_H

#include <pxtdl.h>

#ifndef __PXTB__
extern DLVARFIXUP __pxtexport( libmouse, globals_fixup )[];
extern HOOK __pxtexport( libmouse, handler_hooks )[];
extern void __pxtexport( libmouse, module_initialize )();
#endif

/* --------------------------------------------------------------------------- */

char __pxtexport( libmouse, globals_def )[] =
    "STRUCT mouse\n"
    "x = 99999, y = 99999;\n"
    "z = -512;\n"
    "file;\n"
    "graph;\n"
    "angle;\n"
    "size = 100;\n"
    "flags;\n"
    "region;\n"
    "left, middle, right;\n"
    "wheelup, wheeldown;\n"
    "wheelup, wheeldown;\n"
    "BYTE modr=255, modg=255, modb=255;\n"
    "END\n";

/* --------------------------------------------------------------------------- */

char * __pxtexport( libmouse, module_dependencies )[] =
{
    "libsdlhandler",
    "libgrbase",
    "libvideo",
    "libblit",
    "librender", // Add by Sandman
    NULL
};

#endif

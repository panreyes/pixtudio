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

#ifndef _FMATH_H
#define _FMATH_H

#include <math.h>

#include "pxtcore.h"

/* Rutinas matemáticas de punto fijo, basadas en Allegro */

#ifndef M_PI
#define M_PI 3.14159265358979323846 /* PI */
#endif

#ifndef ABS
#define ABS(x) (((x) < 0) ? -(x) : (x))
#endif
#ifndef SGN
#define SGN(a) (((a) < 0) ? -1 : !(a) ? 0 : 1)
#endif

typedef long int fixed;

extern fixed ftofixed(float x);
extern float fixedtof(fixed x);
extern fixed itofixed(int x);
extern int fixedtoi(fixed x);
extern int fixed_ceil(fixed x);
extern fixed fixed_cos(int x);
extern fixed fixed_sin(int x);
extern fixed fixed_mul(int x, int y);
extern fixed fixed_div(int x, int y);
extern void init_cos_tables();

#endif

#ifndef AGUA_H
#define AGUA_H
#include "chipmunk.h"
#include "pxtdl.h"
#include "pxtrtm.h"
#include "xstrings.h"
#include "dlvaracc.h"
#include "g_bitmap.h"
#include "libdraw.h"
#include "librender.h"
#include "mod_map.h"
#include "globales.h"
#include "locales.h"
int modChipmunkPintaAgua(INSTANCE *my, intptr_t *params);
int modChipmunkMetaball(INSTANCE *my, intptr_t *params);
int modChipmunkSetEfector(INSTANCE *my, intptr_t *params);
int modChipmunkEmulateAgua(INSTANCE *my, intptr_t *params);
#endif

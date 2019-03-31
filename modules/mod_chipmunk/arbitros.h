#ifndef ARBITROS_H
#define ARBITROS_H

#include "chipmunk.h"
#include "pxtdl.h"
#include "pxtrtm.h"
#include "xstrings.h"
#include <math.h>
#include "dlvaracc.h"
#include "libdraw.h"
#include "librender.h"
#include "mod_map.h"
#include "globales.h"
#include "locales.h"
#include "constantes.h"
#include "Arreglos.h"
#include "LL.h"
#include "Handlers.h"

int modArbiterGetNumContactPoints(INSTANCE *my, intptr_t *params);
int modArbiterIsFirstContact(INSTANCE *my, intptr_t *params);
int modArbiterGetNormal(INSTANCE *my, intptr_t *params);
int modArbiterGetPoint(INSTANCE *my, intptr_t *params);
int modArbiterGetDepth(INSTANCE *my, intptr_t *params);
int modArbiterTotalImpulseWithFriction(INSTANCE *my, intptr_t *params);
int modArbiterTotalImpulse(INSTANCE *my, intptr_t *params);
int modArbiterProcessA(INSTANCE *my, intptr_t *params);
int modArbiterProcessB(INSTANCE *my, intptr_t *params);
int modArbiterGetElasticity(INSTANCE *my, intptr_t *params);
int modArbiterSetElasticity(INSTANCE *my, intptr_t *params);
int modArbiterGetFriction(INSTANCE *my, intptr_t *params);
int modArbiterSetFriction(INSTANCE *my, intptr_t *params);
int modArbiterGetSurfaceVelocity(INSTANCE *my, intptr_t *params);
int modArbiterSetSurfaceVelocity(INSTANCE *my, intptr_t *params);

#endif

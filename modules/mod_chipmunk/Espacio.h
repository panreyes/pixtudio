#ifndef ESPACIO_H
#define ESPACIO_H

#include <stdlib.h>
#include <math.h>

#include "chipmunk.h"
#include "pxtdl.h"
#include "pxtrtm.h"
#include "xstrings.h"
#include "dlvaracc.h"
#include "libdraw.h"
#include "librender.h"
#include "mod_map.h"

int modcpSpaceGetCurrentTimeStep(INSTANCE *my, intptr_t *params);
int modGetStaticBody(INSTANCE *my, intptr_t *params);
int modcpSpaceActivateShapesTouchingShape(INSTANCE *my, intptr_t *params);
int modcpSpaceResizeStaticHash(INSTANCE *my, intptr_t *params);
int modcpSpaceResizeActiveHash(INSTANCE *my, intptr_t *params);
int modcpSpaceUseSpatialHash(INSTANCE *my, intptr_t *params);

#endif

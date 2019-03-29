#ifndef CUERPO_H
#define CUERPO_H

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
#include "Arreglos.h"
#include "LL.h"

int modgetBody(INSTANCE *my, intptr_t *params);
int modcpBodyLocal2World(INSTANCE *my, intptr_t *params);
int modDefcpBody(INSTANCE *my, intptr_t *params);
int modGetEcpBody(INSTANCE *my, intptr_t *params);
int modcpBodySetMass(INSTANCE *my, intptr_t *params);
int modcpBodySetMoment(INSTANCE *my, intptr_t *params);
int modcpBodySetAngle(INSTANCE *my, intptr_t *params);
int modcpBodyUpdatePosition(INSTANCE *my, intptr_t *params);
int modcpBodyResetForces(INSTANCE *my, intptr_t *params);
int modcpBodyIsSleeping(INSTANCE *my, intptr_t *params);
int modcpBodySleep(INSTANCE *my, intptr_t *params);
int modcpBodyActivate(INSTANCE *my, intptr_t *params);
int modcpBodyIsStatic(INSTANCE *my, intptr_t *params);
int modcpBodyIsRogue(INSTANCE *my, intptr_t *params);
int modcpBodySleepWithGroup(INSTANCE *my, intptr_t *params);
int modcpBodyApplyForce(INSTANCE *my, intptr_t *params);
int modcpBodyApplyImpulse(INSTANCE *my, intptr_t *params);
int modcpBodyWorld2Local(INSTANCE *my, intptr_t *params);
int modcpBodySlew(INSTANCE *my, intptr_t *params);
int modcpBodyUpdateVelocity(INSTANCE *my, intptr_t *params);
int modActivateProcessTouchingIt(INSTANCE *my, intptr_t *params);
void addListaProcesos(INSTANCE *ins);
int modaddCircleShape(INSTANCE *my, intptr_t *params);
int modaddSegmentShape(INSTANCE *my, intptr_t *params);
int modaddPolyShape(INSTANCE *my, intptr_t *params);
int creaPoly(int *params, cpBody *bod);
int modaddSegmentShapeTo(INSTANCE *my, intptr_t *params);
#define ajustaTam LOCDWORD(mod_chipmunk, my, LOC_SIZE) / 100.0
int creaBodyAndShapeAutomat(INSTANCE *my);
int modcpCalculaConvexHull(INSTANCE *my, intptr_t *params);
#endif

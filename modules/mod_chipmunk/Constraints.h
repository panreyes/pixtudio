#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

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

// int addConstr(cpBody *bod1, cpBody *bod2,cpConstraint * cons);
int modaddDampedSpring(INSTANCE *my, intptr_t *params);
int modaddPinJoint(INSTANCE *my, intptr_t *params);
int modaddPivotJoint2(INSTANCE *my, intptr_t *params);
int modaddSlideJoint(INSTANCE *my, intptr_t *params);
int modaddGrooveJoint(INSTANCE *my, intptr_t *params);
int modaddSimpleMotor(INSTANCE *my, intptr_t *params);
int modaddRatchetJoint(INSTANCE *my, intptr_t *params);
int modaddRotaryLimitJoint(INSTANCE *my, intptr_t *params);
int modaddGearJoint(INSTANCE *my, intptr_t *params);
int modaddDampedRotarySpring(INSTANCE *my, intptr_t *params);
int modaddPivotJoint(INSTANCE *my, intptr_t *params);

int modsetPinJointProperties(INSTANCE *my, intptr_t *params);
int modsetSlideJointProperties(INSTANCE *my, intptr_t *params);
int modsetPivotJointProperties(INSTANCE *my, intptr_t *params);
int modsetGrooveJointProperties(INSTANCE *my, intptr_t *params);
int modsetDampedSpringProperties(INSTANCE *my, intptr_t *params);
int modsetDampedRotarySpringProperties(INSTANCE *my, intptr_t *params);
int modsetRotaryLimitJointProperties(INSTANCE *my, intptr_t *params);
int modsetRatchetJointProperties(INSTANCE *my, intptr_t *params);
int modsetGearJointProperties(INSTANCE *my, intptr_t *params);
int modsetSimpleMotorProperties(INSTANCE *my, intptr_t *params);
int modgetPinJointProperties(INSTANCE *my, intptr_t *params);
int modgetSlideJointProperties(INSTANCE *my, intptr_t *params);
int modgetPivotJointProperties(INSTANCE *my, intptr_t *params);
int modgetGrooveJointProperties(INSTANCE *my, intptr_t *params);
int modgetDampedSpringProperties(INSTANCE *my, intptr_t *params);
int modgetDampedRotarySpringProperties(INSTANCE *my, intptr_t *params);
int modgetRotaryLimitJointProperties(INSTANCE *my, intptr_t *params);
int modgetRatchetJointProperties(INSTANCE *my, intptr_t *params);
int modgetGearJointProperties(INSTANCE *my, intptr_t *params);
int modgetSimpleMotorProperties(INSTANCE *my, intptr_t *params);

int modcpConstraintGetImpulse(INSTANCE *my, intptr_t *params);
int modDefcpConstraint(INSTANCE *my, intptr_t *params);
int modGetcpConstraint(INSTANCE *my, intptr_t *params);
int modcpConstraintSetPostSolveFunc(INSTANCE *my, intptr_t *params);
int modcpConstraintSetPreSolveFunc(INSTANCE *my, intptr_t *params);

int modGetFathetA(INSTANCE *my, intptr_t *params);
int modGetFathetB(INSTANCE *my, intptr_t *params);

int modremoveConstraint(INSTANCE *my, intptr_t *params);
void eliminaConstraint(void *par);

#endif

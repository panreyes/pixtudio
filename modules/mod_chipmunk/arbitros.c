#include "arbitros.h"
typedef struct modChipmunkStruct_Data_Pointer {
    int father;
    int estado;
    struct modChipmunkStruct_Data_Pointer *sig;
    int x, y;
    cpBody *body;
    int angle;
    int nShapes;
    cpShape **Shapes;
    int nConstraints;
    cpConstraint **Constraints;
    cpBody **constraintsBody;
    int typeShape;
} * DataPointer;

int modArbiterGetNumContactPoints(INSTANCE *my, intptr_t *params) {
    return cpArbiterGetCount((cpArbiter *)params[0]);
}

int modArbiterIsFirstContact(INSTANCE *my, intptr_t *params) {
    return cpArbiterIsFirstContact((cpArbiter *)params[0]);
}

int modArbiterGetNormal(INSTANCE *my, intptr_t *params) {
    cpVect v = cpArbiterGetNormal((cpArbiter *)params[0], params[1]);
    *(float *)params[2] = v.x;
    *(float *)params[3] = v.y;
    return 1;
}

int modArbiterGetPoint(INSTANCE *my, intptr_t *params) {
    cpVect v = cpArbiterGetPoint((cpArbiter *)params[0], params[1]);
    *(float *)params[2] = v.x;
    *(float *)params[3] = v.y;
    return 1;
}

int modArbiterGetDepth(INSTANCE *my, intptr_t *params) {
    float f = cpArbiterGetDepth((cpArbiter *)params[0], params[1]);
    return *(int *)&f;
}

int modArbiterTotalImpulseWithFriction(INSTANCE *my, intptr_t *params) {
    cpVect v = cpArbiterTotalImpulseWithFriction((cpArbiter *)params[0]);
    *(float *)params[1] = v.x;
    *(float *)params[2] = v.y;
    return 1;
}

int modArbiterTotalImpulse(INSTANCE *my, intptr_t *params) {
    cpVect v = cpArbiterTotalImpulse((cpArbiter *)params[0]);
    *(float *)params[1] = v.x;
    *(float *)params[2] = v.y;
    return 1;
}

int modArbiterProcessA(INSTANCE *my, intptr_t *params) {
    cpBody *b, *c;
    cpArbiterGetBodies((cpArbiter *)params[0], &b, &c);
    return ((DataPointer)b->data)->father;
}

int modArbiterProcessB(INSTANCE *my, intptr_t *params) {
    cpBody *b, *c;
    cpArbiterGetBodies((cpArbiter *)params[0], &b, &c);
    return ((DataPointer)c->data)->father;
}

int modArbiterGetElasticity(INSTANCE *my, intptr_t *params) {
    float f = cpArbiterGetElasticity((cpArbiter *)params[0]);
    return *(int *)&f;
}

int modArbiterSetElasticity(INSTANCE *my, intptr_t *params) {
    cpArbiterSetElasticity((cpArbiter *)params[0], *(float *)&params[1]);
    return 1;
}

int modArbiterGetFriction(INSTANCE *my, intptr_t *params) {
    float f = cpArbiterGetFriction((cpArbiter *)params[0]);
    return *(int *)&f;
}

int modArbiterSetFriction(INSTANCE *my, intptr_t *params) {
    cpArbiterSetFriction((cpArbiter *)params[0], *(float *)&params[1]);
    return 1;
}

int modArbiterGetSurfaceVelocity(INSTANCE *my, intptr_t *params) {
    cpVect v = cpArbiterGetSurfaceVelocity((cpArbiter *)params[0]);
    *(float *)params[1] = v.x;
    *(float *)params[2] = v.y;
    return 1;
}

int modArbiterSetSurfaceVelocity(INSTANCE *my, intptr_t *params) {
    cpArbiterSetSurfaceVelocity((cpArbiter *)params[0],
                                cpv(*(float *)&params[1], *(float *)&params[2]));
    return 1;
}

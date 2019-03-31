#include "Espacio.h"

extern cpSpace *modChipmunk_cpEspacio;

int modcpSpaceGetCurrentTimeStep(INSTANCE *my, intptr_t *params) {
    float r = cpSpaceGetCurrentTimeStep(modChipmunk_cpEspacio);
    return *(int *)&r;
}

int modGetStaticBody(INSTANCE *my, intptr_t *params) {
    return modChipmunk_cpEspacio->staticBody;
}

int modcpSpaceActivateShapesTouchingShape(INSTANCE *my, intptr_t *params) {
    cpSpaceActivateShapesTouchingShape(modChipmunk_cpEspacio, (cpShape *)params[0]);
    return 0;
}
int modcpSpaceResizeStaticHash(INSTANCE *my, intptr_t *params) {
    // cpHashResizeHash(modChipmunk_cpEspacio,*(( float * ) &params[0]),params[1]);
    printf("Función en desuso\n");
    return 0;
}

int modcpSpaceResizeActiveHash(INSTANCE *my, intptr_t *params) {
    // cpSpaceResizeActiveHash(modChipmunk_cpEspacio,*(( float * ) &params[0]),params[1]);
    printf("Función en desuso\n");
    return 0;
}

int modcpSpaceUseSpatialHash(INSTANCE *my, intptr_t *params) {
    cpSpaceUseSpatialHash(modChipmunk_cpEspacio, *(float *)&params[0], params[1]);
    return 1;
}

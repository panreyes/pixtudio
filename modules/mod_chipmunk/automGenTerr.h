#ifndef AUTOGENTERR_H
#define AUTOGENTERR_H
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

int modChipmunkGeneraTerreno(INSTANCE *my, intptr_t *params);
GRAPH *modChipmunkObtenTodosBordes(GRAPH *mapa1);
void recursApro(int inic, int fin, modChipmunkStruct_Arreglo *coord, uint8_t res[], float umb);
modChipmunkStruct_Arreglo *modChipmunkVertices(GRAPH *map, int i, int j);
modChipmunkStruct_Arreglo *aproxP(modChipmunkStruct_Arreglo *coord, float umb);
int modChipmunkEliminaTerreno(INSTANCE *my, intptr_t *params);
int modChipmunkGetElement(INSTANCE *my, intptr_t *params);
int modChipmunkCantElement(INSTANCE *my, intptr_t *params);
#endif

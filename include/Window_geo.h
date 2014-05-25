#ifndef __WINDOW_GEO_H
#define __WINDOW_GEO_H

#include "Polygon.h"
#include "Mesh.h"

void window_geo_init(void);

void window_geo_addPolyVertor (Vector v);

void window_geo_extrudeMe (void);

int window_geo_isExtruded(void);

void window_geo_drawPoly(void);

void window_geo_drawMesh(void);

#endif // ( __WINDOW_GEO_H )

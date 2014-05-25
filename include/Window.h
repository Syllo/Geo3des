#ifndef __WINDOW_H
#define __WINDOW_H

#include <stdlib.h>
#include "Vector.h"
#include "Polygon.h"
#include "Mesh.h"
#include "Window_geo.h"
#include <GL/glut.h>
#include <GL/glx.h>

#define PAS_DE_TRANSLATION 0.5
#define PAS_DE_ROTATION 10
#define PAS_DE_SCALE 0.1
#define DIM2 0
#define DIM3 1

int InitWindow(int argc, char**argv);

#endif // ( __WINDOW_H )

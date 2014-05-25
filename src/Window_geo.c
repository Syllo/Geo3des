#include "Window_geo.h"

static int is_extruded = false;
static Polygon poly;
static Mesh mesh;
static int slice = 10;

void window_geo_init(void){
    is_extruded = false;
    P_init(&poly);
    M_init(&mesh);
    poly. _is_closed = true;
}

void window_geo_addPolyVertor (Vector v){
    if(! is_extruded)
        P_addVertex(&poly, v);
}

void window_geo_extrudeMe (void){
    if(! is_extruded){
        is_extruded = true;
        M_perlinExtrude(&mesh, &poly, slice);
    }
}

int window_geo_isExtruded(void){
    return is_extruded;
}

void window_geo_drawPoly(void){
    P_draw(&poly);
}

void window_geo_drawMesh(void){
    M_draw(&mesh);
}

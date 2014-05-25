/**
 * \file Window_geo.c
 * \brief Fichier de contenu de fenêtre. (source)
 * \author Maxime SCHMITT
 * \author Arash HABIBI
 * \date 2014
 * \copyright GPL version 3 ou version ultérieur.
 */

/*
   Copyright (C) 2014 Maxime SCHMITT, Arash HABIBI

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */

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

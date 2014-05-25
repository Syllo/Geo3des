/**
 * \file Mesh.h
 * \brief Fichier de fonctions des maillages (source)
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

#include "Mesh.h"

Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4){
    Quad q;
    q. _vertices[0] = v1;
    q. _vertices[1] = v2;
    q. _vertices[2] = v3;
    q. _vertices[3] = v4;
    return q;
}

static void M_init(Mesh *m){
    m-> _nb_quads = 0;
    m-> _is_filled = false;
}

Mesh* M_new(){
    Mesh *m = malloc(sizeof(*m));
    if( m != NULL )
        M_init(m);
    else
        perror("malloc");
    return m;
}

static void Q_print(Quad q){
    for(unsigned int i=0; i < 4; i++)
        V_print(q. _vertices[i], "Point du quadrilatère");
}

void M_print(Mesh *P, char *message){
    fprintf(stderr, "%s\n", message);
    for(unsigned int i=0; i < P-> _nb_quads; i++){
        fprintf(stderr, "Quadrillatère %u\n", i);
        Q_print(P-> _quads[i]);
    }
}

void M_addQuad(Mesh *P, Quad q){
    if( P-> _nb_quads != M_MAX_QUADS )
        P-> _quads[P-> _nb_quads++] = q;
}

void M_addSlice(Mesh *P, Polygon *p1, Polygon *p2){
    if(p1-> _nb_vertices == p2-> _nb_vertices)
        for (int i = 0; i < p1->_nb_vertices; ++i)
        {
            int j = (i + 1) % p1->_nb_vertices;
            Quad q = Q_new
                (
                 p1->_vertices[i],
                 p2->_vertices[i],
                 p2->_vertices[j],
                 p1->_vertices[j]
                );
            M_addQuad (P, q);
        }
}

void M_revolution(Mesh *P, Polygon *p1, int nb_slices){
    Polygon a, b;
    P_copy (p1, & a);
    P_copy (p1, & b);

    double angle = (double) 2.0 * M_PI / nb_slices;
    for (int i = 0; i < nb_slices; ++i)
    {
        P_tournerAutourDeLAxeY (& b, angle);
        M_addSlice (P, & a, & b);
        P_copy (& b, & a);
    }
}


void M_perlinExtrude(Mesh *QM, Polygon *p, int nb_slices){
    Polygon a, b;
    P_copy (p, & a);
    P_copy (p, & b);

    for (int i = 0; i < nb_slices; ++i)
    {
        Vector center = P_center (& b);
        Vector noise = PRLN_vectorNoise (center);
        P_translate (& b, noise);
        P_rotate (& b, noise);
        M_addSlice (QM, & a, & b);
        P_copy (& b, & a);
    }
}

static void Q_draw(Quad q){
    glBegin (GL_POLYGON);

    for (int i = 0; i < 4; ++i)
    {
        Vector v = q. _vertices[i];
        glVertex3d (v.x, v.y, v.z);
    }

    glEnd ();
}

void M_draw(Mesh *P){
    for(unsigned int i=0; i < P-> _nb_quads; i++)
        Q_draw(P-> _quads[i]);
}

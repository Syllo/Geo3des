/**
 * \file Mesh.h
 * \brief Fichier de fonctions des maillages (header)
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

#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "Vector.h"
#include "Polygon.h"
#include "Perlin.h"

/** Nombre maximum de quadrilatères.
*/
#define M_MAX_QUADS 5000

/** Type Quad des quadrilatères.
*/
typedef struct
{
    Vector _vertices[4]; /**< Les points du quadrilatère. */
} Quad;

/** Crée un nouveau quadrilatère avec quatre points.
 * \see Vector
 * \see Quad
 * \param v1 Un point
 * \param v2 Un point
 * \param v3 Un point
 * \param v4 Un point
 * \return Un quadrilatère formé des quatre points.
 */
Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4);

/** Type Mesh des maillages contenant des quadrilatères.
*/
typedef struct
{
    int _nb_quads;              /**< Nombre de quadrilatères courants. */
    Quad _quads[M_MAX_QUADS];   /**< Tableau contenant les quadrilatères. */
    int _is_filled;             /**< Si le quadrilatère est plein. */
} Mesh;

void M_init(Mesh *m);
/** Crée un nouveau maillage
 * \see Mesh
 * \return Un maillage vide.
 */
Mesh* M_new();

/** Affiche un maillage sur la sortie d'erreur (stderr) avec un message pour débuggage.
 * \see Mesh
 * \param P Un maillage.
 * \param message Le message à afficher.
 */
void M_print(Mesh *P, char *message);

/** Ajoute un quadrilatère au Mesh.
 * \param P Un maillage.
 * \param q Un quadrilatère
 * \warning Si le maillage est plein l'ajout est ignorée.
 */
void M_addQuad(Mesh *P, Quad q);

/** Je sais pas pour l'instant !.
*/
void M_addSlice(Mesh *P, Polygon *p1, Polygon *p2);

/** Effectue une révolution du Mesh.
 * \see Mesh
 * \see Polygon
 * \param P Le maillage.
 * \param p1 Un polygone.
 * \param nb_slices Le nombre de tranches.
 */
void M_revolution(Mesh *P, Polygon *p1, int nb_slices);

/** Effectue une extrusion sur le maillage avec un bruit de Perlin.
 * \see Polygon
 * \see Mesh
 * \param QM Le maillage.
 * \param p Un polygone.
 * \param nb_slices Le nombre de tranches.
 */
void M_perlinExtrude(Mesh *QM, Polygon *p, int nb_slices);

/** Dessine dans OpenGl le maillage.
 * \see Mesh
 * \param P Le maillage.
 */
void M_draw(Mesh *P);

#endif // ( _MESH_H_ )

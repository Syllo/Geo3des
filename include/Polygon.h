/**
 * \file Polygon.h
 * \brief Fichier des fonctions sur les polygones. (header)
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

#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "Vector.h"

/** Nombre max de vecteurs pour un polygone.
*/
#define P_MAX_VERTICES 1000

/** Definition d'un polygone.
*/
typedef struct
{
    int _nb_vertices;                   /**< Nombre de points actuels */
    Vector _vertices[P_MAX_VERTICES];   /**< Le tableau contenant les points (pile) */
    int _is_closed;                     /**< Si le polygone est fermé (premier point = dernier) */
    int _is_filled;                     /**< Si le polygone est rempli (affichage) */
    int _is_convex;                     /**< Si le polygone est convexe */
} Polygon;

/** Initialise un polygone avec zero sommets.
 * \see Polygon
 * \param p Un pointeur vers un polygone.
 * \warning Le polygone doit être alloué sinon le resultat n'est pas garanti.
 */
void P_init(Polygon *p);

/** Copie un polygone dans un autre.
 * \see Polygon
 * \param original Le polygone à copier.
 * \param copie Le polygone à ecraser.
 * \warning Les deux polygones doivent êtres alloués sinon le resultat n'est pas garanti.
 */
void P_copy(Polygon *original, Polygon *copie);

/** Ajoute un point au sommet de la pile de points.
 * \see Polygon
 * \see Vector
 * \param P Le polygone dans lequel un point est ajouté.
 * \param pos Le vecteur à ajouter au polygone.
 * \warning Si le polygone à atteint sa capacité maximale le sommet n'est pas ajouté.
 */
void P_addVertex(Polygon *P, Vector pos);

/** Retire le dernier sommet ajouté.
 * \see Polygon
 * \param P Le polygone auquel on retire un sommet.
 */
void P_removeLastVertex(Polygon *P);

/** Dessine un polygone dans OpenGL.
 * \see Polygon
 * \param P Le polygone.
 */
void P_draw(Polygon *P);

/** Affiche sur la sortie d'erreur (stderr) le polygone avec un message pour debuggage.
 * \see Polygon
 * \param P Le polygone.
 * \param message Le message à afficher.
 */
void P_print(Polygon *P, char *message);

/** Renvoie vrai (true) si le polygone est convexe et faux (false) sinon.
 * \see true
 * \see false
 * \see Polygon
 * \param P Un polygone.
 */
int P_isConvex(Polygon *P);

/** Test si M est à droite de chaque bords.
 * \see true
 * \see false
 * \see Vector
 * \see Polygon
 * \param P Un polygone
 * \param M Le vecteur à tester.
 * \return Vrai (true) si M est à droite de chaque bords, faux (false) sinon.
 */
int P_isOnTheLeftOfAllEdges(Polygon *P, Vector M);

/** Renvoie le nombre de bords qu'intersecte la demi-droite Mu_ray.
 * \see true
 * \see false
 * \see Vector
 * \see Polygon
 * \param P Un polygone.
 * \param M Le début de la demi-droite.
 * \param u_ray Un point de la demi-droite.
 * \return Vrai (true) si M est à droite de chaque bords, faux (false) sinon.
 */
int P_nbEdgesIntersectedByRay(Polygon *P, Vector M, Vector u_ray);

/** Test si M est dans le polygone P.
 * \see true
 * \see false
 * \see Vector
 * \see Polygon
 * \param P Un polygone
 * \param M Le vecteur à tester.
 * \return Vrai (true) si M est dans le polygone P, faux (false) sinon.
 */
int P_isInside(Polygon *P, Vector M);

/** Effectue une rotation du polygone autour de l'axe des y.
 * \see Polygon
 * \param P Le polygone.
 * \param radians L'angle de rotation en radians.
 */
void  P_tournerAutourDeLAxeY(Polygon *P, double radians);

/** Renvoie le centre du polygone.
 * \see Vector
 * \see Polygon
 * \param P Un polygone.
 * \return Le point central au polygone.
 */
Vector P_center(Polygon *P);

/** Renvoie le vecteur normal unitaire au polygone supposé plan.
 * \see Vector
 * \see Polygon
 * \param P Un polygone.
 * \return Le vecteur définissant le plan.
 */
Vector P_normal(Polygon *P);

/** Multiplie chaque point du polygone par un facteur "factor".
 * \see Polygon
 * \param P Un polygone.
 * \param factor Le facteur multiplicatif.
 */
void P_scale(Polygon *P, double factor);

/** Effectue une translation du polygone d'un vecteur "trans".
 * \see Polygon
 * \param P Un polygone
 * \param trans Un vecteur de translation.
 */
void P_translate(Polygon *P, Vector trans);

/** Effectue une rotation du polygone autour de son centre de façon à ce que son vecteur normal soit égal à normal.
 * \see Polygon
 * \param P Le polygone
 * \param normal Un vecteur.
 */
void P_rotate(Polygon *P, Vector normal);

#endif // __POLYGON_H__

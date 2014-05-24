/**
 * \file Vector.h
 * \brief Fichier de vecteur et des fonctions associés. (header)
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

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** La marge d'erreur pour le test d'égalité entre flottants
*/
#define ERROR_RATIO 1e-10

enum{
    false,      /**< valeur pour faux */
    true,       /**< valeur pour vrai */
};

/** Définition d'un Point.
 */
typedef struct
{
    float x,    /**< coordonnée sur l'axe des x */
          y,    /**< coordonnée sur l'axe des y */
          z;    /**< coordonnée sur l'axe des z */
} Vector;

/** Crée un nouveau vecteur.
 * \param x La coordonnée selon x
 * \param y La coordonnée selon y
 * \param z La coordonnée selon z
 * \return Un vecteur
 * \see Vector
 */
Vector V_new(float x, float y, float z);

/** Affiche le Vecteur et un message sur stderr.
 * \param v Le Vecteur à afficher
 * \param message Le message à afficher
 * \see Vector
 */
void V_print(Vector v, char *message);

/** Fait l'addition de deux vecteurs.
 * \param v1 Un Vecteur
 * \param v2 Un Vecteur
 * \return Un Vecteur
 * \see Vector
 * Fait l'addition des champs un à un des deux Vecteurs et
 * retourne le résultat v1+v2.
 */
Vector V_add(Vector v1, Vector v2);

/** Effectue la soustraction de deux vecteurs.
 * \param v1 Un Vecteur
 * \param v2 Un Vecteur
 * \return Un Vecteur
 * \see Vector
 * Effectue la soustraction des champs un à un des deux Vecteurs et
 * retourne le résultat v1-v2.
 */
Vector V_substract(Vector v1, Vector v2);

/** Multiplie le vecteur par un scalaire.
 * \param v Un Vecteur
 * \param lambda Un scalaire
 * \return Un Vecteur
 * \see Vector
 * Effectue la multiplication de v par un scalaire et
 * retourne v * lambda.
 */
Vector V_multiply(double lambda, Vector v);

/** Effectue le produit vectoriel entre deux Vecteurs.
 * \param v1 Un Vecteur
 * \param v2 Un Vecteur
 * \return Un Vecteur
 * \see Vector
 * Effectue le produit vectoriel v1^v2.
 */
Vector V_cross(Vector v1, Vector v2);

/** Effectue le produit scalaire entre deux Vecteurs.
 * \param v1 Un Vecteur
 * \param v2 Un Vecteur
 * \return Un Vecteur
 * \see Vector
 * Effectue le produit scalaire v1*v2.
 */
double V_dot(Vector v1, Vector v2);

/** Test si M se trouve à droite de la droite AB.
 * \param M Le Vecteur à tester.
 * \param A Un point d'une droite
 * \param B Un point d'une droite
 * \see Vector
 * \see true
 * \see false
 * \return Vrai (true) si M se trouve à droite de la droite AB, faux (false)sinon.
 * \return Si A et B sont les mêmes -2 est retourné et si M se trouve sur AB -1 est retourné
 */
int V_isOnTheRight(Vector M, Vector A, Vector B);

/** Test si le segment formé par p1 et p2 croise celui formé par q1 et q2.
 * \param p1 Un Vecteur du premier segment.
 * \param p2 Un Vecteur du premier segment.
 * \param q1 Un Vecteur du deuxième segment.
 * \param q2 Un Vecteur du deuxième segment.
 * \see Vector
 * \see true
 * \see false
 * \return Vrai (true) si les deux segments se croisent et faux (false) sinon.
 * \return -1 est renvoyé si p1 et p2 ou q1 et q2 sont confondues.
 */
int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2);

/** Test si la demi-droite d'origine M et passant par u_ray croise le segment p1p2.
 * \param M Le point d'origine de la demi-droite.
 * \param u_ray Un point appartenant à la demi-droite.
 * \param p1 Un Vecteur du premier segment.
 * \param p2 Un Vecteur du premier segment.
 * \see Vector
 * \see true
 * \see false
 * \return Vrai (true) si la demi-droite croise le segment p1p2 et faux (false) sinon.
 * \return -1 est renvoyé si M et u_ray ou p1 et p2 sont confondues.
 */
int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2);

/** Test si d1 est sur le segment p1p2
 * \param p1 Un point formant le segment.
 * \param p2 Un point formant le segment.
 * \param d1 Le point à tester.
 * \see Vector
 * \see true
 * \see false
 * \return Vrai (true) si le point d1 est sur le segment et faux (false) sinon.
 * \return -1 est renvoyé si p1 et p2 sont confondues.
 */
int V_isSurSegment(Vector p1, Vector p2, Vector d1);

/** Retourne le module du vecteur v.
 * \see Vector
 * \param v Un vecteur.
 * \return Le module du vecteur
 */
double V_length(Vector v);

/** Retourne un vecteur unitaire colinéaire à v.
 * \see Vector
 * \param v Un Vecteur.
 * \return Un vecteur unitaire colinéaire à v.
 */
Vector V_unit(Vector v);

/** Effectue une rotation autour de l'axe y du point p d'un angle radians.
 * \see Vector
 * \param p Le point à déplacer.
 * \param radians L'angle de rotation.
 * \return Le vecteur déplacé.
 */
Vector V_tournerAutourDeLAxeY(Vector p, double radians);


/** Effectue une rotation autour de l'axe z du point p d'un angle "radians".
 * \see Vector
 * \param p Le point à déplacer.
 * \param radians L'angle de rotation.
 * \return Le vecteur déplacé.
 */
Vector V_tournerAutourDeLAxeZ(Vector p, double radians);

/** Projette p sur le plan qui a pour vecteur normal "normal".
 * \see Vector
 * \param p Le point à projeté.
 * \param normal Le vecteur normal au plan de projection.
 * \return Le point projeté.
 */
Vector V_ProjectOnPlane(Vector p, Vector normal);

/** Trouve la norme de p selon un vecteur u.
 * \see Vector
 * \param p Un point.
 * \param u Un Vecteur.
 * \return La norme de p selon le Vecteur u.
 */
double V_decompose(Vector p, Vector u);

/** Trouve le point dans le repère orthonormée ((1,0,0) , (0,1,0) , (0,0,1))
 * \see Vector
 * \param x La norme selon u.
 * \param y La norme selon v.
 * \param z La norme selon w.
 * \param u Un vecteur.
 * \param v Un vecteur.
 * \param w Un vecteur.
 * \return le point dans le repère orthonormée ((1,0,0) , (0,1,0) , (0,0,1))
 */
Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w);

/** Trouve u_x et u_y tel que u_x, u_y et u_z forment un repère orthonormée
 * \see Vector
 * \param u_z Un vecteur
 * \param u_x Un pointeur vers un Vecteur
 * \param u_y Un pointeur vers un Vecteur
 * \warning Il faut que u_x et u_y pointent vers des vecteurs alloués sinon des corruptions
 *          mémoire ainsi que des crash peuvent se produire.
 */
void V_uxUyFromUz(Vector u_z, Vector* u_x, Vector* u_y);

/** Calcule le déterminant entre trois vecteurs.
 * \see Vector
 * \param a Un Vecteur
 * \param b Un Vecteur
 * \param c Un Vecteur
 * \return La valeur du déterminant entre ces trois Vecteurs.
 */
double Det(Vector a, Vector b, Vector c);

/** Determine si le Vecteur est à l'origine
 * \see Vector
 * \see true
 * \see false
 * \param v Un Vecteur.
 * \return Vrai (true) si le vecteur est à l'origine et faux (false) sinon.
 */
int V_IsZero(Vector v);

/** Determine si les deux vecteurs sont égaux
 * \see Vector
 * \see true
 * \see false
 * \param v Un Vecteur.
 * \return Vrai (true) si les vecteurs sont égaux et faux (false) sinon.
 */
int V_equals(Vector v1, Vector v2);

#endif // __VECTOR_H__

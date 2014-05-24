
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Vector.h
  \*======================================================*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    float x, y, z;
} Vector;

Vector V_new(float x, float y, float z);
// retourne un vecteur de composantes x, y et z

void V_print(Vector v, char *message);
// affiche à l'écran les coordonnées de v + un message (debug)

Vector V_add(Vector v1, Vector v2);
// retourne v1+v2

Vector V_substract(Vector v1, Vector v2);
// retourne v1-v2

Vector V_multiply(double lambda, Vector v);
// retourne lambda * v

Vector V_cross(Vector v1, Vector v2);
// retourne le produit vectoriel v1^v2

double V_dot(Vector v1, Vector v2);

int V_isOnTheRight(Vector M, Vector A, Vector B);
// retourne 1 si M est à la droite de la droite (AB) et 0 sinon

int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2);
// retourne 1 si le segment [p1p2] intersect le segment [q1q2]

int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2);
// retourne 1 si la demie droite d'origine M et de direction u_ray
// intersect le segment [p1p2]

double V_length(Vector v);
// retourne le module du vecteur v

Vector V_unit(Vector v);
// retourne un vecteur colinéaire à v mais de longueur 1

Vector V_tournerAutourDeLAxeY(Vector p, double radians);
// Tourne d'un angle de radians le point  p autour de l'axe Y
// et retourne le résultat.
Vector V_tournerAutourDeLAxeZ(Vector p, double radians);
// Tourne d'un angle de radians le point  p autour de l'axe Z
// et retourne le résultat.
Vector V_ProjectOnPlane(Vector p, Vector normal);
//Projete p sur le plan qui a pour vecteur noemal normal
double V_decompose(Vector p, Vector u);
//trouve la norme selon u
Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w);
// retrouve le vecteur dans la base 1,1,1
void V_uxUyFromUz(Vector u_z, Vector* u_x, Vector* u_y);
//trouve les vecteurs u_x et u_y tq u_x,u_y,u_z soient un repère orthonormé
double Det(Vector a, Vector b, Vector c);
//retourne le determinant de abc
int V_IsZero(Vector v);

#endif // __VECTOR_H__

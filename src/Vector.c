/**
 * \file Vector.c
 * \brief Fichier de vecteur et des fonctions associés. (source)
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

#include "Vector.h"

Vector V_new(double x, double y, double z)
{
    Vector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline int min(int a, int b){
    return a > b ? b : a;
}

static inline int max(int a, int b){
    return a > b ? a : b;
}

static inline int zero(double a){
    return a < (0 + ERROR_RATIO) && a > (0 - ERROR_RATIO);
}

void V_print(Vector v, char *message)
{
    fprintf(stderr,"%s : %f %f %f\n",message, v.x, v.y, v.z);
}

Vector V_add(Vector v1, Vector v2){
    Vector v = V_new( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
    return v;
}

Vector V_substract(Vector v1, Vector v2){
    Vector v = V_new( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
    return v;
}

Vector V_multiply(double lambda, Vector v1){
    Vector v = V_new( v1.x * lambda, v1.y * lambda, v1.z * lambda );
    return v;
}

Vector V_cross(Vector v1, Vector v2){
    Vector v = V_new( v1.y * v2.z - v2.y * v1.z,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
            );
    return v;
}

double V_dot(Vector v1, Vector v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

int V_isOnTheRight(Vector M, Vector A, Vector B){
    double det;
    if( V_equals(A,B) )
        return -2;
    det = Det(M, A, B);
    if(zero(det))
        return -1;
    return Det(M, A, B) > 0 ? false : true;
}

int V_segmentsCoplanar(Vector p1, Vector p2, Vector q1, Vector q2){
    if( V_equals(p1, p2) || V_equals(q1, q2) )
        return -1;

    Vector p1p2 = V_substract(p2, p1);
    Vector q1q2 = V_substract(q2, q1);
    Vector p1q1 = V_substract(q1, p1);
    return zero( Det(p1p2, q1q2, p1q1) );
}

int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2){
    if( V_equals(p1, p2) || V_equals(q1, q2) )
        return -1;

    if(!V_segmentsCoplanar(p1,p2,q1,q2))
        return false;

    double detq1 = Det(p1, p2, q1);
    double detq2 = Det(p1, p2, q2);
    double detp1 = Det(q1, q2, p1);
    double detp2 = Det(q1, q2, p2);

    if(zero(detq1) && V_isSurSegment(p1, p2, q1))
        return true;
    if(zero(detq2) && V_isSurSegment(p1, p2, q2))
        return true;
    if(zero(detp1) && V_isSurSegment(q1, q2, p1))
        return true;
    if(zero(detp2) && V_isSurSegment(q1, q2, p2))
        return true;

    if( detq1*detq2 < 0 && detp2*detp1 <0 )
        return true;

    return false;
}

int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2){
    return 0;
}

int V_isSurSegment(Vector p1, Vector p2, Vector d1){
    if( V_equals(p1, p2) )
        return -1;
    return zero(Det(p1, p2, d1)) &&
        d1.x <= max(p1.x, p2.x) && d1.x >= min(p1.x, p2.x) &&
        d1.y <= max(p1.y, p2.y) && d1.y >= min(p1.y, p2.y) &&
        d1.z <= max(p1.z, p2.z) && d1.z >= min(p1.z, p2.z);
}

double V_length(Vector v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vector V_unit(Vector v){
    double longueur = V_length(v);
    return V_new(v.x/longueur, v.y/longueur, v.z/longueur);
}

Vector V_tournerAutourDeLAxeY(Vector p, double radians){
    return V_new(p.x*cos(radians) + p.z*sin(radians),
            p.y,
            -p.x*sin(radians) + p.z*cos(radians)
            );
}

Vector V_tournerAutourDeLAxeZ(Vector p, double radians){
    return V_new(p.x*cos(radians) - p.y*sin(radians),
            p.x*sin(radians) + p.y*cos(radians),
            p.z
            );
}

Vector V_ProjectOnPlane(Vector p, Vector normal){
    Vector u_x, u_y;
    double x, y;
    V_uxUyFromUz(normal, &u_x, &u_y);
    x = V_decompose(p, u_x);
    y = V_decompose(p, u_y);
    return V_recompose(x, y, 0., u_x, u_y, normal);
}

double V_decompose(Vector p, Vector u){
    return V_dot(p,u) * V_length(u);
}

Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w){
    return V_add(V_multiply(x,u), V_add(V_multiply(y,v), V_multiply(z,w)));
}

void V_uxUyFromUz(Vector u_z, Vector* u_x, Vector* u_y){
    Vector y = V_new(0,1,0);
    double size_uz = V_length(u_z);
    if(V_IsZero(V_cross(y,u_z))){
        if( u_z.y < 0 )
            u_x->x = -1 * size_uz;
        else
            u_x->x = 1 * size_uz;
        u_x->y = 0;
        u_x->x = 0;

        u_y->x = 0;
        u_y->y = 0;
        u_y->z = -1 * size_uz;
    }
    else{
        *u_x = V_unit(V_multiply(-1, V_unit( V_cross(u_z, y) )));
        *u_y = V_unit(V_multiply(1, V_unit(V_cross(u_z, *u_x))));
    }
}

double Det(Vector a, Vector b, Vector c){
    return a.x*b.y*c.z + b.x*c.y*a.z + c.x*a.y*b.z - a.x*b.z*c.y - c.x*b.y*a.z - b.x*a.y*c.z;
}

int V_IsZero(Vector v){
    return zero(v.x) && zero(v.y) && zero(v.z);
}

int V_equals(Vector v1, Vector v2){
    return V_IsZero( V_substract(v1, v2) );
}

Vector V_rotate(Vector v, Vector centre, Vector v1, Vector v2){
    double x, y, z;
    Vector u_x_v1, u_y_v1, u_z_v1, u_x_v2, u_y_v2, u_z_v2;
    u_z_v1 = V_unit(v1);
    u_z_v2 = V_unit(v2);

    V_uxUyFromUz(u_z_v1, &u_x_v1, &u_y_v1);
    V_uxUyFromUz(u_z_v2, &u_x_v2, &u_y_v2);

    Vector temp = V_substract(v, centre);
    x = V_decompose(temp, u_x_v1);
    y = V_decompose(temp, u_y_v1);
    z = V_decompose(temp, u_z_v1);
    return V_add(centre, V_recompose(x, y, z, u_x_v2, u_y_v2, u_z_v2));
}

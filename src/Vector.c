
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Vector.c
  \*======================================================*/

#include "Vector.h"
#define ERROR_RATIO 1e-4

enum{
    false, true,
};

//------------------------------------------------

Vector V_new(float x, float y, float z)
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

static inline int zero(float a){
    return a < (0 + ERROR_RATIO) && a > (0 - ERROR_RATIO);
}

void V_print(Vector v, char *message)
{
    fprintf(stderr,"%s : %f %f %f\n",message, v.x,v.y,v.z);
}

Vector V_add(Vector v1, Vector v2){
    Vector v = V_new( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
    return v;
}
// retourne v1+v2

Vector V_substract(Vector v1, Vector v2){
    Vector v = V_new( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
    return v;
}
// retourne v1-v2

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
// retourne le produit vectoriel v1^v2

double V_dot(Vector v1, Vector v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double Det(Vector a, Vector b, Vector c){
    return a.x*b.y*c.z + b.x*c.y*a.z + c.x*a.y*b.z - a.x*b.z*c.y - c.x*b.y*a.z - b.x*a.z*c.z;
}

int V_isOnTheRight(Vector M, Vector A, Vector B){
    float det= Det(M, A, B);
    if(zero(det))
        return -1;
    return Det(M, A, B) > 0 ? false : true;
}
// retourne 1 si M est à la droite de la droite (AB) et 0 sinon

int isSurSegment(Vector p1, Vector p2, Vector d1){
    return zero(Det(p1, p2, d1)) &&
        d1.x <= max(p1.x, p2.x) && d1.x >= min(p1.x, p2.x) &&
        d1.y <= max(p1.y, p2.y) && d1.y >= min(p1.y, p2.y) &&
        d1.z <= max(p1.z, p2.z) && d1.z >= min(p1.z, p2.z)
        ;
}

int V_segmentsCoplanar(Vector p1, Vector p2, Vector q1, Vector q2)
{
    Vector p1p2 = V_new(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    Vector q1q2 = V_new(q2.x - q1.x, q2.y - q1.y, q2.z - q1.z);
    Vector p1q1 = V_new(q1.x - p1.x, q1.y - p1.y, q1.z - p1.z);
    if(zero(Det(p1p2, q1q2, p1q1)))
        return true;
    return false;
}

int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2){

    if(!V_segmentsCoplanar(p1,p2,q1,q2))
        return false;

    float detq1 = Det(p1, p2, q1);
    float detq2 = Det(p1, p2, q2);
    float detp1 = Det(q1, q2, p1);
    float detp2 = Det(q1, q2, p2);

    if(zero(detq1) && isSurSegment(p1, p2, q1))
        return true;
    if(zero(detq2) && isSurSegment(p1, p2, q2))
        return true;
    if(zero(detp1) && isSurSegment(q1, q2, p1))
        return true;
    if(zero(detp2) && isSurSegment(q1, q2, p2))
        return true;

    if( detq1*detq2 < 0 && detp2*detp1 <0 )
        return true;

    return false;
}
// retourne 1 si le segment [p1p2] intersect le segment [q1q2]

int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2){
    return 0;
}
// retourne 1 si la demie droite d'origine M et de direction u_ray
// intersect le segment [p1p2]

double V_length(Vector v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
// retourne le module du vecteur v

Vector V_unit(Vector v){
    double longueur = V_length(v);
    return V_new(v.x/longueur, v.y/longueur, v.z/longueur);
}
// retourne un vecteur colinéaire à v mais de longueur 1

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
// Tourne d'un angle de radians le point  p autour de l'axe Y
// et retourne le résultat.
double V_decompose(Vector p, Vector u){
    return V_dot(p,u) * V_length(u);
}

Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w){
    return V_add(V_multiply(x,u), V_add(V_multiply(y,v), V_multiply(z,w)));
}

int V_IsZero(Vector v){
    return zero(v.x) && zero(v.y) && zero(v.z);
}

void V_uxUyFromUz(Vector u_z, Vector* u_x, Vector* u_y){
    Vector y = V_new(0,1,0);
    if(V_IsZero(V_cross(y,u_z))){
        u_x->x = 1 * V_length(u_z);
        u_x->y = 0;
        u_x->x = 0;

        u_y->x = 0;
        u_y->y = 0;
        u_y->z = -1 * V_length(u_z);
    }
    else{

    }
}

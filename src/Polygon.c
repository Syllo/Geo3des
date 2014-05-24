#include "Polygon.h"

void P_init(Polygon *p){
    p->_nb_vertices = 0;
    p->_is_closed = false;
    p->_is_filled = false;
    p->_is_convex = false;
}

void P_copy(Polygon *original, Polygon *copie){
    copie->_nb_vertices = original->_nb_vertices;
    copie->_is_closed = original->_is_closed;
    copie->_is_filled = original->_is_filled;
    copie->_is_convex = original->_is_convex;
    for(int i=0; i < original->_nb_vertices; i++){
        copie->_vertices[i] =  original->_vertices[i];
    }
}

void P_addVertex(Polygon *P, Vector pos){
    if( P->_nb_vertices != P_MAX_VERTICES )
        P->_vertices[P->_nb_vertices++] = pos;
    P->_is_convex = P_isConvex( P );
}

void P_removeLastVertex(Polygon *P){
    if(P->_nb_vertices > 0)
        P->_nb_vertices--;
    P->_is_convex = P_isConvex( P );
}

void P_draw(Polygon *P){
    int cheat = P-> _is_closed ? 0 : 1;
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    for(int i=0; i < P->_nb_vertices - cheat; i++){
        glVertex3f(P->_vertices[i].x, P->_vertices[i].y, P->_vertices[i].z);
        glVertex3f(P->_vertices[(i+1) % P->_nb_vertices].x, P->_vertices[(i+1) % P->_nb_vertices].y, P->_vertices[(i+1) % P->_nb_vertices].z);
    }
    glEnd();
}

void P_print(Polygon *P, char *message){
    fprintf(stderr, "%s\n", message);
    for(int i=0; i < P->_nb_vertices; i++){
        fprintf(stderr, "%d %f %f %f \n", i, P->_vertices[i].x, P->_vertices[i].y, P->_vertices[i].z);
    }
}

int isConvex(Polygon *P){ ///////////// A FINIR
    double val = 1;
    for(int i=0; i < P->_nb_vertices && val; i++){
        Vector v1 = V_unit(P->_vertices[i]);
        Vector v2 = V_unit(P->_vertices[i+1 % P->_nb_vertices]);
        Vector v3 = V_unit(P->_vertices[i+2 % P->_nb_vertices]);
        val = Det(v1, v2, v3);
    }
}

int P_isOnTheLeftOfAllEdges(Polygon *P, Vector M){
    int result = P-> _nb_vertices > 1;
    int cheat = P-> _is_closed ? 0 : 1;
    for(int i=0; result && i < (P->_nb_vertices - cheat); i++){
        result = ! V_isOnTheRight(M, P->_vertices[i], P->_vertices[i+1 % P->_nb_vertices]);
    }
    return result;
}

int P_nbEdgesIntersectedByRay(Polygon *P, Vector M, Vector u_ray){ /////////// A FAIRE

}

int P_isInside(Polygon *P, Vector M){ /////////////////// A FAIRE

}

void  P_tournerAutourDeLAxeY(Polygon *P, double radians){
    for(int i=0; i < P->_nb_vertices; i++){
        P->_vertices[i] = V_tournerAutourDeLAxeY(P->_vertices[i], radians);
    }
}

Vector P_center(Polygon *P){
    if( P-> _nb_vertices == 0 )
        return V_new(0, 0, 0);

    long double x,y,z;
    x=y=z=0.;
    for(int i=0; i < P-> _nb_vertices; i++){
        x+=P-> _vertices[i].x;
        x+=P-> _vertices[i].y;
        x+=P-> _vertices[i].z;
    }

    return V_new(x/P-> _nb_vertices, y/ P-> _nb_vertices, z/ P-> _nb_vertices);
}

Vector P_normal(Polygon *P){
    if( P-> _nb_vertices < 3 )
        return V_new(0, 0, 0);

    return V_unit( V_cross( V_substract(P-> _vertices[0], P-> _vertices[1]), V_substract(P-> _vertices[0], P-> _vertices[2]) ) );
}

void P_scale(Polygon *P, double factor){
    for(unsigned int i=0; i < P-> _nb_vertices; i++)
        P-> _vertices[i] = V_multiply(factor, P-> _vertices[i]);
}

void P_translate(Polygon *P, Vector trans){
    for(unsigned int i=0; i < P-> _nb_vertices; i++)
        P-> _vertices[i] = V_add(trans, P-> _vertices[i]);
}

void P_rotate(Polygon *P, Vector normal){
    Vector centre = P_center(P);
    Vector normal_poly = P_normal(P);
    for(unsigned int i=0; i < P-> _nb_vertices; i++)
        P-> _vertices[i] = V_rotate(P-> _vertices[i], centre, normal_poly, normal);
}

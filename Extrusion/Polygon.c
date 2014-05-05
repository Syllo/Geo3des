#include "Polygon.h"
void P_init(Polygon *p){
    p->_nb_vertices = 0;
    p->_is_closed = 0;
    p->_is_filled = 0;
    p->_is_convex = 0;
}
// initialise un polygone (0 sommets)

void P_copy(Polygon *original, Polygon *copie){
    copie->_nb_vertices = original->_nb_vertices;
    copie->_is_closed = original->_is_closed;
    copie->_is_filled = original->_is_filled;
    copie->_is_convex = original->_is_convex;
    for(int i=0; i < copie->_nb_vertices; i++){
        copie->_vertices[i].x =  original->_vertices[i].x;
        copie->_vertices[i].y =  original->_vertices[i].y;
        copie->_vertices[i].z =  original->_vertices[i].z;
    }
}
// original et copie sont deux polygones déjà alloués.
// Cette fonction copie les donnée
// depuis original vers copie de façon à ce que les
// deux polygones soient identiques.

void P_addVertex(Polygon *P, Vector pos){
    if(P->_nb_vertices != P_MAX_VERTICES)
        P->_vertices[P->_nb_vertices++] = pos;
}
// ajoute un sommet au polygone P. Ce nouveau sommet est situé en pos.

void P_removeLastVertex(Polygon *P){
    if(P->_nb_vertices > 0)
        P->_nb_vertices--;
}
// enlève le dernier sommet de P

void P_draw(Polygon *P){
    int cheat;
    if(P->_is_closed)
        cheat=0;
    else
        cheat=1;
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    for(int i=0; i < P->_nb_vertices - cheat; i++){
        glVertex3f(P->_vertices[i].x, P->_vertices[i].y, P->_vertices[i].z);
        glVertex3f(P->_vertices[(i+1) % P->_nb_vertices].x, P->_vertices[(i+1) % P->_nb_vertices].y, P->_vertices[(i+1) % P->_nb_vertices].z);
    }
    glEnd();
}
// dessine le polygone P

void P_print(Polygon *P, char *message){
    fprintf(stderr, "%s\n", message);
    for(int i=0; i < P->_nb_vertices; i++){
        fprintf(stderr, "%d %f %f %f \n", i, P->_vertices[i].x, P->_vertices[i].y, P->_vertices[i].z);
    }
}
// Affiche sur une console les données de P
// à des fins de debuggage.

void  P_tournerAutourDeLAxeY(Polygon *P, double radians){
    for(int i=0; i < P->_nb_vertices; i++){
        P->_vertices[i] = V_tournerAutourDeLAxeY(P->_vertices[i], radians);
    }
}
// tourne tous les points de P d'un angle de radians
// radians autour de l'axe Y.

int isConvex(Polygon *P){
    float val;
    for(int i=0; i < P->_nb_vertices && val; i++){
        Vector v1 = V_unit(P->_vertices[i]);
        Vector v2 = V_unit(P->_vertices[i+1 % P->_nb_vertices]);
        Vector v3 = V_unit(P->_vertices[i+2 % P->_nb_vertices]);
        val = Det(v1, v2, v3);
        
    }
}

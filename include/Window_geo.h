#ifndef __WINDOW_GEO_H
#define __WINDOW_GEO_H

#include "Polygon.h"
#include "Mesh.h"

/** Initialise le contenu de la fenêtre.
 */
void window_geo_init(void);
/** Ajoute un vecteur au polygone.
 * \see Vector
 * \param v Un Vecteur.
 */
void window_geo_addPolyVertor (Vector v);

/** Extrude le polygone.
 */
void window_geo_extrudeMe (void);

/** Renvoie si le polygone est extrudé ou pas.
 * \return Vrai (true) si le polygone est extrudé et faux (false) sinon.
 */
int window_geo_isExtruded(void);

/** Affiche le polygone dans OpenGL.
 */
void window_geo_drawPoly(void);

/** Affiche le Mesh dans OpenGl.
 */
void window_geo_drawMesh(void);

#endif // ( __WINDOW_GEO_H )

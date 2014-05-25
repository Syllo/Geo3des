/**
 * \file Window_geo.h
 * \brief Fichier de contenu de fenêtre. (header)
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

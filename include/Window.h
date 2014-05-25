/**
 * \file Window.h
 * \brief Fichier de fenêtre utilisateur. (header)
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

#ifndef __WINDOW_H
#define __WINDOW_H

#include <stdlib.h>
#include "Vector.h"
#include "Polygon.h"
#include "Mesh.h"
#include "Window_geo.h"
#include <GL/glut.h>
#include <GL/glx.h>

/** Le pas de mouvement pour une translation.
 */
#define PAS_DE_TRANSLATION 0.5
/** Le pas de mouvement pour une rotation.
 */
#define PAS_DE_ROTATION 10
/** Le pas de mouvement pour une mise à l'échelle.
 */
#define PAS_DE_SCALE 0.1
/** QQCH2
 */
#define DIM2 0
/** QQCH3
 */
#define DIM3 1

/** Initialise la fenêtre.
 * \param argc Le nombre de string dans argv.
 * \param argv Un pointeur contenant des chaines de caractère.
 * \return Rien normalement.
 */
int InitWindow(int argc, char**argv);

#endif // ( __WINDOW_H )

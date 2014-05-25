/**
 * \brief Fichier de fonctions de bruit de Perlin. (header)
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

#ifndef _PERLIN_H_
#define _PERLIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Vector.h"

#define PRLN_000 0
#define PRLN_100 1
#define PRLN_010 2
#define PRLN_110 3
#define PRLN_001 4
#define PRLN_101 5
#define PRLN_011 6
#define PRLN_111 7


//double PRLN_scalarNoise(Vector p, double period, double amplitude, int nb_octaves, double lacunarity, double gain);
//Vector PRLN_vectorNoise(Vector p, double period, double amplitude, int nb_octaves, double lacunarity, double gain);
double PRLN_scalarNoise(Vector p);
Vector PRLN_vectorNoise(Vector p);

#endif


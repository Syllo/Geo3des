/**
 * \file Window.c
 * \brief Fichier de fenêtre utilisateur. (source)
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

#include "Window.h"

static int dim = DIM2;
static int width = 650;
static int height = 650;
static double x_translate = 0;
static double y_translate = 0;
static double horizon_rota = 0;
static double vertica_rota = 0;
static double scale = 1;

static GLfloat p_light[4];

static inline void haut(void){
    if(window_geo_isExtruded())
        y_translate += PAS_DE_TRANSLATION;
}

static inline void bas(void){
    if(window_geo_isExtruded())
        y_translate -= PAS_DE_TRANSLATION;
}

static inline void gauche(void){
    if(window_geo_isExtruded())
        x_translate -= PAS_DE_TRANSLATION;
}

static inline void droite(void){
    if(window_geo_isExtruded())
        x_translate += PAS_DE_TRANSLATION;
}

static inline void rotationDroite(void){
    if(window_geo_isExtruded())
        horizon_rota += PAS_DE_ROTATION;
}

static inline void rotationGauche(void){
    if(window_geo_isExtruded())
        horizon_rota -= PAS_DE_ROTATION;
}

static inline void rotationHaut(void){
    if(window_geo_isExtruded())
        vertica_rota += PAS_DE_ROTATION;
}

static inline void rotationBas(void){
    if(window_geo_isExtruded())
        vertica_rota -= PAS_DE_ROTATION;
}

static void zoom_in(void){
    if(window_geo_isExtruded())
        scale += PAS_DE_SCALE;
}

static void zoom_out(void){
    if(window_geo_isExtruded())
        scale -= PAS_DE_SCALE;
}

//static void initShade(){
//    GLfloat mat_diffuse[] = {1,1,1,1.0};
//    GLfloat mat_ambient[] = {0.1,0.1,0.1,0.0};
//
//    glClearColor (0.0, 0.0, 0.0, 0.0);
//    glShadeModel (GL_SMOOTH);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
//    glLightfv(GL_LIGHT0, GL_POSITION, p_light);
//
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_DEPTH_TEST);
//}

static void display(){
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(dim==DIM2)
        glOrtho(-1,1,-1,1,-1,1);
    else
        gluPerspective( 0, (float) width/height, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScaled(scale, scale, scale);
    glRotated(horizon_rota, 0, 1, 0);
    glRotated(vertica_rota, 1, 0, 0);
    glTranslated(x_translate, y_translate, 0.);

    if(window_geo_isExtruded())
        window_geo_drawMesh();
    else
        window_geo_drawPoly();

    glutSwapBuffers();
}

static void keyboard(unsigned char keycode, int x, int y){
    // printf("Touche frapee : %c (code ascii %d)\n",keycode, keycode);

    switch(keycode){
        case '2':
            rotationBas();
            break;
        case '4':
            rotationGauche();
            break;
        case '6':
            rotationDroite();
            break;
        case '8':
            rotationHaut();
            break;
        case 'e':
            window_geo_extrudeMe();
            break;
        case 27: // ECHAP
            exit(0);
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

static void special(int keycode, int x, int y){
    int mod = glutGetModifiers();
    switch(keycode)
    {
        case GLUT_KEY_UP:
            haut();
            break;
        case GLUT_KEY_DOWN:
            bas();
            break;
        case GLUT_KEY_LEFT:
            gauche();
            break;
        case GLUT_KEY_RIGHT:
            droite();
            break;
        case GLUT_KEY_PAGE_UP:
            zoom_in();
            break;
        case GLUT_KEY_PAGE_DOWN:
            zoom_out();
            break;
        default :
            fprintf(stderr,"function special : unknown keycode %d\n",keycode); break;
    }
    if(mod==GLUT_ACTIVE_CTRL)
        glLightfv(GL_LIGHT0, GL_POSITION, p_light);
}

static inline double mouseToDouble(int x, int xmax){
    return (double) x / xmax * 2. - 1.;
}

static inline double xMouseToRealX(int x){
    return mouseToDouble(x, width);
}

static inline double yMouseToRealY(int y){
    return - mouseToDouble(y, height);
}

static void mouse(int button, int state, int x, int y){
   // printf("Clic at %d %d \n",x,y);

    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN){
                double xr = xMouseToRealX(x);
                double yr = yMouseToRealY(y);
                Vector v = V_new(xr, yr, 0.);
                window_geo_addPolyVertor(v);
            }
            break;
        case 3:
            zoom_in();
            break;
        case 4:
            zoom_out();
            break;
        case GLUT_RIGHT_BUTTON:
            window_geo_extrudeMe();
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

static void idle(){
    glutPostRedisplay();
}

int InitWindow(int argc, char**argv){

    window_geo_init();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Geo3des");
    glViewport(0, 0, width, height);
    glClearColor(0,0,0,0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}

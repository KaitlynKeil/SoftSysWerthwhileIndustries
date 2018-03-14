/* Main running for our game
   Needs to have gcc game.c quadtree.c asteroids.c -lGL -lGLU -lglut -lm to run
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include "quadtree.h"

#define MAX_AST        20
#define WX             250
#define WY             250
#define true           1

float ast_size = 0.1f;

time_t cur_time, ltime;
double dt;

int loop, num_freed, num_asts = 5;
Asteroid *ast_field[MAX_AST];
Quad *q;


void draw_ast() {
  float x, y;

  for (loop = 0; loop < num_asts; loop++) {
    if (ast_field[loop]->alive == true) {
      x = ast_field[loop]->xpos;
      y = ast_field[loop]->ypos;

      // Draw particles
      glColor3f(1.0f, 1.0f, 1.0f); // white
      glBegin(GL_POLYGON);
        // Front
        glVertex2f(x-ast_size, y-ast_size); // lower left
        glVertex2f(x-(ast_size*0.5f), y); // left side
        glVertex2f(x-ast_size, y+ast_size); // upper left
        glVertex2f(x, y+(ast_size*0.5f)); // top side
        glVertex2f(x+ast_size, y+ast_size); // upper right
        glVertex2f(x+(ast_size*0.5f), y); // right side
        glVertex2f(x+ast_size, y-ast_size); // lower left
        glVertex2f(x, y-(ast_size*0.5f)); // bottom side
      glEnd();
    }
    else {
      ast_field[loop] = make_asteroid();
    }
  }
  num_freed = update_quad(q, ast_field, num_asts);
}

void init( ) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    q = make_quad(make_point(-300, 400), make_point(300,-400));

    // Initialize asteroids
    for (loop = 0; loop < num_asts; loop++) {
        ast_field[loop] = make_asteroid();
        insert_node(q, ast_to_node(ast_field[loop]));
    }

}

void drawScene( ) {
  // Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,
				0.0f, 0.0f,  0.0f,
				0.0f, 1.0f,  0.0f);
  
  glBegin(GL_QUADS);
    glVertex3f(-0.5f+globalX,-2.7f+globalY, 0.0f);
    glVertex3f(0.0f+globalX,-2.2f+globalY, 0.0f);
    glVertex3f(.5f+globalX, -2.7f+globalY, 0.0f);
    glVertex3f(0.0f+globalX,-2.45f+globalY, 0.0f);
  glEnd();

	draw_ast();

  updateLasers(*laserList);
	
  glutSwapBuffers();
}

void reshape(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void idle ( ) {
  glutPostRedisplay();
  cur_time = time(NULL);
  ltime = time(NULL);
}

void processSpecialKeys(int key, int x, int y) {

  switch(key) {
    case GLUT_KEY_LEFT :
        if((-.6f+globalX)<-4.1f){
        } else{
          globalX -= .1f;
        } break;
    case GLUT_KEY_RIGHT :
        if((.6f+globalX)>4.2f){
        } else{
          globalX += .1f;
        } break;
    case GLUT_KEY_UP :
        if((-2.1f+globalY)>4.1f){
        } else{
          globalY += .1f;
        } break;
    case GLUT_KEY_DOWN :
        if((-2.7f+globalY)<-4.1f){
        } else{
          globalY -= .1f;
        } break;
    case GLUT_KEY_INSERT:
        addLaser();
        break;
  }
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main (int argc, char** argv) {
  Laser* laser1 = (Laser*)malloc(sizeof(Laser));
  LaserNode* firstNode = (LaserNode*)malloc(sizeof(LaserNode));
  //Laser* laser1 = (Laser*)malloc(sizeof(Laser));
  laser1->xPos = 0.0f;
  laser1->yPos = 0.0f;
  laser1->xVel = 0.0f;
  laser1->yVel = 0.0f;
  //LaserNode* firstNode = (LaserNode*)malloc(sizeof(LaserNode));
  firstNode->val = laser1;
  firstNode->next = NULL;

  laserList = &firstNode;

  glutInit(&argc, argv);
  glutCreateWindow("CMPS 161 - Final Project");
  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(WX, WY);
  glutInitWindowPosition(50, 50);
  init();
  glutDisplayFunc(drawScene);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutSpecialFunc(processSpecialKeys);
  glutMainLoop();
  return 0;
}
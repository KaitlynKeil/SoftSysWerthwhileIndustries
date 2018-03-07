/* Main running for our game
   Needs to have gcc game.c asteroids.c -lGL -lGLU -lglut -lm to run
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "asteroids.h"

#define NUM_AST        5
#define WX             250
#define WY             250
#define true           1

float ast_size = 0.1f;

int loop;
Asteroid *ast_field[NUM_AST];


void draw_ast() {
  float x, y;

  for (loop = 0; loop < NUM_AST; loop++) {
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

      // Update values
      //Move
      int is_alive = update_asteroid(ast_field[loop]);
      if(is_alive != true) {
      	ast_field[loop] = make_asteroid();
      }
    }
  }
}

void init( ) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Initialize asteroids
    for (loop = 0; loop < NUM_AST; loop++) {
        ast_field[loop] = make_asteroid();
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
	draw_ast();
	
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
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main (int argc, char** argv) {
  glutInit(&argc, argv);
  glutCreateWindow("CMPS 161 - Final Project");
  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(WX, WY);
  glutInitWindowPosition(50, 50);
  init();
  glutDisplayFunc(drawScene);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
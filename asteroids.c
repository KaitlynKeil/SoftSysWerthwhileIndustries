// Makes asteroids that fall from the sky
// Kaitlyn is the lead

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#define NUM_AST        5
#define WX             250
#define WY             250
#define true           1


float x_bound = 3.0f;
float y_bound = 4.0f;

float min_yvel = -0.005f;
float max_yvel = -0.01f;
float min_xvel = -0.01f;
float max_xvel = 0.01f;
float ast_size = 0.1f;

int loop;

typedef struct {
	// Asteroid life
	int alive; // Is it still around?
	float life; // Health

	// color/apperance
	float red;
	float green;
	float blue;

	// position
	float xpos;
	float ypos;

	// velocity
	float xvel;
	float yvel;
} asteroid;

asteroid ast_field[NUM_AST];


float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

// Initialize/Reset Asteroids - give them their attributes
void initAsteroids(int i) {
    ast_field[i].alive = true;
    ast_field[i].life = 1.0f;

    ast_field[i].xpos = float_rand(-x_bound, x_bound);
    ast_field[i].ypos = y_bound;

    ast_field[i].red = 0.5f;
    ast_field[i].green = 0.5f;
    ast_field[i].blue = 1.0f;

    ast_field[i].yvel = float_rand(max_yvel, min_yvel);
    ast_field[i].xvel = float_rand(max_xvel, min_xvel);
}

void drawAst() {
  float x, y;

  for (loop = 0; loop < NUM_AST; loop++) {
    if (ast_field[loop].alive == true) {
      x = ast_field[loop].xpos;
      y = ast_field[loop].ypos;

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
      ast_field[loop].ypos += ast_field[loop].yvel;
      ast_field[loop].xpos += ast_field[loop].xvel;
      // Decay
      if(ast_field[loop].ypos < -y_bound) {ast_field[loop].life = 0.0f;}
      if(abs(ast_field[loop].xpos) > x_bound) {ast_field[loop].xvel *= -1.0f;}

      //Revive
      if (ast_field[loop].life <= 0.0f) {
        initAsteroids(loop);
      }
    }
  }
}

/* Initialize OpenGL Graphics */
void init( ) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Initialize particles
    for (loop = 0; loop < NUM_AST; loop++) {
        initAsteroids(loop);
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
	drawAst();
	
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
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>

float angle = 0.0f;
float globalX = 0.0f;
float globalY = 0.0f;

typedef struct Laser {
	float xPos, yPos, xVel, yVel;
} Laser;


typedef struct LaserNode{
	Laser* val;
	struct LaserNode* next;
} LaserNode;

LaserNode** laserList;

void addLaser(){
	LaserNode* current = *laserList;
	while(current->next != NULL){
		current = current->next;
	}
	Laser* addedLaser = (Laser*)malloc(sizeof(Laser));
	LaserNode* addedNode = (LaserNode*)malloc(sizeof(LaserNode));
	addedLaser->xPos = globalX;
	addedLaser->yPos = globalY;
	addedLaser->xVel = 0.0f;
	addedLaser->yVel = .01f;
	addedNode->val = addedLaser;
	addedNode->next = NULL;
	current->next = addedNode;
}

void updateLasers(LaserNode* updateNode){
	LaserNode* current = updateNode;
	if(current->next != NULL){
		float xPos = current->next->val->xPos;
		float yPos = current->next->val->yPos;
		float xVel = current->next->val->xVel;
		float yVel = current->next->val->yVel;
		if(((xPos<3.5f) && (xPos>-3.5f)) && ((yPos<3.6f) && (yPos>-3.6f))){
			printf("%s", (yPos<3.6f)&&(yPos>-3.6f) ? "true" : "false");
			glBegin(GL_QUADS);{
				glVertex3f(-.1f+xPos+xVel,0.0f+yPos+yVel,0.0f);
				glVertex3f(0.0f+xPos+xVel,.1f+yPos+yVel,0.0f);
				glVertex3f(.1f+xPos+xVel,0.0f+yPos+yVel,0.0f);
				glVertex3f(0.0f+xPos+xVel,-.1f+yPos+yVel,0.0f);
			}
			current->next->val->xPos = xPos+xVel;
			current->next->val->yPos = yPos+yVel;
		} else{
			printf("NOW\n");
			LaserNode* temp = current->next->next;
			printf("HERE\n");
			free(current->next);
			printf("NEXT\n");
			current->next = temp;
			printf("BEFORE\n");
		}
		if(current->next!=NULL){
			updateLasers(current->next);
		}
		printf("FINISHED\n");
	}
}

void printLasers(LaserNode* current){
	if(current!=NULL){
		printf("xPos:%f yPos:%f\n",current->val->xPos,current->val->yPos);
		printLasers(current->next);
	} else{
		printf("end\n");
	}
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

void changeSize(int w, int h) {

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

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 0.0f, 10.0f,
			0.0f, 0.0f,  0.0f,
			0.0f, 1.0f,  0.0f);

	glBegin(GL_QUADS);
		glVertex3f(-0.5f+globalX,-2.7f+globalY, 0.0f);
		glVertex3f(0.0f+globalX,-2.2f+globalY, 0.0f);
		glVertex3f(.5f+globalX, -2.7f+globalY, 0.0f);
		glVertex3f(0.0f+globalX,-2.45f+globalY, 0.0f);
	glEnd();

	updateLasers(*laserList);

	printLasers(*laserList);

	//printf("%f %f\n",-2.2f+globalY, .5f+globalX);
	//printf("%d %d\n",GLUT_SCREEN_WIDTH, GLUT_SCREEN_HEIGHT);
	glutSwapBuffers();
}

int main(int argc, char **argv) {

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
	
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;

}
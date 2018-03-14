#include <GL/glut.h>
#include <stdio.h>
#include "lasers.h"

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
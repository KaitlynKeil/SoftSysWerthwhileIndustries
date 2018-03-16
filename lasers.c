#include <GL/glut.h>
#include <stdio.h>
#include "lasers.h"

//instantiate score as well as the position of the sprite at zero
float globalX = 0.0f;
float globalY = 0.0f;
int score = 0;

//Adds a new laser to the linkedlist with a standard x and y velocity at the position of the 
//spaceship
void addLaser(){
	LaserNode* current = *laserList;
	//reaches the end of the linkedlist
	while(current->next != NULL){
		current = current->next;
	}
	//allocates space for the new laser in the heap
	Laser* addedLaser = (Laser*)malloc(sizeof(Laser));
	LaserNode* addedNode = (LaserNode*)malloc(sizeof(LaserNode));
	//instantiates the new laser and lasernode
	addedLaser->xPos = globalX;
	addedLaser->yPos = globalY-2.7f;
	addedLaser->xVel = 0.0f;
	addedLaser->yVel = .01f;
	addedLaser->life = 1;
	addedNode->val = addedLaser;
	addedNode->next = NULL;
	//adds the new laser to the laserlist
	current->next = addedNode;
}

//updateLasers increments the position of the lasers based on the velocity
//one at a time. Also, removes lasers from the linkedlist if they are off
//the screen or if the life is zero. If the next node is not null, updateLasers
//is called again
void updateLasers(LaserNode* updateNode){
	LaserNode* current = updateNode;
	if(current->next != NULL){
		//break out the x and y pos as well as the x and y velocity of the laser as 
		//well as the life
		float xPos = current->next->val->xPos;
		float yPos = current->next->val->yPos;
		float xVel = current->next->val->xVel;
		float yVel = current->next->val->yVel;
		int life = current->next->val->life;
		//checks if the laser is off the screen and if life is zero
		if(xPos<3.5f && xPos>-3.5f && yPos<3.6f && yPos>-3.6f && life){
			//draws the new laser at the new position
			glBegin(GL_QUADS);{
				glVertex3f(-.1f+xPos+xVel,0.0f+yPos+yVel,0.0f);
				glVertex3f(0.0f+xPos+xVel,.1f+yPos+yVel,0.0f);
				glVertex3f(.1f+xPos+xVel,0.0f+yPos+yVel,0.0f);
				glVertex3f(0.0f+xPos+xVel,-.1f+yPos+yVel,0.0f);
			}
			//updates the xPos and the yPos of the laser
			current->next->val->xPos = xPos+xVel;
			current->next->val->yPos = yPos+yVel;
		} else{
			//Removes the laser from the linkedlist if the laser is off the screen or if life is zero
			LaserNode* temp = current->next->next;
			free(current->next);
			current->next = temp;
		}
		//Call update for the next laser in the linkedlist if the next laser is not a NULL
		if(current->next!=NULL){
			updateLasers(current->next);
		}
	}
}

//Print out the x and y position of each of the lasers currently in the laser list.
//Takes the top level laser as input and prints end when done
void printLasers(LaserNode* current){
	if(current!=NULL){
		printf("xPos:%f yPos:%f\n",current->val->xPos,current->val->yPos);
		printLasers(current->next);
	} else{
		printf("end\n");
	}
}

//Checks for collisions between asteroids and the lasers
//sweeps through the list of laser nodes and checks for collisions with 
//the quadtree. If there is a collision, score is incremented and laser life goes to zero
void checkLaserAstCollisions(LaserNode* laserToLocate, Quad *q){
	if(laserToLocate != NULL){
		int res = check_collisions(q,convert_coords(laserToLocate->val->xPos,laserToLocate->val->yPos));
		if(res){
			laserToLocate->val->life = 0;
			score=score+1;
		}
		checkLaserAstCollisions(laserToLocate->next,q);
	}
}
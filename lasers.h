#include "quadtree.h"

extern float globalX;
extern float globalY;
int score;

typedef struct Laser {
	float xPos, yPos, xVel, yVel;
	int life;
} Laser;


typedef struct LaserNode{
	Laser* val;
	struct LaserNode* next;
} LaserNode;

LaserNode** laserList;

void addLaser();
void updateLasers(LaserNode* updateNode);
void printLasers(LaserNode* current);
Point* makePointFromLaser(LaserNode* laserToPoint);
void checkLaserAstCollisions(LaserNode* laserToLocate, Quad *q);
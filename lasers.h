LaserNode** laserList;

typedef struct Laser {
	float xPos, yPos, xVel, yVel;
} Laser;


typedef struct LaserNode{
	Laser* val;
	struct LaserNode* next;
} LaserNode;

void addLaser();
void updateLasers(LaserNode* updateNode);
void printLasers(LaserNode* current);
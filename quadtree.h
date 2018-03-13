#include "asteroids.h"

typedef struct sQuad
{
	// Hold details of the boundary of this node
	Point *topLeft;
	Point *botRight;

	Node *n;

	// Children
	struct sQuad *topLeftTree;
	struct sQuad *topRightTree;
	struct sQuad *botLeftTree;
	struct sQuad *botRightTree;

}Quad;

Quad *make_quad(Point *topL, Point *botR);
/* Frees the entire quadtree */
void free_quad(Quad *q);

/* Clears everything out of the quad tree to reset */
void clear_quad(Quad *q);
/* Checks to see if the point is inside the boundary
 of the given quadrant */
int in_boundary(Quad *q, Point *p);

/* Finds where it should insert the new nodes, makes subtrees if it must */
void insert_node(Quad *q, Node *node);

/* searches the quadtree for that point */
Node *search(Quad *q, Point *p);

/* Clears the quadtree, then updates and inserts the
 asteroids. Returns the number of asteroids that went
 off-screen. */
int update_quad(Quad *q, Asteroid **asts, int num_asts);

void print_quad(Quad *q);

void print_occupied(Quad *q);

/* Checks if there are any collisions at a point */
int check_collisions(Quad *q, Point *p);
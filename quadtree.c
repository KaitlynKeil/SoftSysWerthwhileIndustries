#include <stdio.h>
#include <stdlib.h>

float x_bound = 3.0f;
float y_bound = 4.0f;

float min_yvel = -0.005f;
float max_yvel = -0.01f;
float min_xvel = -0.01f;
float max_xvel = 0.01f;
float ast_size = 0.1f;


float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

typedef struct {
	int x;
	int y;
} Point;

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

typedef struct 
{
	Point *pos;
	asteroid *ast;
} Node;

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

void initAsteroids(int i, asteroid *ast_field) {
    ast_field[i].alive = 1;
    ast_field[i].life = 1.0f;

    ast_field[i].xpos = float_rand(-x_bound, x_bound);
    ast_field[i].ypos = y_bound;

    ast_field[i].red = 0.5f;
    ast_field[i].green = 0.5f;
    ast_field[i].blue = 1.0f;

    ast_field[i].yvel = float_rand(max_yvel, min_yvel);
    ast_field[i].xvel = float_rand(max_xvel, min_xvel);
}

Point *make_point(int x, int y) {
	Point *new = malloc(sizeof(Point));
    new->x = x;
    new->y = y;
    return new;
}

Node *make_node(Point *center, asteroid *ob) {
	Node *new = malloc(sizeof(Node));
	new->pos = make_point(center->x, center->y);
	new->ast = ob;
	return new;
}

Quad *make_quad(Point *topL, Point *botR) {
	Quad *new = malloc(sizeof(Quad));
	new->n = NULL;
	new->topLeftTree = NULL;
	new->topRightTree = NULL;
	new->botLeftTree = NULL;
	new->botRightTree = NULL;
	new->topLeft = make_point(topL->x, topL->y);
	new->botRight = make_point(botR->x, botR->y);
	return new;
}

void insert_node(Quad *q, Node *node) {
	if(node == NULL) {return;}

	// Current quad can't contain it
	if(!in_boundary(q, node->pos)) {return;}

	// Indicates unit area, cannot subdivide further
	if(abs(q->topLeft->x - q->botRight->x) <= 1 &&
		abs(q->topLeft->y - q->botRight->y) <= 1)
	{
		if(q->n == NULL) {
			q->n = node;
		}
		return;
	}

	if ((q->topLeft->x + q->botRight->x) / 2 >= node->pos->x) {
		// Indicates topLeftTree
		if ((q->topLeft->y + q->botRight->y) / 2 >= node->pos->y) {
			if(q->topLeftTree == NULL) {
				q->topLeftTree = make_quad(
					make_point(q->topLeft->x, q->topLeft->y),
					make_point((q->topLeft->x + q->botRight->x) / 2,
							(q->topLeft->y + q->botRight->y) / 2));
			}
			insert_node(q->topLeftTree, node);
		}
		// Indicates botLeftTree
		else {
			if(q->botLeftTree == NULL) {
				q->botLeftTree = make_quad(
					make_point(q->topLeft->x,
						(q->topLeft->y + q->botRight->y)/2),
					make_point((q->topLeft->x + q->botRight->x)/2,
						(q->botRight->y)));
			}
			insert_node(q->botLeftTree, node);
		}
	}
	else {
		// Indicates topRightTree
		if ((q->topLeft->y + q->botRight->y) / 2 >= node->pos->y)
        {
            if (q->topRightTree == NULL){
                q->topRightTree = make_quad(
                    make_point((q->topLeft->x + q->botRight->x) / 2,
                        q->topLeft->y),
                    make_point(q->botRight->x,
                        (q->topLeft->y + q->botRight->y) / 2));
            }
            insert_node(q->topRightTree, node);
        }
 
        // Indicates botRightTree
        else
        {
            if (q->botRightTree == NULL){
                q->botRightTree = make_quad(
                    make_point((q->topLeft->x + q->botRight->x) / 2,
                        (q->topLeft->y + q->botRight->y) / 2),
                    make_point(q->botRight->x, q->botRight->y));
            }
            insert_node(q->botRightTree, node);
        }
	}
}

Node *search(Quad *q, Point *p) {
	// Current quad cannot contain it
	if (!in_boundary(q, p)) {return NULL;}

	// Cannot subdivide further
	if(q->n != NULL) {return q->n;}

	if ((q->topLeft->x + q->botRight->x) / 2 >= p->x)
    {
        // Indicates topLeftTree
        if ((q->topLeft->y + q->botRight->y) / 2 >= p->y)
        {
            if (q->topLeftTree == NULL)
                return NULL;
            return search(q->topLeftTree,p);
        }
 
        // Indicates botLeftTree
        else
        {
            if (q->botLeftTree == NULL)
                return NULL;
            return search(q->botLeftTree, p);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((q->topLeft->y + q->botRight->y) / 2 >= p->y)
        {
            if (q->topRightTree == NULL)
                return NULL;
            return search(q->topRightTree, p);
        }
 
        // Indicates botRightTree
        else
        {
            if (q->botRightTree == NULL)
                return NULL;
            return search(q->botRightTree, p);
        }
    }
}

int in_boundary(Quad *q, Point *p) {
	return(p->x >= q->topLeft->x &&
		p->x <= q->botRight->x &&
		p->y >= q->topLeft->y &&
		p->y <= q->botRight->y);
}

int main() {
	asteroid ast[3];
	int i;
	for(i=0;i<3;i++) {
		initAsteroids(i, ast);
	}
	// TODO: convert float x/y from asteroids to int coords
	Quad *center = make_quad(make_point(0, 0), make_point(8,8));
	Node *a = make_node(make_point(1,1), &ast[0]);
	Node *b = make_node(make_point(2,5), &ast[1]);
	Node *c = make_node(make_point(7,6), &ast[2]);
	
	insert_node(center, a);
	insert_node(center, b);
	insert_node(center, c);
	printf("%f\n", search(center, make_point(1,1))->ast->xpos);
	printf("%f\n", search(center, make_point(2,5))->ast->xpos);
	printf("%f\n", search(center, make_point(7,6))->ast->xpos);
	printf("%f\n", search(center, make_point(4,4))->ast->xpos);
}
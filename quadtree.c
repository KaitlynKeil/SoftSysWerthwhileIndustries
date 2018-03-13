#include <stdio.h>
#include <stdlib.h>
#include "quadtree.h"

// float x_bound = 3.0f;
// float y_bound = 4.0f;

// float min_yvel = -0.005f;
// float max_yvel = -0.01f;
// float min_xvel = -0.01f;
// float max_xvel = 0.01f;
// float ast_size = 0.1f;

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

/* Frees the entire quadtree */
void free_quad(Quad *q) {
	if(q!=NULL){
		free_quad(q->topLeftTree);
		free_quad(q->topRightTree);
		free_quad(q->botLeftTree);
		free_quad(q->botRightTree);
	}
	free(q);
}

/* Clears everything out of the quad tree to reset */
void clear_quad(Quad *q) {
	if(q == NULL) return;

	q->n = NULL;
	clear_quad(q->topLeftTree);
	q->topLeftTree = NULL;
	clear_quad(q->topRightTree);
	q->topRightTree = NULL;
	clear_quad(q->botLeftTree);
	q->botLeftTree = NULL;
	clear_quad(q->botRightTree);
	q->botRightTree = NULL;
}

/* Checks to see if the point is inside the boundary
 of the given quadrant */
int in_boundary(Quad *q, Point *p) {
	return(p->x >= q->topLeft->x &&
		p->x <= q->botRight->x &&
		p->y <= q->topLeft->y &&
		p->y >= q->botRight->y);
}

/* Finds where it should insert the new nodes, makes subtrees if it must */
void insert_node(Quad *q, Node *node) {
	if(node == NULL) {
		return;
	}

	// Current quad can't contain it
	if(!in_boundary(q, node->pos)) {
		// puts("Node out of bounds");
		return;
	}

	// Indicates unit area, cannot subdivide further
	if(abs(q->topLeft->x - q->botRight->x) <= 10 &&
		abs(q->topLeft->y - q->botRight->y) <= 10)
	{
		if(q->n == NULL) {
			// printf("\nInserting ");
			// print_point(node->pos);
			// printf("\n");
			q->n = node;
		}
		return;
	}

	if ((q->topLeft->x + q->botRight->x) / 2 >= node->pos->x) {
		// Indicates topLeftTree
		if ((q->topLeft->y + q->botRight->y) / 2 <= node->pos->y) {
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
		if ((q->topLeft->y + q->botRight->y) / 2 <= node->pos->y)
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

/* searches the quadtree for that point */
Node *search(Quad *q, Point *p) {
	if(q == NULL) {return NULL;}
	// Current quad cannot contain it
	if (!in_boundary(q, p)) {return NULL;}

	// Cannot subdivide further
	if(q->n != NULL) {return q->n;}

	if ((q->topLeft->x + q->botRight->x) / 2 >= p->x)
    {
        // Indicates topLeftTree
        if ((q->topLeft->y + q->botRight->y) / 2 <= p->y)
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
        if ((q->topLeft->y + q->botRight->y) / 2 <= p->y)
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

/* Clears the quadtree, then updates and inserts the
 asteroids. Returns the number of asteroids that went
 off-screen. */
int update_quad(Quad *q, Asteroid **asts, int num_asts) {
	clear_quad(q);
	int i, num_freed = 0;
	for(i = 0; i<num_asts; i++){
		int on_screen = update_asteroid(asts[i]);
		if(on_screen){
		    insert_node(q, ast_to_node(asts[i]));
	    }
	    else {
	    	num_freed++;
	    }
	}
	return num_freed;
}

void print_quad(Quad *q) {
	if(q == NULL) {return;}
	printf("Quad");
	print_node(q->n);
	printf(" spans ");
	print_point(q->topLeft);
	printf(" to ");
	print_point(q->botRight);
	printf(" {\n\t top left:   ");
	print_quad(q->topLeftTree);
	printf("\n\t top right:    ");
	print_quad(q->topRightTree);
	printf("\n\t bottom left:  ");
	print_quad(q->botLeftTree);
	printf("\n\t bottom right: ");
	print_quad(q->botRightTree);
	printf("\n}\n");
}

void print_occupied(Quad *q) {
	if(q != NULL) {
		if(q->n != NULL){
			printf("\nQuad");
			print_node(q->n);
			printf(" spans ");
			print_point(q->topLeft);
			printf(" to ");
			print_point(q->botRight);
			printf("\n");
	    }
		print_occupied(q->topLeftTree);
		print_occupied(q->topRightTree);
		print_occupied(q->botLeftTree);
		print_occupied(q->botRightTree);
    }
}
/* Checks if there are any collisions at a point */
int check_collisions(Quad *q, Point *p) {
	Node *ast = search(q, p);
	if(ast!=NULL){
		return ast_collision(ast->ast, p);
	}
	return 0;
}

// int main() {
// 	Asteroid *ast[3];
// 	int i;
// 	for(i=0;i<3;i++) {
// 		ast[i] = make_asteroid();
// 		// print_ast(ast[i]);
// 	}
// 	// TODO: convert float x/y from asteroids to int coords
// 	Quad *center = make_quad(make_point(-300, 400), make_point(300,-400));
// 	Node *a = make_node(convert_coords(ast[0]), ast[0]);
// 	Node *b = make_node(convert_coords(ast[1]), ast[1]);
// 	Node *c = make_node(convert_coords(ast[2]), ast[2]);
	
// 	insert_node(center, a);
// 	insert_node(center, b);
// 	insert_node(center, c);

// 	print_occupied(center);

// 	// print_quad(center);

//     printf("\n");
// 	print_node(search(center, convert_coords(ast[0])));
// 	printf("\n");
// 	if(check_collisions(center, convert_coords(ast[0]))) {
// 		puts("Got collision!");
// 	}

// 	update_quad(center, ast, 3);
// 	puts("Quad updated");
// 	// printf("%d\n", check_collisions(center, convert_coords(ast[0])));
// 	print_occupied(center);
// }
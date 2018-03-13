// Makes asteroids that fall from the sky
// Kaitlyn is the lead

// Needs to have gcc asteroids.c -lGL -lGLU -lglut -lm to run

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include "asteroids.h"

#define NUM_AST        5
#define WX             250
#define WY             250
#define true           1

float x_bound = 3.0f;
float y_bound = 4.0f;

float min_yvel = -0.0005f;
float max_yvel = -0.002f;
float min_xvel = -0.001f;
float max_xvel = 0.001f;
int ast_radius = 5;

// Conversion variables for coordinates
int SCALE = 100; //, SHIFTX = 300, SHIFTY = 400;

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

Asteroid *make_asteroid() {
  Asteroid *new = malloc(sizeof(Asteroid));
  new->alive = true;
  new->life = 1.0f;
  new->xpos = float_rand(-x_bound, x_bound);
  new->ypos = y_bound;

  new->yvel = float_rand(max_yvel, min_yvel);
  new->xvel = float_rand(max_xvel, min_xvel);
  return new;
}

void free_asteroid(Asteroid *ast) {
  free(ast);
}

Point *make_point(int x, int y) {
  Point *new = malloc(sizeof(Point));
    new->x = x;
    new->y = y;
    return new;
}

void print_point(Point *p) {
  if(p==NULL) {return;}
  printf("(%d, %d)", p->x, p->y);
}

void print_ast(Asteroid *a) {
  if(a==NULL) {return;}
  printf("Asteroid at ");
  print_point(convert_coords(a));
  // printf("\n");
}

Node *make_node(Point *center, Asteroid *ob) {
  Node *new = malloc(sizeof(Node));
  new->pos = make_point(center->x, center->y);
  new->ast = ob;
  return new;
}

void print_node(Node *n) {
  if(n==NULL) {return;}
  printf("Node contains ");
  print_ast(n->ast);
}

int update_asteroid(Asteroid *ast) {
  if(ast != NULL){
    ast->ypos += (ast->yvel);
    ast->xpos += (ast->xvel);
    if(abs(ast->xpos) > x_bound) {ast->xvel *= -1.0f;}
    if (ast->ypos < -y_bound || ast->life <= 0.0f) {
      free_asteroid(ast);
      return 0;
    }
  }
    return 1;
}

/* Given an Asteroid, converts the floating point coordinates
to cartesian integer point */
Point *convert_coords(Asteroid *ast) {
  // return make_point((ast->xpos * SCALE)+SHIFTX, (ast->ypos * SCALE)+SHIFTY);
  return make_point((ast->xpos * SCALE), (ast->ypos * SCALE));
}

/* Makes the asteroids into nodes */
Node *ast_to_node(Asteroid *ast) {
  return make_node(convert_coords(ast), ast);
}

/* Checks to see if the point is inside the asteroid's radius. */
int ast_collision(Asteroid *ast, Point *p) {
  Point *a = convert_coords(ast);
  int x = p->x, ax = a->x;
  int y = p->y, ay = a->y;
  int res = (x >= ax-ast_radius &&
    x <= ax+ast_radius &&
    y >= ay-ast_radius &&
    y <= ay+ast_radius);
  ast->life = 0.0f;
  return res;
}
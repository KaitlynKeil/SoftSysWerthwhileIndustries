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

float min_yvel = -0.005f;
float max_yvel = -0.01f;
float min_xvel = -0.01f;
float max_xvel = 0.01f;

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

int update_asteroid(Asteroid *ast) {
  ast->ypos += ast->yvel;
  ast->xpos += ast->xvel;

  if(abs(ast->xpos) > x_bound) {ast->xvel *= -1.0f;}
  if (ast->ypos < -y_bound) {
    free_asteroid(ast);
    return 0;
  }
  return 1;
}
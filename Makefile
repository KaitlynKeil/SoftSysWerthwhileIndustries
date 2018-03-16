asteroids: asteroids.h quadtree.h lasers.h asteroids.c
	gcc -o asteroids.o asteroids.c -lGL -lGLU -lglut -lm

quadtree: quadtree.h asteroids.h lasers.h quadtree.c
	gcc -o quadtree.o quadtree.c asteroids.c -lGL -lGLU -lglut -lm

lasers: lasers.h quadtree.h asteroids.h lasers.c
	gcc -o lasers.o lasers.c quadtree.c asteroids.c -lGL -lGLU -lglut -lm

game: lasers.h quadtree.h asteroids.h game.c
	gcc -o game.o game.c lasers.c quadtree.c asteroids.c -lGL -lGLU -lglut -lm

all: asteroids.o quadtree.o lasers.o game.o
	gcc -o game asteroids.o quadtree.o lasers.o game.o -lGL -lGLU -lglut -lm
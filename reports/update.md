# Re-making Asteroids in C

## Bryan Werth and Kaitlyn Keil

### Shooting for the Stars... or at least, the asteroids

For Project 1, we are building a flash game that will involve shooting and destroying asteroids that fall from the top of the screen via a user-controlled space craft icon. As a lower bound, we will have a projectile, the asteroid, moving with a simple, randomly assigned velocity and trajectory on the screen along with a movable game token, the spaceship, that can shoot at the asteroid to destroy it. If the asteroid touches the spaceship, there is a notification of game over. Stretch goals are going to involve building out game functionality to include a variety of asteroids of varying sizes and more than one life for the player.

This project is meant to help us improve our C programming, both through learning new techniques (such as how to use OpenGL through Glut) and by refining old skills (like object oriented programming). The relatively simple concept has many places where it can be optimized, where making a poor decision could severely limit gameplay; collision detection for a large number of moving objects, for example. By making informed choices on how to handle such obstacles, we will improve ourselves as programmers and researchers.

### The Engines are shot, Captain!

Actually, the engines are running along fairly well. Currently, we have a player-controllable space craft and asteroids that bounce off the edge of the screen. However, these are not integrated onto one screen as of yet, but rather run in their own, separate spaces. We haven't done as much integration early on as we expected to, and have segmented the project fairly thoroughly into 'space craft' and 'asteroids'. This is letting us work in parallel, but could make final integration difficult.

We were able to find a number of resources for Glut, which we chose to use based on previous Software System projects. These tutorials and pieces of advice have let us progress pretty well in the space of graphics, though we are, if anything, under-utalizing Glut. We've also been able to find resources for things such as quadtrees, which we are examining for collision detection.

### Current State

At the moment, we are working in two main areas. On the space craft side, Bryan is working on being able to fire projectiles. Kaitlyn is currently exploring collision detection with quadtrees, which will allow for the main intersection of the two pieces. However, we are currently unsure if quadtrees are the best choice, as the asteroids are also in motion, and will continue to do research from here out. The space craft will be done when it can fire and be affected by asteroids. Collision detection will be done when it can loop through all the shots and apply them to whatever asteroids need to be affected, or determine that the space craft has been hit. The final task, which both team members are working on, is making all of the pieces modular and integratable.
# Project 1 Proposal

## Bryan Werth and Kaitlyn Keil

For Project 1, we are building a flash game that will involve shooting and destroying asteroids with a game token of some sort. As a lower bound we want to have a projectile, the asteroid, moving with a simple trajectory on the screen along with a movable game token, the spaceship, that can shoot at the asteroid to destroy it. If the asteroid touches the spaceship, there is a notification of game over. Stretch goals are going to involve building out game functionality to include a variety of asteroids of varying sizes and more than one life for the player.

We intend to use this project to get better at programming in C. Our hope is that this will give us more experience with C in a different context than most of the homeworks have presented it, as well as give us an idea of what it’s like to develop a larger scale project.

As this is a fairly well-documented style of project, we have the resources we need to get started. We have a good idea of what we want to accomplish and how we’ll do it, and if we need to find supportive resources or answer questions, there are plenty of online sources.

We're planning to do the majority of this project by pair programming, though we both understand there might be times that neither of us can make that work. We intend to start by using the graphics.h interface as a jumping off point for our game. We want to first program a spaceship that moves at the command of a user within the bounds of the screen. This will be considered done when we have a spaceship that moves only within the provided screen. Once we have this done, we want to allow the user to shoot lasers from the spaceship. This will be considered done when lasers appear from the spaceship at the press of the spacebar and disappear out of the view of the screen after traveling directly away from the spaceship. After, we want to integrate the asteroid into the game, starting with one asteroid that generates at the beginning of program run and integrating asteroid generation as an extension. Asteroid generation at program runtime will be completed when there is an asteroid that moves with a trajectory within the bounds of the screen and disappears if it comes into contact with a laser.
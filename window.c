// #include <ctime.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MOVE_SPEED 25

int main(int argc, char** argv){
    //Seeding the random generator
    // srand(time(NULL));

    // Init glut
    glutInit(&argc, argv);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(1200, 1200);
    glutInitDisplayMode (GLUT_RGB);
    glutCreateWindow("Pipe Screensaver");

    // initGL();
    glutMainLoop();
//     printf("test\n");
// const char* s = getenv("PATH");
// printf("PATH :%s\n",(s!=NULL)? s : "getenv returned NULL");
// printf("end test\n");
}
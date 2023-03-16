/*****************************************************************//**
 * \file   main.cpp
 * \brief  My solution for exersice ('Maman') 11 in Computer Graphics (20562) course
 * 
 * *** BUILD INSTRUCTIONS (VS2022, Windows 11) ***
 * 1. Setup OpenGL: https://www.geeksforgeeks.org/how-to-setup-opengl-with-visual-studio-2019-on-windows-10/.
 * 2. Select x86 Debug configuration.
 * 3. Build the solution (ctrl + shift + B).
 * 
 * \author aaron
 * \date   March 2023
 *********************************************************************/

/* OpenGL */
#include <Windows.h>
#include <GL/glut.h>

/* STL */
#include <iostream>
#include <math.h>

/* Window constants */
#define WINDOW_X_OFFSET 100
#define WINDOW_Y_OFFSET 100
#define WINDOW_HEIGHT   500
#define WINDOW_WIDTH    500
#define WINDOW_TITLE    "CG Maman 11"
#define X_COORD_RNG     100.0
#define Y_COORD_RNG     100.0


/**
 * Creates and initializes GLUT display-window.
 * 
 * \param argc Argument count.
 * \param argv Argument vector.
 */
void createWindow(int argc, char** argv)
{
    /* Create the window */
    glutInit(&argc, argv);                        // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
    glutInitWindowPosition(WINDOW_X_OFFSET, WINDOW_Y_OFFSET);  // Set top-left window position
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);           // Set window width and height
    glutCreateWindow(WINDOW_TITLE);  // Create window

    /* Initialize the window */
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // Set window color to white
    glMatrixMode(GL_PROJECTION);           // Set projection parameters
    gluOrtho2D(0.0, X_COORD_RNG, 0.0, Y_COORD_RNG);
}


/* Callback functions */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

/**
 * Assigns callback functions for events.
 * 
 */
void registerCallbacks(void)
{
    glutDisplayFunc(display);
}

/**
 * Main function.
 * 
 * \param argc Argument count.
 * \param argv Argument vector.
 * \return 
 */
int main(int argc, char** argv)
{
    createWindow(argc, argv);  // Create the display-window
    registerCallbacks();       // Assign callback functions for events
    glutMainLoop();            // Display everything and wait
}

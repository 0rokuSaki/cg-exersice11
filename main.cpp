/*****************************************************************//**
 * \file   main.cpp
 * \brief  My solution for exersice ('Maman') 11 in Computer Graphics (20562) course
 * 
 * This program creates an ugly logo for the Open University of Israel.
 * 
 * *** BUILD INSTRUCTIONS (VS2022, Windows 11) ***
 * 1. Setup OpenGL: https://www.geeksforgeeks.org/how-to-setup-opengl-with-visual-studio-2019-on-windows-10/.
 * 2. Select x86 Debug configuration.
 * 3. Build the solution (ctrl + shift + B).
 * 
 * \author aaron
 * \date   March 2023
 *********************************************************************/

/* Include cmath constants */
#define _USE_MATH_DEFINES

/* OpenGL */
#include <Windows.h>
#include <GL/glut.h>

/* STL */
#include <iostream>
#include <string>
#include <cmath>


/* Window constants */
#define WINDOW_X_OFFSET   100u         // Initial window left-offset
#define WINDOW_Y_OFFSET   100u         // Initial window top-offset
#define WINDOW_HEIGHT     500u         // Initial window height
#define WINDOW_WIDTH      500u         // Initial window width
#define WINDOW_MIN_HEIGHT 375u         // Minimal window height
#define WINDOW_MIN_WIDTH  350u         // Minimal window width
#define WINDOW_TITLE    "CG Maman 11"  // Window title

/* Exit button constants */
#define EXIT_BTN_WIDTH       85u     // Exit button  width (pixel)
#define EXIT_BTN_HEIGHT      50u     // Exit button height (pixel
#define EXIT_BTN_TEXT_POS_X  14.0f   // Exit button text x coord
#define EXIT_BTN_TEXT_POS_Y  15.0f   // Exit button text y coord
#define EXIT_BTN_TEXT        "EXIT"  // Exit button text
#define EXIT_BTN_FRAME_WIDTH 3.0f    // Exit button frame width

/* Title constants */
#define TITLE_HEIGHT       75u                     // Title height
#define TITLE_WIDTH        175u                    // Title width
#define TITLE_TEXT_POS_X   5.0f                    // Title text x coord
#define TITLE_TEXT_POS_Y   50.0f                   // Title text y coord
#define TITLE_AUTHOR_POS_X 5.0f                    // Title author x coord
#define TITLE_AUTHOR_POS_Y 25.0f                   // Title author y coord
#define TITLE_TEXT         "CG - Maman 11"         // Title text
#define TITLE_AUTHOR       "Author: Aaron Barkan"  // Title author name
#define TITLE_FRAME_WIDTH  3.0f                    // Title frame width

/* Logo constants */
#define LOGO_WIDTH        280u
#define LOGO_HEIGHT       200u
#define LOGO_MIN_COORD   -5.0f
#define LOGO_MAX_COORD    5.0f
#define LOGO_FRAME_WIDTH  5.0f
#define LOGO_LINE1_X     -4.0f
#define LOGO_LINE2_X      4.0f
#define LOGO_LINE_Y1     -3.0f
#define LOGO_LINE_Y2      3.0f
#define LOGO_LOOP_STEP    0.1f
#define LOGO_SIN_OFFSET   3.6f
#define LOGO_COS_OFFSET  -3.6f
#define LOGO_TEXT1        "The Open University"
#define LOGO_TEXT2        "of Israel"
#define LOGO_TEXT_POS_X1  -3.75f
#define LOGO_TEXT_POS_Y1   0.75f
#define LOGO_TEXT_POS_X2  -1.5f
#define LOGO_TEXT_POS_Y2  -1.25f


/* HELPER FUNCTIONS */

/* Creates and initializes GLUT display-window */
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
}


/* Create a frame */
void createFrame(const int width, const int height, const int frameWidth)
{
    glLineWidth(frameWidth);
    const float offset = frameWidth / 2.0;  // To see frame correctly
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f + offset, 0.0f + offset);
        glVertex2f(width - offset, 0.0f + offset);
        glVertex2f(width - offset, height - offset);
        glVertex2f(0.0f + offset, height - offset);
    glEnd();
}


/* Displays an exit button at the bottom left of the window */
void displayExitButton(void)
{
    /* Create viewport for exit button */
    glViewport(0, 0, EXIT_BTN_WIDTH, EXIT_BTN_HEIGHT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, EXIT_BTN_WIDTH, 0.0, EXIT_BTN_HEIGHT);

    /* Create red rectangle at the bottom left */
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(0.0f, 0.0f, EXIT_BTN_WIDTH, EXIT_BTN_HEIGHT);

    /* Create black frame */
    glColor3f(0.0f, 0.0f, 0.0f);
    createFrame(EXIT_BTN_WIDTH, EXIT_BTN_HEIGHT, EXIT_BTN_FRAME_WIDTH);

    /* Add text to button */
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(EXIT_BTN_TEXT_POS_X, EXIT_BTN_TEXT_POS_Y);
    for (const char c : EXIT_BTN_TEXT)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}


/* Display title and author name at the top right of the window */
void displayTitle(void)
{
    /* Create viewport for title */
    const int viewportX = glutGet(GLUT_WINDOW_WIDTH) - TITLE_WIDTH;
    const int viewportY = glutGet(GLUT_WINDOW_HEIGHT) - TITLE_HEIGHT;
    glViewport(viewportX, viewportY, TITLE_WIDTH, TITLE_HEIGHT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, TITLE_WIDTH, 0.0, TITLE_HEIGHT);

    /* Create a black frame */
    glColor3f(0.0f, 0.0f, 0.0f);
    createFrame(TITLE_WIDTH, TITLE_HEIGHT, TITLE_FRAME_WIDTH);

    /* Create title text */
    glRasterPos2f(TITLE_TEXT_POS_X, TITLE_TEXT_POS_Y);
    for (const char c : TITLE_TEXT)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    /* Create title author */
    glRasterPos2f(TITLE_AUTHOR_POS_X, TITLE_AUTHOR_POS_Y);
    for (const char c : TITLE_AUTHOR)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}


/* Display logo at the center of the window */
void displayLogo(void)
{
    /* Get window dimensions */
    const int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    const int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    
    /* Create a viewport at the center of the window */
    glViewport(windowWidth / 4, windowHeight / 4, LOGO_WIDTH, LOGO_HEIGHT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(LOGO_MIN_COORD, LOGO_MAX_COORD, LOGO_MIN_COORD, LOGO_MAX_COORD);

    /* Draw a blue logo of OpenU */
    glColor3f(0.0f, 0.8f, 1.0f);
    glLineWidth(LOGO_FRAME_WIDTH);
    glBegin(GL_LINES);
        glVertex2f(LOGO_LINE1_X, LOGO_LINE_Y1);
        glVertex2f(LOGO_LINE1_X, LOGO_LINE_Y2);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(LOGO_LINE2_X, LOGO_LINE_Y1);
        glVertex2f(LOGO_LINE2_X, LOGO_LINE_Y2);
    glEnd();

    float x, y;
    glBegin(GL_LINE_STRIP);
    for (x = LOGO_MIN_COORD + 1; x <= LOGO_MAX_COORD - 1; x += LOGO_LOOP_STEP)
    {
        y = sin(x + M_PI_2) + LOGO_SIN_OFFSET;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (x = LOGO_MIN_COORD + 1; x <= LOGO_MAX_COORD - 1; x += LOGO_LOOP_STEP)
    {
        y = -cos(x) + LOGO_COS_OFFSET;
        glVertex2f(x, y);
    }
    glEnd();

    /* Create text for logo */
    glRasterPos2f(LOGO_TEXT_POS_X1, LOGO_TEXT_POS_Y1);
    for (const char c : LOGO_TEXT1)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glRasterPos2f(LOGO_TEXT_POS_X2, LOGO_TEXT_POS_Y2);
    for (const char c : LOGO_TEXT2)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}


/* CALLBACK FUNCTIONS */

/* Callback for 'glutDisplayFunc' */
void displayCallback(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    displayExitButton();
    displayTitle();
    displayLogo();

    glFlush();
}


/* Callback for 'glutReshapeFunc' */
void reshapeCallback(int width, int height)
{
    if (width < WINDOW_MIN_WIDTH && height < WINDOW_MIN_HEIGHT)
    {
        glutReshapeWindow(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
    }
    else if (width < WINDOW_MIN_WIDTH && height >= WINDOW_MIN_HEIGHT)
    {
        glutReshapeWindow(WINDOW_MIN_WIDTH, height);
    }
    else if (width >= WINDOW_MIN_WIDTH && height < WINDOW_MIN_HEIGHT)
    {
        glutReshapeWindow(width, WINDOW_MIN_HEIGHT);
    }
}


/* Callback for 'glutMouseFunc' */
void mouseCallback(int button, int state, int x, int y)
{
    /* Exit program if right click on exit button */
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
        x < EXIT_BTN_WIDTH && y >= glutGet(GLUT_WINDOW_HEIGHT) - EXIT_BTN_HEIGHT)
    {
        exit(0);
    }
}


/* Assigns callback functions for events */
void registerCallbacks(void)
{
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutMouseFunc(mouseCallback);
}


/* Main function */
int main(int argc, char** argv)
{
    createWindow(argc, argv);  // Create the display-window
    registerCallbacks();       // Assign callback functions for events
    glutMainLoop();            // Display everything and wait
}

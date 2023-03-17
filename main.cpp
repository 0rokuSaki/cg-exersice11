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
#include <string>
#include <math.h>

/* General constants */
#define FONT_SWITCH_WIDTH  500  // Window  width at which font changes size
#define FONT_SWITCH_HEIGHT 300  // Window height at which font changes size

/* Window constants */
#define WINDOW_X_OFFSET 100            // Initial window left-offset
#define WINDOW_Y_OFFSET 100            // Initial window top-offset
#define WINDOW_HEIGHT   500            // Initial window height
#define WINDOW_WIDTH    500            // Initial window width
#define WINDOW_TITLE    "CG Maman 11"  // Window title
#define X_COORD_RNG     100.0f         // Max value for x coord
#define Y_COORD_RNG     100.0f         // Max value for y coord

/* Exit button constants */
#define EXIT_BTN_HEIGHT            10.0f   // Exit button height
#define EXIT_BTN_WIDTH             20.0f   // Exit button width
#define EXIT_BTN_TEXT_RASTER_POS_X 3.0f    // Exit button text x coord
#define EXIT_BTN_TEXT_RASTER_POS_Y 3.0f    // Exit button text y coord
#define EXIT_BTN_TEXT              "EXIT"  // Exit button text

/* Title constants */
#define TITLE_HEIGHT              17.5f            // Title height
#define TITLE_WIDTH               35.0f            // Title width
#define TITLE_TEXT_RASTER_POS_X   66.0f            // Title text x coord
#define TITLE_TEXT_RASTER_POS_Y   92.5f            // Title text y coord
#define TITLE_AUTHOR_RASTER_POS_X 66.0f            // Title author x coord
#define TITLE_AUTHOR_RASTER_POS_Y 85.0f            // Title author y coord
#define TITLE_TEXT                "CG - Maman 11"  // Title text
#define TITLE_AUTHOR              "Aaron Barkan"   // Title author name
#define TITLE_LINE_WIDTH          3.0f             // Title frame line width


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
    glMatrixMode(GL_PROJECTION);           // Set projection parameters
    gluOrtho2D(0.0, X_COORD_RNG, 0.0, Y_COORD_RNG);
}


/* Get font according to window size */
void* getFont(const std::string& fontName)
{
    void* font = nullptr;
    bool large = (glutGet(GLUT_WINDOW_WIDTH) >= FONT_SWITCH_WIDTH) && (glutGet(GLUT_WINDOW_HEIGHT) >= FONT_SWITCH_HEIGHT);
    if ("Times Roman" == fontName)
    {
        font = large ? GLUT_BITMAP_TIMES_ROMAN_24 : GLUT_BITMAP_TIMES_ROMAN_10;
    }
    else if ("Halvetica" == fontName)
    {
        font = large ? GLUT_BITMAP_HELVETICA_18 : GLUT_BITMAP_HELVETICA_10;
    }
    else
    {
        std::cout << "[getFont] Invalid font name: " << fontName << std::endl;
    }
    return font;
}


/* Displays an exit button at the bottom left of the window */
void displayExitButton(void)
{
    /* Create red rectangle at the bottom left */
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(0.0f, 0.0f, EXIT_BTN_WIDTH, EXIT_BTN_HEIGHT);

    /* Add text to button */
    glColor3f(0.0f, 0.0f, 0.0f);
    void* font = getFont("Times Roman");
    glRasterPos2f(EXIT_BTN_TEXT_RASTER_POS_X, EXIT_BTN_TEXT_RASTER_POS_Y);
    for (char c : EXIT_BTN_TEXT)
    {
        glutBitmapCharacter(font, c);
    }
}


void displayTitle(void)
{
    /* Create a black frame at the top right */
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(TITLE_LINE_WIDTH);
    glBegin(GL_LINE_LOOP);
        glVertex2f(X_COORD_RNG - TITLE_WIDTH, Y_COORD_RNG - TITLE_HEIGHT);
        glVertex2f(X_COORD_RNG, Y_COORD_RNG - TITLE_HEIGHT);
        glVertex2f(X_COORD_RNG, Y_COORD_RNG);
        glVertex2f(X_COORD_RNG - TITLE_WIDTH, Y_COORD_RNG);
    glEnd();

    /* Create title text */
    void* font = getFont("Times Roman");
    glRasterPos2f(TITLE_TEXT_RASTER_POS_X, TITLE_TEXT_RASTER_POS_Y);
    for (char c : TITLE_TEXT)
    {
        glutBitmapCharacter(font, c);
    }

    /* Create title author */
    font = getFont("Halvetica");
    glRasterPos2f(TITLE_AUTHOR_RASTER_POS_X, TITLE_AUTHOR_RASTER_POS_Y);
    for (char c : TITLE_AUTHOR)
    {
        glutBitmapCharacter(font, c);
    }
}


/* CALLBACK FUNCTIONS */

/* Callback for 'glutDisplayFunc' */
void displayCallback(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    displayExitButton();
    displayTitle();
    glFlush();
}


/* Callback for 'glutMouseFunc' */
void mouseCallback(int button, int state, int _x, int _y)
{
    /* Transform mouse coordinates to Ortho 2D coordinates */
    const long long windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    const double x = _x * X_COORD_RNG / glutGet(GLUT_WINDOW_WIDTH);
    const double y = (windowHeight - _y) * Y_COORD_RNG / windowHeight;

    /* Exit program if right click on exit button */
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
        x <= EXIT_BTN_WIDTH && y <= EXIT_BTN_HEIGHT)
    {
        glutDestroyWindow(1);
        exit(0);
    }
}


/* Assigns callback functions for events */
void registerCallbacks(void)
{
    glutDisplayFunc(displayCallback);
    glutMouseFunc(mouseCallback);
}


/* Main function */
int main(int argc, char** argv)
{
    createWindow(argc, argv);  // Create the display-window
    registerCallbacks();       // Assign callback functions for events
    glutMainLoop();            // Display everything and wait
}

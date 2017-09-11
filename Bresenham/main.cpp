#include <algorithm>
#include <iostream>
#include <GL/glut.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf;

using namespace std;

void setPixel(int x, int y)
{
    glColor3f(255, 255, 255); //Set pixel to black  
    glBegin(GL_POINTS);
    glVertex2i(x, y); //Set pixel coordinates 
    glEnd();
}

//Draw line if X distance is greater than Y
void bresenhamX(int x0, int y0, int x1, int y1, int dx, int dy)
{
    int i, j, k;
    
    i = 2 * dy - dx;
    j = 2 * dy;
    k = 2 * (dy - dx);
    if (!(x0 < x1)) {
        swap(x0, x1);
        swap(y0, y1);
    }
    setPixel(x0, y0);
    while (x0 < x1) {
        if (i < 0)
        i += j;
        else {
            if (y0 < y1)
            ++y0;
            else
            --y0;
            i += k;
        }
        ++x0;
        setPixel(x0, y0);
    }
}

//Draw line if X distance is lesser than Y
void bresenhamY(int x0, int y0, int x1, int y1, int dx, int dy)
{
    int i, j, k;
    
    i = 2 * dx - dy;
    j = 2 * dx;
    k = 2 * (dx - dy);
    if (!(y0 < y1)) {
        swap(x0, x1);
        swap(y0, y1);
    }
    setPixel(x0, y0);
    while (y0 < y1) {
        if (i < 0)
        i += j;
        else {
            if (x0 > x1)
            --x0;
            else
            ++x0;
            i += k;
        }
        ++y0;
        setPixel(x0, y0);
    }
}

//Called by mouse(), will call the appropriate function depending on the length of the X and Y axis
void bresenham(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    
    if (dx >= dy)
    bresenhamX(x0, y0, x1, y1, dx, dy);
    else
    bresenhamY(x0, y0, x1, y1, dx, dy);
}

//Calls Bresenham function when the mouse has traced a line
bool firstClick = true;
// bool firstClick2 = true;
bool drawLine = false;
// bool drawLine2 = false;

void mouse(int btn, int state, int x, int y)
{
    if( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        if (firstClick) {
            firstClick= not firstClick;
        }
    }
}

void mouse2( int x, int y)
{
    cout<<"x: "<<x<<",y: "<<y<<endl;
    
    if (!firstClick) {
        xi = x;
        yi = (wh - y);
        firstClick = true;
        drawLine = false;
    }
    else {
        xf = x;
        yf = (wh - y);
        // firstClick = true;
        drawLine = true;
        // firstClick2=true;
    }
    if( drawLine )
    {
        bresenham(xi, yi, xf, yf);
    }
    glFlush();


    glutPostRedisplay();
}



// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Press escape to exit.
        exit(0);
        break;
    default:
        break;
    }
}

// Drawing (display) routine.
void drawScene(void)
{
    glClearColor(0, 0,0,0); // Set foreground color
    glColor3f(0.1, 0.2, 0.2); // Clear screen to background color.
    glClear(GL_COLOR_BUFFER_BIT);   //Flush created objects to the screen, i.e., force rendering.
}

// OpenGL window reshape routine.
void setup()
{
    glViewport(0, 0, ww, wh); // Set viewport size to be entire OpenGL window.
    glMatrixMode(GL_PROJECTION); // Set matrix mode to projection.
    glLoadIdentity(); // Clear current projection matrix to identity.
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh); // Specify the orthographic (or perpendicular) projection, i.e., define the viewing box.
    glMatrixMode(GL_MODELVIEW); // Set matrix mode to modelview.
}

// Main routine: defines window properties, creates window, registers callback routines and begins processing.
int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode as single-buffered and RGB color.
    glutInitWindowSize(ww, wh); // Set OpenGL window size.
    glutInitWindowPosition(100, 100); // Set position of OpenGL window upper-left corner.
    glutCreateWindow("Bresenham"); // Create OpenGL window with title.
    glutDisplayFunc(drawScene); // Register display routine.
    setup(); // Register reshape routine.
    glutKeyboardFunc(keyInput); // Register keyboard routine.
    glutMouseFunc(mouse); // Begin processing.
    glutMotionFunc(mouse2); // Begin processing.
    glutMainLoop();
    return 0;
}
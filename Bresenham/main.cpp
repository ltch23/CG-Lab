#define GLUT_DISABLE_ATEXIT_HACK	
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#define KEY_ESC 27

int xi, yi, xf, yf;

using namespace std;

//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex2d(0, 0);
	glVertex2d(400, 0);
	glColor3d(0, 255, 0);
	glVertex2d(0, 0);
	glVertex2d(0, 400);
	glEnd();
}

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


void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  { 
     //hacer algo x,z
     if (firstClick) {
        firstClick= not firstClick;
    }
  }	
}

void OnMouseMotion(int x, int y)
{
     //hacer algo x,z
     cout<<"x: "<<x<<",y: "<<y<<endl;
     
     if (!firstClick) {
         xi = x;
         yi = (800 - y);
         firstClick = true;
         drawLine = false;
     }
     else {
         xf = x;
         yf = (800 - y);
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



void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay(); 
}

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	// glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	// glLoadIdentity();
	// glOrtho(-400.0f,  400.0f,-400.0f, 400.0f, -1.0f, 1.0f); 
	
	
	// //dibuja el gizmo
	// displayGizmo();

	// //doble buffer, mantener esta instruccion al fin de la funcion
    // glutSwapBuffers();
    
    glClearColor(0, 0,0,0); // Set foreground color
    glColor3f(0.1, 0.2, 0.2); // Clear screen to background color.
    glClear(GL_COLOR_BUFFER_BIT);   //Flush created objects to the screen, i.e., force rendering.

}

GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height); // Specify the orthographic (or perpendicular) projection, i.e., define the viewing box.
    
	// glOrtho(-400.0f,  400.0f,-400.0f, 400.0f, -1.0f, 1.0f); 
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}


GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP2 bis OpenGL : Bresenham"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint); 
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);

	glutMainLoop(); //bucle de rendering

	return 0;
}
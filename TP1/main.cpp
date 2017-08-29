#define GLUT_DISABLE_ATEXIT_HACK	
#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

#define KEY_ESC 27

// int x=0,y=0, len_edge=0;
long op=0;

//	dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex2d(20, 0);
	glColor3d(0, 255, 0);
	glVertex2d(0, 0);
	glVertex2d(0, 20);
	glColor3d(0, 0, 255);
	glVertex2d(20, 0);
	glVertex2d(0, 20);
	glEnd();
}

//dibuja un simple gizmo
void displayGizmo2()
{
	glBegin(GL_LINE_LOOP);
	glColor3d(255,255,255);
	glVertex2d(-1, 0);
	glVertex2d(1, 0);
	glVertex2d(0, 1);
	glEnd();
}

//  1) dibuja cuadrado
void displaySquare(int x,int y, int edge)
{
	int tmp=edge*0.5;
	glBegin(GL_LINE_LOOP);
	glColor3d(255,0,0);
	glVertex2d(x-tmp, y+tmp);
	glVertex2d(x+tmp, y+tmp);
	glVertex2d(x+tmp, y-tmp);
	glVertex2d(x-tmp, y-tmp);
	glEnd();
	
}

// 2) dibuja circulo
void displayCircle(int x,int y,int r)
{
	int number_edges=10; //*2 por 2*PI
	glBegin(GL_LINE_LOOP);
	for(float i=0; i<2*M_PI; i+= M_PI/number_edges)
		glVertex2f((r*cos(i))+x, (r*sin(i)+y));
	glEnd();
}


// 3) dibuja circulos desde un mismo punto izquierda
void displayCircles(int number_circles,int red_radio){
	float radio_default=30;
	int x=0,y=0;
	displayCircle(x,y,radio_default); 
	radio_default-=red_radio;
	
	for( int i=1; i<number_circles;i++,radio_default-=red_radio){
		if(radio_default<0) break;
		x-=red_radio;
		displayCircle(x,y,radio_default);
	}
}	


// 4) dibuja circulos de mayor a menor icontinuos 
void displayCircles2(int number_circles,int red_radio){
	float radio_default=10;
	float tmp_radio=radio_default;
	int x=-40,y=0;
	displayCircle(x,y,radio_default); 
	radio_default-=red_radio; // no perder radio para avanzar
	
	for( int i=1; i<number_circles;i++,radio_default-=red_radio){
		if(radio_default<0) break;
		
		x+=tmp_radio+radio_default;// suma de radio anterior y actual
		displayCircle(x,y,radio_default);
		tmp_radio=radio_default;
		
	}
}	

// 5) dibuja circulos de mayor a menor icontinuos con angulo
void displayCircles3(int number_circles, float red_radio, float _teta){
	float radio_default=10;
	float radio=radio_default;

	float tmp_radio=radio_default;
	float x=0,y=0;
	float teta= (_teta*M_PI/180);
	float x1=-40.0,y1=-40.0;
	displayCircle(x1,y1,radio_default); 
	radio_default-=red_radio; // no perder radio para avanzar
	
	radio+=radio_default;
	x=(cos(teta)*radio)+x1;
	y=(sin(teta)*radio)+y1;
	displayCircle(x,y,radio_default);
	tmp_radio=radio_default;
	
	radio_default-=red_radio; //
	for( int i=2; i<number_circles;i++,radio_default-=red_radio){
		if(radio_default<0) break;
		radio=tmp_radio+radio_default;
		x=(cos(teta)*radio)+x;
		y=(sin(teta)*radio)+y;
		displayCircle(x,y,radio_default);
		tmp_radio=radio_default;
	}
}	


//	funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();

	switch (op){
		case 1:
		// dibuja el gizmo
		displayGizmo();
		break;
		case 2:
		// dibuja cuadrado
		displaySquare(0,0,4);
		break;
		case 3:
		// dibuja circulo
		displayCircle(-30,-15,10);
		break;
		case 4:
		// dibuja circulos
		displayCircles(10,4);
		break;
		case 5:
		//	dibuja circulos 2
		displayCircles2(7,1);
		break;
		case 6:
		// dibuja circulos 3
		displayCircles3(5,2.0,45.0);
		break;
		default:
		break;
	}
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//inicializacion de OpenGL
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-50.0f,  50.0f,-50.0f, 50.0f, -1.0f, 1.0f); 
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
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

//	el programa principal

int main(int argc, char** argv) {

	//datos por consola

	op = strtol(argv[1], NULL, 10);
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint); 
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}

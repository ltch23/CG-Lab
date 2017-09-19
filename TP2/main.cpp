#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

GLfloat xRotated=0, yRotated=0, zRotated=0;
GLfloat xRect=0.0;
bool dir=true;
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();

void exercise1();
void exercise2();
void exercise3();
void exercise4();


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 2 : Transformaciones");


	initGL();
	init_scene();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
	

	
	/*dibujar aqui*/
	exercise4();

	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	xRotated+=1;
	yRotated+=3;
 
	if(xRect>= 8)	dir=false;
	else if(xRect<=-8)	dir=true;

	if(dir==true) 	xRect+=0.1;
	else 	xRect-=0.1;

	window_display();

	glutPostRedisplay();
}


void exercise1(){

	//primero rotamos z 
	glRotatef(xRotated,0.0,0.0,1.0);	
	//trasladar  z
	glTranslatef(4.0, 0.0, 0.0);
	glColor3f(0.0,1.0, 0.0);
	glutSolidTeapot(4.0);
}

void exercise2(){

	glColor3f(1.0,1.0, 1.0);
	glutSolidSphere(0.5,8,8);
		
		glTranslatef(xRect, 0.0, 0.0);
		glColor3f(1.0,0.0, 0.0);
		glutSolidSphere(0.5,8,8);

		glRotatef(xRotated,0.0,0.0,1.0);	
		glTranslatef(8.0, 0.0, 0.0);
		glColor3f(0.0,1.0, 0.0);
		glutSolidTeapot(2.0);
}
	
void exercise3(){
	
	glColor3f(1.0,1.0, 1.0);
	glutSolidSphere(0.5,8,8);
	
	glPushMatrix();
		// primero rotamos z 
		glTranslatef(xRect, 0.0, 0.0);
		glColor3f(1.0,0.0, 0.0);
		glutSolidSphere(0.5,8,8);
		
		glRotatef(xRotated,0.0,0.0,1.0);	
		glTranslatef(8.0, 0.0, 0.0);
		glColor3f(0.0,1.0, 0.0);
		glutSolidTeapot(2.0);
		/*******/
		// rotar y
		glRotatef(-yRotated,0.0,1.0,0.0);	
		// trasladar desde x
		glTranslatef(3.0, 0.0, 0.0);
		glColor3f(1.0,0.0, 1.0);
		glutSolidTorus(0.2,0.6,10,20);
		
	glPopMatrix();
		
	glPushMatrix();
		//rotar x
		glRotatef(-xRotated,1.0,0.0,0.0);	
		//trasladar -y
		glTranslatef(0.0, 8.0, 0.0);
		
		glColor3f(0.0,0.0, 1.0);
		glutSolidCube(2);
		glPopMatrix();
		
	}	
	
	//Sistema Solar
	void exercise4(){
		
	glPushMatrix();

		glRotatef(xRotated,0.0,1.0,0.0);	
		glColor3f(1.0,1.0, 0.0);
		glutSolidSphere(4,8,8);
		
	glPopMatrix();
	
	glPushMatrix();
		
		//tierra
		glRotatef(xRotated,0.0,1.0,0.0);	
		// glRotatef(xRotated,0.0,1.0,0.0);	
		glTranslatef(10.0, 00.0, 0.0);
		//sobre si misma
		glRotatef(3*xRotated,0.0,1.0,0.0);	
		glColor3f(0.0,0.0, 1.0);
		glutSolidSphere(2,8,8);
		
		//luna
		glRotatef(2*xRotated,0.0,0.0,1.0);	
		glTranslatef(5.0, 00.0, 0.0);
		//sobre si misma
		glRotatef(1.5*xRotated,0.0,1.0,0.0);	
		glColor3f(1.0,1.0, 1.0);
		glutSolidSphere(0.2,8,8);
		
		glPopMatrix();
		
		glPushMatrix();
		
		glRotatef(3*xRotated,0.0,0.0,1.0);	
		glTranslatef(18.0, 00.0, 0.0);
		//sobre si misma
		glRotatef(3*xRotated,0.0,1.0,0.0);	
		glColor3f(1.0,0.0,0.0);
		glutSolidSphere(3,8,8);
		
	glPopMatrix();
		//trasladar -y
	
}

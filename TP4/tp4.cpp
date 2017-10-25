#define GLUT_DISABLE_ATEXIT_HACK	
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "TextureManager.h"
#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27


void init_scene();
void draw();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);


//variables para el gizmo
float delta_x = -50.0; 
float delta_y = 5.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_z = -100.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)
GLint suelo;
GLint pared1;
GLint pared2;
GLint pared3;
GLint tejado;
GLint techo;

///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		step++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		step--;
		glutPostRedisplay();
		break;


	}
}



///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	
	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}


//function called on each frame
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 3 : Transformations 3D Part 2");

	// suelo = TextureManager::Inst()->LoadTexture("pasto.jpg",GL_BGR_EXT,GL_RGB);
	suelo = TextureManager::Inst()->LoadTexture("pasto.jpg", GL_BGR_EXT, GL_RGB);
	pared1 = TextureManager::Inst()->LoadTexture("puerta.jpeg", GL_BGR_EXT, GL_RGB);
	pared2 = TextureManager::Inst()->LoadTexture("paredatras.jpeg", GL_BGR_EXT, GL_RGB);
	pared3 = TextureManager::Inst()->LoadTexture("costado.jpeg", GL_BGR_EXT, GL_RGB);
	tejado = TextureManager::Inst()->LoadTexture("tejado.jpg", GL_BGR_EXT, GL_RGB);
	techo = TextureManager::Inst()->LoadTexture("techo.jpeg", GL_BGR_EXT, GL_RGB);
	
	initGL();
	init_scene();


	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	
	
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	glutKeyboardFunc(&window_key);
	//glutKeyboardUpFunc(&window_key_up); //key release events
	glutSpecialFunc(&callback_special);
	//glutSpecialUpFunc(&callback_special_up); //key release events
	
	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient[]={0.3f,0.3f,0.3f,1.0f};
	GLfloat diffuse[]={0.8f,0.8f,0.8f,1.0f};
	GLfloat specular[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat shinn[]={10.f};
	
	GLfloat lightAmbient[]={0.3f,0.3f,0.3f,1.0f};
	GLfloat lightPosition[]={150.0f,150.0f,150.0f,1.0f};

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinn);
	
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmbient);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);



	glClearColor(RED, GREEN, BLUE, ALPHA);
}


void Gizmo3D(){

	
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();


	return;

}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);

	glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);


	// Gizmo3D();
	draw();
	

	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

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
	glutPostRedisplay();
}
void draw(){

	// SUELO
	// glutSolidSphere(10,64,64);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, suelo);
	glBegin(GL_POLYGON);
	glNormal3f(1,0,0);
	glTexCoord2f(0.0,0.0);	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(5.0,0.0);	glVertex3f(0.0f, 0.0f, 40.0f);
	glTexCoord2f(5.0,5.0);	glVertex3f(40.0f, 0.0f, 40.0f );
	glTexCoord2f(0.0,5.0);	glVertex3f(40.0f, 0.0f, 00.0f);
	glEnd();
	glPopMatrix();
	
	// CASA
	// PAREDES
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, pared1);
	glBegin(GL_POLYGON);
	glNormal3f(1,0,0);
	glTexCoord2f(0.0,0.0);	glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(1.0,0.0);	glVertex3f(10.0f, 0.0f, 10.0f);
	glTexCoord2f(1.0,1.0);	glVertex3f(10.0f, 10.0f, 10.0f );
	glTexCoord2f(0.0,1.0);	glVertex3f(0.0f, 10.0f, 10.0f);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, pared2);
	glBegin(GL_POLYGON);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0,0.0);	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0,0.0);	glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0,1.0);	glVertex3f(10.0f, 10.0f, 0.0f );
	glTexCoord2f(0.0,1.0);	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, pared3);
	glBegin(GL_POLYGON);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0,0.0);	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0,0.0);	glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(1.0,1.0);	glVertex3f(0.0f, 10.0f, 10.0f );
	glTexCoord2f(0.0,1.0);	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, pared3);
	glNormal3f(0,0,1);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);	glVertex3f(10.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0,0.0);	glVertex3f(10.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0,1.0);	glVertex3f(10.0f, 10.0f, 10.0f );
		glTexCoord2f(0.0,1.0);	glVertex3f(10.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();
	


	//TECHOS

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, techo);
	glNormal3f(0,0,1);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0,0.0);	glVertex3f(10.0f, 10.0f, 0.0f);
		glTexCoord2f(4.0,0.0);	glVertex3f(10.0f, 15.0f, 5.0f);
		glTexCoord2f(0.0,4.0);	glVertex3f(10.0f, 10.0f, 10.0f );
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, techo);
	glNormal3f(0,0,1);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0,0.0);	glVertex3f(0.0f, 10.0f, 0.0f);
		glTexCoord2f(4.0,0.0);	glVertex3f(0.0f, 15.0f, 5.0f);
		glTexCoord2f(0.0,4.0);	glVertex3f(0.0f, 10.0f, 10.0f );
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tejado);
	glNormal3f(1,1,0);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);	glVertex3f(0.0f, 10.0f, 0.0f);
		glTexCoord2f(1.0,0.0);	glVertex3f(0.0f, 15.0f, 5.0f);
		glTexCoord2f(1.0,1.0);	glVertex3f(10.0f, 15.0f, 5.0f );
		glTexCoord2f(0.0,1.0);	glVertex3f(10.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tejado);
	glNormal3f(1,1,0);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);	glVertex3f(0.0f, 10.0f, 10.0f);
		glTexCoord2f(1.0,0.0);	glVertex3f(0.0f, 15.0f, 5.0f);
		glTexCoord2f(1.0,1.0);	glVertex3f(10.0f, 15.0f, 5.0f );
		glTexCoord2f(0.0,1.0);	glVertex3f(10.0f, 10.0f, 10.0f);
	glEnd();
	glPopMatrix();
	
		
	// ARBOL 
	glTranslated(15.0f, 0.0f, 25.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(gluNewQuadric(),1.0f,1.0f,10.0f,32.0f,32.0f);
	// HOJAS
	glTranslated(0.0f, 00.0f, 15.0f);
	glutSolidSphere(5.0, 32.0f, 32.0f);
	
	
}





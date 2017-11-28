#include <GL/glut.h>
#include "terreno.h"
#include "TextureManager.h"

using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

GLint texture;
float delta_x = 0.0;
float delta_y = 90.0;
float mouse_x, mouse_y;
float var_x = -2500.0;
float var_y = -3000.0;

GLfloat lightPosition[4];
GLfloat light_axis_x=4000,light_axis_y=4000,light_axis_z=4000;

Terreno terreno;

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid callback_mouse(int button, int state, int x, int y);
GLvoid callback_motion(int x, int y);
GLvoid callback_special(int key, int x, int y);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_idle();

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowSize(800, 800);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP 5: Malla");

  texture = TextureManager::Inst()->LoadTexture("fontvieille.tga", GL_BGR_EXT, GL_RGB);
  terreno.load("fontvieille_ant.txt");

  initGL();

  init_scene();
  glutDisplayFunc(&window_display);
  glutReshapeFunc(&window_reshape);

  glutMouseFunc(&callback_mouse);
  glutMotionFunc(&callback_motion);

  glutKeyboardFunc(&window_key);
  glutSpecialFunc(&callback_special);

  glutIdleFunc(&window_idle);
  glutMainLoop();
  
  
  return 0;
}

GLvoid window_idle()
{
  glutPostRedisplay();
}

GLvoid callback_special(int key, int x, int y)
{
  switch (key)
    {
    case GLUT_KEY_UP:
      var_y += 35.0;
      glutPostRedisplay();
      break;

    case GLUT_KEY_DOWN:
      var_y -= 35.0;
      glutPostRedisplay();
      break;

    case GLUT_KEY_LEFT:
      var_x += 35.0;
      glutPostRedisplay();
      break;

    case GLUT_KEY_RIGHT:
      var_x -= 35.0;
      glutPostRedisplay();
      break;

    case GLUT_KEY_PAGE_UP:
      light_axis_z+=50;
      glutPostRedisplay();
      break;
    case GLUT_KEY_PAGE_DOWN:
      light_axis_z-=50;
      glutPostRedisplay();
      break;
    }
}


GLvoid window_key(unsigned char key, int x, int y)
{
  switch (key) {
  case ECHAP:
    exit(1);
    break;
  case 99:
    light_axis_x+=50;
    glutPostRedisplay();
    break;
  case 122:
    light_axis_x-=50;
    glutPostRedisplay();
    break;
  case 115:
    light_axis_y+=50;
    glutPostRedisplay();
    break;
  case 120:
    light_axis_y-=50;
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

GLvoid callback_mouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
      mouse_x = x;
      mouse_y = y;
    }
}

GLvoid callback_motion(int x, int y)
{

  delta_x += x - mouse_x;
  delta_y += y - mouse_y;
  mouse_x = x;
  mouse_y = y;
  glutPostRedisplay();
}




void init_scene() {}

GLvoid initGL()
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(RED, GREEN, BLUE, ALPHA);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

GLvoid window_display()
{
  lightPosition[0]=light_axis_x;
  lightPosition[1]=light_axis_y;
  lightPosition[2]=light_axis_z;
  lightPosition[3]=1.0f;

  GLfloat light0Ambient [] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat light0Difusa [] = {0.5f, 0.5f, 0.5f, 1.0f};
  GLfloat light0Especular [] = {0.5f, 0.5f, 0.5f, 1.0f};


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Difusa);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0Especular);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  gluPerspective(90.0f, 1.0f, 0.01f, 15000.0f);
  glTranslatef(var_x, -1500, var_y);

  glRotatef(delta_x, 0.0, 1.0, 0.0);
  glRotatef(delta_y, 1.0, 0.0, 0.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  terreno.display();

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


#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


#define ESCAPE 27

int window;


float rtri = 0.0f;


float rquad = 0.0f;



void InitGL(int Width, int Height)
{

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);                // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);                // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);            // Enables Depth Testing
  glShadeModel(GL_SMOOTH);            // Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);
}

void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)                // Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);        // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

float ballX = -0.5f;
float ballY = 0.0f;
float ballZ = 0.0f;

void drawBall(void) {
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(ballX,ballY,ballZ);

        glutSolidSphere (0.3, 20, 20);
        glTranslatef(ballX+1.5,ballY,ballZ);
        glutSolidSphere (0.3, 20, 20); //
        }



void DrawGLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(rtri,0.0f,-6.0f);

  glBegin(GL_POLYGON);
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3f(-1.0f, 1.0f, 0.0f);
  glVertex3f(0.4f, 1.0f, 0.0f);

  glVertex3f(1.0f, 0.4f, 0.0f);

  glColor3f(0.0f,1.0f,0.0f);
  glVertex3f( 1.0f,0.0f, 0.0f);        // Bottom Right
  glColor3f(0.0f,0.0f,1.0f);            // Set The Color To Blue
  glVertex3f(-1.0f,0.0f, 0.0f);// Bottom Left

  //glVertex3f();
  glEnd();                    // we're done with the polygon (smooth color interpolation)
  drawBall();

  rtri+=0.0005f;                    // Increase The Rotation Variable For The Triangle
  if(rtri>=2)
      rtri=-2.0f;
  rquad-=15.0f;                    // Decrease The Rotation Variable For The Quad


  glutSwapBuffers();
}


void keyPressed(unsigned char key, int x, int y)
{

    /* If escape is pressed, kill everything. */
    if (key == ESCAPE)
    {
    /* shut down our window */
    glutDestroyWindow(window);

    /* exit the program...normal termination. */
    exit(0);
    }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

  /* get a 640 x 480 window */
  glutInitWindowSize(640, 480);

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);

  /* Open a window */
  window = glutCreateWindow("Moving Car");

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);

  /* Go fullscreen.  This is as soon as possible. */
  //glutFullScreen();

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&DrawGLScene);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);

  /* Initialize our window. */
  InitGL(640, 480);

  /* Start Event Processing Engine */
  glutMainLoop();

  return 1;
}

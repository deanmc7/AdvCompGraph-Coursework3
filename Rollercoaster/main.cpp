#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Geometry.h"

/* ASCII codes for various special Keys */
#define ESCAPE 27
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

#define PI 3.1415926532L
Geometry* geometry = new Geometry();

double g_curX = 210, g_curY = -10.5, g_curZ = 290;
double g_angle = 120;

void setupLights()
{
	/* ambient RGBA reflectance of the material */
	float materialAmbience[] = { 0.5, 0.5, 0.5, 1.0 };
	/* ambient RGBA intensity of entire scene */
	float sceneAmbience[] = { 0.7, 0.7, 0.7, 1.0 };

	/* specify lighting model parameters
	- GL_LIGHT_MODEL_AMBIENT: specify ambient RGBA intensity of entire scene*/
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, sceneAmbience);
	/* specify material parameters for lighting model
	- GL_FRONT_AND_BACK: front and back faces are being updated
	- GL_AMBIENT: update all the ambient faces */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbience);
}

void setTexturedMode()
{
	/* enable texturing */
	glEnable(GL_TEXTURE_2D);
	/* if texturing isn't enabled, generate error */
	if (!glIsEnabled(GL_TEXTURE_2D))
		fprintf(stderr, "Texture enabling failed.\n");
}

void turnLightsOff()
{
	glDisable(GL_LIGHTING);
}

void turnLightsOn()
{
	glEnable(GL_LIGHTING);
}

void setSmoothShadeModel()
{
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
}

void setFlatShadeModel()
{
	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
}

void activateLight()
{
	glEnable(GL_LIGHT0);
}

void setupLightDirection()
{
	float lightDirection[] = { sin(0.0) * 100.0, 60.0, cos(0.0) * 100.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
}

void SwitchToOrtho()
{
	/* specifies the Projection matrix as the current matrix */
	glMatrixMode(GL_PROJECTION);
	/* pushes current matrix stack down by one */
	glPushMatrix();
	/* move to the center of the screen */
	glLoadIdentity();
	/* define a 2-D orthographic projection matrix */
	gluOrtho2D(0, 1024, 0, 768);
	/* scales along the x, -y, and z axes */
	glScalef(1, -1, 1);
	/* moves along the x, y and z-axis, moves -'768' units (down) on y-
	axis */
	glTranslatef(0, -1.0 * 768, 0);
	/* specifies the Modelview matrix as the current matrix */
	glMatrixMode(GL_MODELVIEW);
	/* move to the center of the screen */
	glLoadIdentity();
}

void SwitchFromOrtho()
{
	/* specifies the Projection matrix as the current matrix */
	glMatrixMode(GL_PROJECTION);
	/* pops current matrix stack */
	glPopMatrix();
	/* specifies the Modelview matrix as the current matrix */
	glMatrixMode(GL_MODELVIEW);
}

static void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	setSmoothShadeModel();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	geometry->loadTextures();

	glEnable(GL_NORMALIZE);
	/* specifies front- and back-facing polygons
	-counterclockwise polygons are front-facing (GL_CCW)
	-clockwise polygons are front-facing (GL_CW) */
	glFrontFace(GL_CCW);
	/* specifies whether front- or back-faces are to be culled */
	glCullFace(GL_BACK);

	activateLight();

	setupLights();

	turnLightsOn();

	setTexturedMode();

	geometry->buildTrack();
}

static void display()
{
	static double supa; // This value will be remembered each time display is called
	supa += .005; // Increment 5 degrees each call

	/* clear frame buffer and z-buffer - thus clearing the screen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* move to the center of the screen */
	glLoadIdentity();

	glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		/* rotate camera 'g_angle' degrees about the y-axis */
		glRotatef(g_angle, 0.0, 1.0, 0.0);

		/* translate (move) camera to the intitial "spawn" position, thereafter
		moving the camera to the updated position as calculated by
		InputKeyPressed */
		glTranslatef(g_curX, g_curY, g_curZ);
		geometry->drawFloor();
		geometry->drawTrack();
	glPopMatrix();

	glutSwapBuffers();		      // Swap buffers
	glutPostRedisplay();		      // Display results
	glFlush();			      // Flush drawing routines
}

static void Reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (GLfloat)width / (GLfloat)height, 0.05, 2000.0);
	gluLookAt(0.0, 10.0, 15, 0.0, 10.0, 0, 0.0, 1.0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 'i':
	case 'I':
		glLoadIdentity();
		gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 'x':
	case 'X':
		glRotatef(10., 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		glRotatef(30., 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case ESCAPE:
		exit(0);
		break;
	}
}

void specialKeyFunc(int key, int x, int y)
{
	/* switch control structure */
	switch (key)
	{
		/* when the up-arrow on the keyboard is pressed */
	case GLUT_KEY_UP:
	{
		double rads = g_angle / 180.0L * PI;
		/* the smaller the number divided by the faster you glide forward */
		double dx = -sin(rads) / 0.1;// 1.5;
		/* the smaller the number divided by the faster you glide forward */
		double dz = cos(rads) / 0.1;// 1.5;

		g_curX += dx;
		g_curZ += dz;
	}
		break;

		/* when the back-arrow on the keyboard is pressed */
	case GLUT_KEY_DOWN:
	{
		double rads = g_angle / 180.0L * PI;
		/* the smaller the number divided by the faster you glide forward */
		double dx = -sin(rads) / 0.1; //3.0;
		/* the smaller the number divided by the faster you glide forward */
		double dz = cos(rads) / 0.1;// 3.0;

		g_curX -= dx;
		g_curZ -= dz;
	}
		break;

		/* when the right-arrow on the keyboard is pressed */
	case GLUT_KEY_RIGHT:
		g_angle += 5;
		break;

		/* when the left-arrow on the keyboard is pressed */
	case GLUT_KEY_LEFT:
		g_angle -= 5;
		break;

		/* when anything else is pressed */
	default:
		break;
	}
	/* sets the current window for redisplay */
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Initialize modes
	glutInitWindowSize(1220, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Rollercoaster Program"); // Note that arg[0] is name of program (Window name)
	Init();
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeyFunc);
	glutKeyboardFunc(keyboardFunc);	// Set the callback function for key presses
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}
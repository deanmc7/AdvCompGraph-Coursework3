#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Geometry.h"
#include "Camera.h"
#include "Car.h"
#include "Skybox.h"
#include "Mesh.h"
#include "Collision.h"
#include "Utility.h"
#include "Textures.h"
#include "Track.h"

/*
Wheels
Techniques (shader implementation)
*/

Geometry*	mGeometry	= new Geometry();
Textures*	mTextures	= new Textures();
Track*		mTrack		= new Track();
Camera*		mCamera		= new Camera(210, -10.5, 290, 120);

Car*		mCar1		= new Car(6.8f, 0.005f, mTrack->getTrackInnerRadius(),
	mTrack->getTrackOuterRadius(), mTrack->getTrackHeight(), GRAVITY, mTrack->getNumOfHills(), 1.0f, CAR1SPEED);

Car*		mCar2		= new Car(10.0f, 0.005f, mTrack->getTrackInnerRadius(),
	mTrack->getTrackOuterRadius(), mTrack->getTrackHeight(), GRAVITY, mTrack->getNumOfHills(), 100.0f, CAR2SPEED);

Car*		mCar3		= new Car(4.0f, 0.005f, mTrack->getTrackInnerRadius(),
	mTrack->getTrackOuterRadius(), mTrack->getTrackHeight(), GRAVITY, mTrack->getNumOfHills(), 200.0f, CAR3SPEED);

Skybox*		mSkybox		= new Skybox(mCamera);

Collision*	mCollision	= new Collision();

std::vector<glm::vec4> vertices;
std::vector<vec3> normals;
std::vector<vec2> uvs;
GLuint vertexBuffer;
GLuint uvBuffer;
Mesh* mDesert			= new Mesh("desert.obj");

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

	mTextures->loadTextures();

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
	
	mDesert->Load(vertices, normals, uvs);
	mDesert->InitShader();
	//mDesert->Draw(vertexBuffer, uvBuffer, vertices, normals, uvs);

	mCar1->Init();
	mCar1->BuildCar();

	mCar2->Init();
	mCar2->BuildCar();

	mCar3->Init();
	mCar3->BuildCar();

	mSkybox->Init();
}

static void display()
{
	/* clear frame buffer and z-buffer - thus clearing the screen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* move to the center of the screen */
	glLoadIdentity();

	glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		/* rotate camera 'g_angle' degrees about the y-axis */
		glRotatef(mCamera->getAngle(), 0.0, 1.0, 0.0);

		/* translate (move) camera to the intitial "spawn" position, thereafter
		moving the camera to the updated position as calculated by
		InputKeyPressed */
		glTranslatef(mCamera->getX(), mCamera->getY(), mCamera->getZ());
		
		mSkybox->Render(mTextures);
		
		mTrack->buildTrack();
		mTrack->buildTrackFloor(mTextures);
		
		//mGeometry->drawFloor(mTextures);

		mCar1->RenderCar();
		mCar1->BuildWheel();
		mCar1->Display(mCar1->getCarX(), mCar1->getCarY(), mCar1->getCarZ());
		
		mCar2->RenderCar();
		mCar2->BuildWheel();
		mCar2->Display(mCar2->getCarX(), mCar2->getCarY(), mCar2->getCarZ());
		
		mCar3->RenderCar();
		mCar3->BuildWheel();
		mCar3->Display(mCar3->getCarX(), mCar3->getCarY(), mCar3->getCarZ());
		
		Collision::Point car1Centre(mCar1->getCarX(), mCar1->getCarY(), mCar1->getCarZ());
		Collision::Point car1HalfWidth(mCar1->getRad(), mCar1->getRad(), mCar1->getRad());
		Collision::AABB car1AABB(car1Centre, car1HalfWidth);
		
		Collision::Point car2Centre(mCar2->getCarX(), mCar2->getCarY(), mCar2->getCarZ());
		Collision::Point car2HalfWidth(mCar2->getRad(), mCar2->getRad(), mCar2->getRad());
		Collision::AABB car2AABB(car2Centre, car2HalfWidth);
		
		Collision::Point car3Centre(mCar3->getCarX(), mCar3->getCarY(), mCar3->getCarZ());
		Collision::Point car3HalfWidth(mCar3->getRad(), mCar3->getRad(), mCar3->getRad());
		Collision::AABB car3AABB(car3Centre, car3HalfWidth);
		
		if (mCollision->checkCollision(car1AABB, car2AABB))
		{
			std::cout << "HIT car 1 and 2\n";
			GLfloat temp1, temp2;
			temp1 = mCar1->getSpeed();
			temp2 = mCar2->getSpeed();
			mCar1->swapSpeeds(temp1, temp2);
			mCar1->setSpeed(temp1);
			mCar2->setSpeed(temp2);
		}

		if (mCollision->checkCollision(car1AABB, car3AABB))
		{
			std::cout << "HIT car 1 and 3\n";
			GLfloat temp1, temp2;
			temp1 = mCar1->getSpeed();
			temp2 = mCar3->getSpeed();
			mCar1->swapSpeeds(temp1, temp2);
			mCar1->setSpeed(temp1);
			mCar3->setSpeed(temp2);
		}

		if (mCollision->checkCollision(car2AABB, car3AABB))
		{
			std::cout << "HIT car 2 and 3\n";
			GLfloat temp1, temp2;
			temp1 = mCar2->getSpeed();
			temp2 = mCar3->getSpeed();
			mCar2->swapSpeeds(temp1, temp2);
			mCar2->setSpeed(temp1);
			mCar3->setSpeed(temp2);
		}
		glTranslatef(0.0f, -200.0f, 0.0f);
		mDesert->Display(vertices, vertexBuffer, uvBuffer, mTextures, DESERT_TEXTURE, normals, uvs);
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
	mCamera->SpecialKeyInput(key, x, y);

	/* sets the current window for redisplay */
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1220, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Rollercoaster");
	glewInit();
	Init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutSpecialFunc(specialKeyFunc);
	glutKeyboardFunc(keyboardFunc);	// Set the callback function for key presses
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}
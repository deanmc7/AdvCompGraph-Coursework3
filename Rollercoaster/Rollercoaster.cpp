#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Geometry.h"
#include "Camera.h"
#include "GlutBackend.h"
#include "TypeDefs.h"

/*
Camera
Physics
Cars
Wheels
Track
Techniques (shader implementation)
*/

#define WINDOW_WIDTH 1220
#define WINDOW_HEIGHT 600

class Rollercoaster : public Callbacks
{
private:
	Camera*		mCamera;
	Geometry*	mGeometry;
public:

	Rollercoaster()
	{
		mCamera = NULL;
		mGeometry = NULL;
	}

	virtual ~Rollercoaster(){}

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
	
	void activateLight()
	{
		glEnable(GL_LIGHT0);
	}

	void setupLightDirection()
	{
		float lightDirection[] = { sin(0.0) * 100.0, 60.0, cos(0.0) * 100.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
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

	bool Init()
	{
		mCamera = new Camera(210, -10.5, 290, 120);

		mGeometry = new Geometry();

		setSmoothShadeModel();

		mGeometry->loadTextures();

		activateLight();

		setupLights();

		turnLightsOn();

		setupLightDirection();

		setTexturedMode();

		mGeometry->buildTrack();

		return true;
	}

	void Run()
	{
		BackendRun(this);
	}

	virtual void RenderCallback()
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
			glRotatef(mCamera->getAngle(), 0.0, 1.0, 0.0);

			/* translate (move) camera to the intitial "spawn" position, thereafter
			moving the camera to the updated position as calculated by
			InputKeyPressed */
			glTranslatef(mCamera->getX(), mCamera->getY(), mCamera->getZ());
			mGeometry->drawFloor();
			mGeometry->drawTrack();			
		glPopMatrix();

		BackendSwapBuffers();	    // Swap buffers
		glutPostRedisplay();		// Display results
		glFlush();					// Flush drawing routines
	}

	void KeyboardCallback(KEY key)
	{
		switch (key)
		{
		case KEY_q:
		case KEY_ESCAPE:
			BackendLeaveMainLoop();
			break;
		default:
			mCamera->KeyInput(key);
		}
	}

	virtual void ReshapeCallback(int width, int height)
	{
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(70.0, (GLfloat)width / (GLfloat)height, 0.05, 2000.0);
		gluLookAt(0.0, 10.0, 15, 0.0, 10.0, 0, 0.0, 1.0, 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

};

/*int main(int argc, char** argv)
{
	BackendInit(argc, argv, true);

	if (!gCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rollercoaster Program"))
		return 1;
	
	Rollercoaster* mApp = new Rollercoaster();

	if (!mApp->Init())
		return 1;

	mApp->Run();

	delete mApp;

	return 0;
}*/
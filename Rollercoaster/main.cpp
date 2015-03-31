#include "Geometry.h"
#include "Camera.h"
#include "Car.h"
#include "Skybox.h"
#include "Mesh.h"
#include "Collision.h"
#include "Utility.h"
#include "Textures.h"
#include "Track.h"
#include "Lighting.h"

Geometry*	mGeometry	= new Geometry();
Textures*	mTextures	= new Textures();
Track*		mTrack		= new Track();
Camera*		mCamera		= new Camera(0, 10, 150, 0);

Car*		mCar1 = new Car(0.5f, 0.005f, mTrack->getTrackInnerRadius(),
	mTrack->getTrackOuterRadius(), mTrack->getTrackHeight(), GRAVITY, mTrack->getNumOfHills(), 1.0f, CAR1SPEED, mTextures);

Car*		mCar2 = new Car(0.5f, 0.005f, mTrack->getTrackInnerRadius(),
	mTrack->getTrackOuterRadius(), mTrack->getTrackHeight(), GRAVITY, mTrack->getNumOfHills(), 100.0f, CAR2SPEED, mTextures);

Car*		mCar3 = new Car(0.5f, 0.005f, mTrack->getTrackInnerRadius(),
	mTrack->getTrackOuterRadius(), mTrack->getTrackHeight(), GRAVITY, mTrack->getNumOfHills(), 200.0f, CAR3SPEED, mTextures);

Skybox*		mSkybox		= new Skybox(mCamera);

Collision*	mCollision	= new Collision();

Lighting*	mLighting	= new Lighting();

Shaders allShaders[3];

ShaderProgram fogShader;

glm::mat4 mProjection;
float fGlobalAngle;

namespace FogParameters
{
	float fDensity = 0.04f;
	float fStart = 10.0f;
	float fEnd = 75.0f;
	glm::vec4 vFogColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	int iFogEquation = FOG_EQUATION_EXP; // 0 = linear, 1 = exp, 2 = exp2
};

void setTexturedMode()
{
	/* enable texturing */
	glEnable(GL_TEXTURE_2D);
	/* if texturing isn't enabled, generate error */
	if (!glIsEnabled(GL_TEXTURE_2D))
		fprintf(stderr, "Texture enabling failed.\n");
}

void InitShaders()
{
	allShaders[0].LoadShader("shader.vs", GL_VERTEX_SHADER);
	allShaders[1].LoadShader("shader.fs", GL_FRAGMENT_SHADER);
	allShaders[2].LoadShader("fog.fs", GL_FRAGMENT_SHADER);

	fogShader.createProgram();
	fogShader.addShader(&allShaders[0]);
	fogShader.addShader(&allShaders[1]);
	fogShader.addShader(&allShaders[2]);
	fogShader.linkProgram();
}

void callFog()
{
	fogShader.useProgram();

	fogShader.setUniform("sunLight.vColor", glm::vec3(1.0f, 1.0f, 1.0f));
	fogShader.setUniform("sunLight.fAmbientIntensity", 1.0f); // Full light for skybox
	fogShader.setUniform("sunLight.vDirection", glm::vec3(0, -1, 0));

	fogShader.setUniform("matrices.projectionMatrix", mProjection);
	fogShader.setUniform("gSampler", 0);

	glm::mat4 mModelView = mCamera->getLook();
	glm::mat4 mModelToCamera;

	fogShader.setUniform("FogParameters.iEquation", FogParameters::iFogEquation);
	fogShader.setUniform("FogParameters.vFogColor", FogParameters::vFogColor);

	if (FogParameters::iFogEquation == FOG_EQUATION_LINEAR)
	{
		fogShader.setUniform("FogParameters.fStart", FogParameters::fStart);
		fogShader.setUniform("FogParameters.fEnd", FogParameters::fEnd);
	}
	else
		fogShader.setUniform("FogParameters.fDensity", FogParameters::fDensity);

	fogShader.setUniform("matrices.modelViewMatrix", glm::translate(mModelView, mCamera->getPos()));

	fogShader.setUniform("sunLight.fAmbientIntensity", 0.55f);
	fogShader.setUniform("matrices.modelViewMatrix", &mModelView);
}

static void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	mLighting->SetSmoothShadeModel();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
	/* specifies front- and back-facing polygons
	-counterclockwise polygons are front-facing (GL_CCW)
	-clockwise polygons are front-facing (GL_CW) */
	glFrontFace(GL_CCW);
	/* specifies whether front- or back-faces are to be culled */
	glCullFace(GL_BACK);

	InitShaders();

	mLighting->ActivateLight();

	mLighting->SetUpLighting();

	mLighting->TurnLightsOn();

	mLighting->InitShaders();
	
	setTexturedMode();

	mTextures->loadTextures();

	mSkybox->Init();

	mGeometry->Init();

	mCar1->Init();
	mCar1->BuildCar();
	mCar1->BuildWheel();

	mCar2->Init();
	mCar2->BuildCar();
	mCar2->BuildWheel();

	mCar3->Init();
	mCar3->BuildCar();
	mCar3->BuildWheel();
}

static void display()
{
	/* clear frame buffer and z-buffer - thus clearing the screen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* move to the center of the screen */
	//glLoadIdentity();


	glPushMatrix();
		//glRotatef(mCamera->getAngle(), 0.0, 1.0, 0.0);
		//glTranslatef(0.0f, 200.0f, 0.0f);
		
		mLighting->Display();
		mSkybox->Render(mTextures);
		
		//geometry renders
		//mGeometry->drawCreature();
		//mGeometry->drawCastle();
		
		mTrack->buildTrack();
		mTrack->buildTrackFloor(mTextures);		

		mCar1->Display(mCar1->getCarX(), mCar1->getCarY(), mCar1->getCarZ());

		mCar2->Display(mCar2->getCarX(), mCar2->getCarY(), mCar2->getCarZ());

		mCar3->Display(mCar3->getCarX(), mCar3->getCarY(), mCar3->getCarZ());
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2000.0f, 0.0f);
		fogShader.useProgram();

		fogShader.setUniform("sunLight.vColor", glm::vec3(1.0f, 1.0f, 1.0f));
		fogShader.setUniform("sunLight.fAmbientIntensity", 1.0f); // Full light for skybox
		fogShader.setUniform("sunLight.vDirection", glm::vec3(0, -1, 0));

		fogShader.setUniform("matrices.projectionMatrix", mProjection);
		fogShader.setUniform("gSampler", 0);

		glm::mat4 mModelView = mCamera->getLook();
		glm::mat4 mModelToCamera;

		fogShader.setUniform("FogParameters.iEquation", FogParameters::iFogEquation);
		fogShader.setUniform("FogParameters.vFogColor", FogParameters::vFogColor);

		if (FogParameters::iFogEquation == FOG_EQUATION_LINEAR)
		{
			fogShader.setUniform("FogParameters.fStart", FogParameters::fStart);
			fogShader.setUniform("FogParameters.fEnd", FogParameters::fEnd);
		}
		else
			fogShader.setUniform("FogParameters.fDensity", FogParameters::fDensity);

		fogShader.setUniform("matrices.modelViewMatrix", glm::translate(mModelView, mCamera->getPos()));

		fogShader.setUniform("sunLight.fAmbientIntensity", 0.55f);
		fogShader.setUniform("matrices.modelViewMatrix", &mModelView);
		fogShader.setUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		glm::vec3 vPos = glm::vec3(0.0f, -2000.0f, 0.0f);
		mModelToCamera = glm::translate(glm::mat4(1.0), vPos);
		mModelToCamera = glm::rotate(mModelToCamera, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		fogShader.setUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelToCamera)));
		fogShader.setUniform("matrices.modelViewMatrix", mModelView*mModelToCamera);
		mGeometry->drawTerrain();
		glTranslatef(0.0f, 2000.0f, 0.0f);
	glPopMatrix();
		
	glPushMatrix();
		Collision::Point car1Centre(mCar1->getCarX(), mCar1->getCarY(), mCar1->getCarZ());
		Collision::Point car1HalfWidth(11.5, 6.8, 11.5);
		Collision::AABB car1AABB(car1Centre, car1HalfWidth);
		
		Collision::Point car2Centre(mCar2->getCarX(), mCar2->getCarY(), mCar2->getCarZ());
		Collision::Point car2HalfWidth(11.5, 6.8, 11.5);
		Collision::AABB car2AABB(car2Centre, car2HalfWidth);
		
		Collision::Point car3Centre(mCar3->getCarX(), mCar3->getCarY(), mCar3->getCarZ());
		Collision::Point car3HalfWidth(11.5, 6.8, 11.5);
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
	glPopMatrix();

	if (mCamera->getFollow() == 1)
	{
		mCamera->followCart(mCar1);
	}

	if (mCamera->getFollow() == 2)
	{
		mCamera->followCart(mCar2);
	}

	if (mCamera->getFollow() == 3)
	{
		mCamera->followCart(mCar3);
	}

	glutSwapBuffers();		// Swap buffers
	glutPostRedisplay();	// Display results
	glFlush();				// Flush drawing routines
}

static void Reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	mProjection = glm::perspective((float)70.0, (float)width / (float)height, (float)0.05, (float)2000.0);
	gluPerspective(70.0, (GLfloat)width / (GLfloat)height, 0.05, 2000.0);
	gluLookAt(0.0, 10.0, 150.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardFunc(unsigned char key, int x, int y)
{
	mCamera->KeyInput(key, x, y);
	switch (key) {
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
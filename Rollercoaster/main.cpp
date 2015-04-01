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
#include "ClothSim.h"

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

Skybox*		mSkybox		= new Skybox(mCamera, mTextures);

Collision*	mCollision	= new Collision();

Lighting*	mLighting	= new Lighting();

ClothSim* flag = new ClothSim();

Shaders allShaders[8];

ShaderProgram lightingShader, fogShader, skyboxShader, toonShader, blurShader;

glm::mat4 mProjection;
float fGlobalAngle;

/*namespace FogParameters
{
	float fDensity = 0.04f;
	float fStart = 10.0f;
	float fEnd = 75.0f;
	glm::vec4 vFogColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	int iFogEquation = FOG_EQUATION_EXP; // 0 = linear, 1 = exp, 2 = exp2
};*/

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
	allShaders[0].LoadShader("diffuse.vs", GL_VERTEX_SHADER);
	allShaders[1].LoadShader("diffuse.fs", GL_FRAGMENT_SHADER);
	allShaders[2].LoadShader("fog.fs", GL_FRAGMENT_SHADER);
	allShaders[3].LoadShader("skybox.vs", GL_VERTEX_SHADER);
	allShaders[4].LoadShader("skybox.fs", GL_FRAGMENT_SHADER);
	allShaders[5].LoadShader("toon.vs", GL_VERTEX_SHADER);
	allShaders[6].LoadShader("toon.fs", GL_FRAGMENT_SHADER);
	allShaders[7].LoadShader("blur.fs", GL_FRAGMENT_SHADER);

	lightingShader.createProgram();
	lightingShader.addShader(&allShaders[0]);
	lightingShader.addShader(&allShaders[1]);
	lightingShader.linkProgram();

	fogShader.createProgram();
	fogShader.addShader(&allShaders[2]);
	fogShader.linkProgram();

	skyboxShader.createProgram();
	skyboxShader.addShader(&allShaders[3]);
	skyboxShader.addShader(&allShaders[4]);
	skyboxShader.linkProgram();

	toonShader.createProgram();
	toonShader.addShader(&allShaders[5]);
	toonShader.addShader(&allShaders[6]);
	toonShader.linkProgram();

	blurShader.createProgram();
	blurShader.addShader(&allShaders[7]);
	blurShader.linkProgram();
}

/*void callFog()
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
}*/

static void Init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);

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

	mLighting->TurnLightsOn();
	
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

	/*glDepthMask(GL_FALSE);
		skyboxShader.useProgram();
		skyboxShader.setUniform("P",mProjection);
		skyboxShader.setUniform("V", mCamera->getLook());
		skyboxShader.setUniform("cube_texture", mSkybox->getCubeMap());
		mSkybox->Render(mTextures);
		glUseProgram(0);
		glDepthMask(GL_TRUE);*/
	mSkybox->Render(mTextures);

	/*glDisable(GL_CULL_FACE);
	 //initialise the cloth 
	flag->drawCloth();
	 //enable culling (remove all the faces pointing away from the viewer) 
	glEnable(GL_CULL_FACE);*/

	glPushMatrix();		
		toonShader.useProgram();
		mTrack->buildTrack();
		glUseProgram(0);
		mTrack->buildTrackFloor(mTextures);		
	
		mCar1->Display(mCar1->getCarX(), mCar1->getCarY(), mCar1->getCarZ());

		mCar2->Display(mCar2->getCarX(), mCar2->getCarY(), mCar2->getCarZ());

		mCar3->Display(mCar3->getCarX(), mCar3->getCarY(), mCar3->getCarZ());
	glPopMatrix();
	
	glPushMatrix();
	//Fog attempts
	/*fogShader.useProgram();

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
	fogShader.setUniform("matrices.modelViewMatrix", mModelView*mModelToCamera);*/

	/*fogShader.useProgram();
	glm::mat4 ground_model_matrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 10, -15, +10, 1);
	fogShader.setUniform("model_matrix", ground_model_matrix);
	fogShader.setUniform("view_matrix", mCamera->getPos());
	fogShader.setUniform("projection_matrix", mProjection);
	fogShader.setUniform("light_position", mLighting->getLightOnePos());
	fogShader.setUniform("eye_position", mCamera->getPos());*/
	
	/*fogShader.setUniform("lightPos[1]", mLighting->getLightOnePos());
	fogShader.setUniform("density", 0.005f);

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glFogf(GL_FOG_DENSITY, 0.005f);*/

	/*fogShader.useProgram();		
		fogShader.setUniform("density", 0.05f);*/

		glTranslatef(0.0f, -2000.0f, 0.0f);
		mGeometry->drawTerrain();
		glTranslatef(0.0f, 2000.0f, 0.0f);

		lightingShader.useProgram();
		lightingShader.setUniform("lightPos", mLighting->getLightOnePos());

		if (mCamera->getFollow() == 1)
		{
			toonShader.useProgram();
			glPushMatrix();
			glColor3f(0.0f, 1.0f, 1.0f);
			glTranslatef(0.0f, 80.0f, 0.0);
			glutSolidTeapot(30.0f);
			glPopMatrix();

			glTranslatef(0.0f, -100.0f, 0.0f);
			mGeometry->drawColumn();
			glTranslatef(0.0f, 100.0f, 0.0f);
			glUseProgram(0);
		}
		else if (mCamera->getFollow() == 2)
		{
			toonShader.useProgram();
			glPushMatrix();
			glColor3f(0.0f, 1.0f, 1.0f);
			glTranslatef(0.0f, 80.0f, 0.0);
			glutSolidTeapot(30.0f);
			glPopMatrix();
			glUseProgram(0);

			glTranslatef(0.0f, -100.0f, 0.0f);
			mGeometry->drawColumn();
			glTranslatef(0.0f, 100.0f, 0.0f);
		}
		else if (mCamera->getFollow() == 3)
		{
			
			glPushMatrix();
			glColor3f(0.0f, 1.0f, 1.0f);
			glTranslatef(0.0f, 80.0f, 0.0);
			glutSolidTeapot(30.0f);
			glPopMatrix();
			
			toonShader.useProgram();
			glTranslatef(0.0f, -100.0f, 0.0f);
			mGeometry->drawColumn();
			glTranslatef(0.0f, 100.0f, 0.0f);
			glUseProgram(0);
		}
		else
		{
			glPushMatrix();
			glColor3f(0.0f, 1.0f, 1.0f);
			glTranslatef(0.0f, 80.0f, 0.0);
			glutSolidTeapot(30.0f);
			glPopMatrix();

			glTranslatef(0.0f, -100.0f, 0.0f);
			mGeometry->drawColumn();
			glTranslatef(0.0f, 100.0f, 0.0f);
		}

		glUseProgram(0);
	glPopMatrix();
		
	/*Collision Detection and response*/
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

	/*flag->wind = 0.4;
	flag->clothPhysics();
	flag->initUnitForce();*/

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
	/* setups the cloth */
	/*flag->particleSetup();
	flag->clothPhysics();*/
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
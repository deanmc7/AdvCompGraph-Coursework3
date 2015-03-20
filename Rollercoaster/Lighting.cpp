#include"Lighting.h"

Lighting::Lighting()
{

	lightPos0[0] = 140.0f;
	lightPos0[1] = 250.0f;
	lightPos0[2] = 140.0f;
	lightPos0[3] = 1.0f;

	lightPos1[0] = -140.0f;
	lightPos1[1] = 250.0f;
	lightPos1[2] = 140.0f;
	lightPos1[3] = 1.0f;

	lightPos2[0] = 0.0f;
	lightPos2[1] = 250.0f;
	lightPos2[2] = -200.0f;
	lightPos2[3] = 1.0f;

	materialAmbience[0] = 0.5;
	materialAmbience[1] = 0.5;
	materialAmbience[2] = 0.5;
	materialAmbience[3] = 1.0;

	sceneAmbience[0] = 0.7;
	sceneAmbience[1] = 0.7;
	sceneAmbience[2] = 0.7;
	sceneAmbience[3] = 1.0;

	lightDirection[0] = sin(0.0) * 100.0;
	lightDirection[1] = 60.0;
	lightDirection[2] = cos(0.0) * 100.0;
	lightDirection[3] = 0.0;

	lightRotation = 0.0f;
}

void Lighting::InitShaders(void)
{
	if (!lightingShader.Load("skybox.vs", "skybox.fs"))
	{
		std::cout << "error loading skybox shader\n";
		return;
	}

	lightingShader.CompileShader();

	lightingShader.UniformLocations = new GLuint[1];
	lightingShader.UniformLocations[0] = glGetUniformLocation(lightingShader, "lightPos[0]");
	if (lightingShader != 1)
	{
		glUniform3fv(lightingShader, 1, lightDirection);
	}

	
}

void Lighting::Display(void)
{
	glUseProgram(lightingShader);
	glUniform3fv(lightingShader, 1, lightDirection);
	glUseProgram(0);
}

void Lighting::UseShader(void)
{
	glUseProgram(lightingShader);
}

void Lighting::SetUpLighting(void)
{
	/* specify lighting model parameters
	- GL_LIGHT_MODEL_AMBIENT: specify ambient RGBA intensity of entire scene*/
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, sceneAmbience);
	/* specify material parameters for lighting model
	- GL_FRONT_AND_BACK: front and back faces are being updated
	- GL_AMBIENT: update all the ambient faces */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbience);
}

void Lighting::TurnLightsOff(void)
{
	glDisable(GL_LIGHTING);
}

void Lighting::TurnLightsOn(void)
{
	glEnable(GL_LIGHTING);
}

void Lighting::SetSmoothShadeModel(void)
{
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
}

void Lighting::SetFlatShadeModel(void)
{
	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
}

void Lighting::ActivateLight(void)
{
	glEnable(GL_LIGHT0);
}

void Lighting::SetupLightDirection(void)
{
	glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
}
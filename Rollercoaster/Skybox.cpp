#include "Skybox.h"

Skybox::Skybox(Camera* pCam) : pCamera(pCam)
{
}

void Skybox::Init()
{
	if (!mSkyboxShader.Load("skybox.vs", "skybox.fs"))
	{
		std::cout << "error loading skybox shader\n";
		return;
	}

	mSkyboxShader.UniformLocations = new GLuint[1];
	mSkyboxShader.UniformLocations[0] = glGetUniformLocation(mSkyboxShader, "CameraPosition");
}

void Skybox::Render(Textures* texture)
{
	glPushMatrix();
		
		glLoadIdentity();
		gluLookAt(0, 0, 0,
			pCamera->getX(), pCamera->getY(), pCamera->getZ(),
			0, 1, 0);

		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);

		glColor4f(1, 1, 1, 1);

		/*glUseProgram(mSkyboxShader);
		glUniform3fv(mSkyboxShader.UniformLocations[0], 1, &pCamera->position);*/

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_FRONT));
		glBegin(GL_QUADS);
		glUseProgram(mSkyboxShader);
		glUniform3fv(mSkyboxShader.UniformLocations[0], 1, &pCamera->position);
			glTexCoord2f(0, 1);
			glVertex3f(50.0f, -50.0f, -50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-50.0f, -50.0f, -50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-50.0f, 50.0f, -50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(50.0f, 50.0f, -50.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_LEFT));
		glBegin(GL_QUADS);
		glUseProgram(mSkyboxShader);
		glUniform3fv(mSkyboxShader.UniformLocations[0], 1, &pCamera->position);
			glTexCoord2f(0, 1);
			glVertex3f(50.0f, -50.0f, 50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(50.0f, -50.0f, -50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(50.0f, 50.0f, -50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(50.0f, 50.0f, 50.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_BACK));
		glBegin(GL_QUADS);
		glUseProgram(mSkyboxShader);
		glUniform3fv(mSkyboxShader.UniformLocations[0], 1, &pCamera->position);
			glTexCoord2f(0, 1);
			glVertex3f(-50.0f, -50.0f, 50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(50.0f, -50.0f, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(50.0f, 50.0f, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-50.0f, 50.0f, 50.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_RIGHT));
		glBegin(GL_QUADS);
		glUseProgram(mSkyboxShader);
		glUniform3fv(mSkyboxShader.UniformLocations[0], 1, &pCamera->position);
			glTexCoord2f(0, 1);
			glVertex3f(-50.0f, -50.0f, -50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-50.0f, -50.0f, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-50.0f, 50.0f, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_TOP));
		glBegin(GL_QUADS);
		glUseProgram(mSkyboxShader);
		glUniform3fv(mSkyboxShader.UniformLocations[0], 1, &pCamera->position);
			glTexCoord2f(1, 1);
			glVertex3f(-50.0f, 50.0f, -50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-50.0f, 50.0f, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(50.0f, 50.0f, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(50.0f, 50.0f, -50.0f);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopAttrib();
	glPopMatrix();
}
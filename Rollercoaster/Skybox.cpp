#include "Skybox.h"

Skybox::Skybox(Camera* pCam) : pCamera(pCam)
{
	this->textureFilenames[SKYBOX_TOP]		= "skyboxTop.tga";
	this->textureFilenames[SKYBOX_FRONT]	= "skyboxFront.tga";
	this->textureFilenames[SKYBOX_LEFT]		= "skyboxLeft.tga";
	this->textureFilenames[SKYBOX_RIGHT]	= "skyboxRight.tga";
	this->textureFilenames[SKYBOX_BACK]		= "skyboxBack.tga";
}

bool Skybox::loadImage(char* textureName, int currentTexture)
{
	/* image loading type */
	TGAloader Img;

	/* loads the texture */
	if (Img.Load(textureName) != IMG_OK)
		return false;

	/* the texture handle is set to the current loaded texture */
	glBindTexture(GL_TEXTURE_2D, this->textures[currentTexture]);

	/* setup the texture if it is a standard solid 24bit image (no transparency) */
	if (Img.GetBPP() == 24)
	{
		/* specifies the solid two-dimensional texture */
		glTexImage2D(GL_TEXTURE_2D, 0, 3, Img.GetWidth(), Img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, Img.GetImg());
	}
	/* else setup the texture if it is a 32bit image with an alpha channel */
	else if (Img.GetBPP() == 32)
	{
		/* specifies the transparent two-dimensional texture */
		glTexImage2D(GL_TEXTURE_2D, 0, 4, Img.GetWidth(), Img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Img.GetImg());
	}
	else
	{
		return false;
	}

	/* sets the texture parameters - for reference, consult Prog 8.6's discussion */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true;
}

void Skybox::loadTextures(void)
{
	/* deals with the generation of texture names  */
	glGenTextures(5, this->textures);

	for (int i = 0; i < 5; i++)
	{
		loadImage(this->textureFilenames[i], i);
	}
}

void Skybox::Render(void)
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

		glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_FRONT]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(50.0f, -50.0f, -50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-50.0f, -50.0f, -50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-50.0f, 50.0f, -50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(50.0f, 50.0f, -50.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_LEFT]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(50.0f, -50.0f, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(50.0f, -50.0f, -50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(50.0f, 50.0f, -50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(50.0f, 50.0f, 50.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_BACK]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-50.0f, -50.0f, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(50.0f, -50.0f, 50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(50.0f, 50.0f, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-50.0f, 50.0f, 50.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_RIGHT]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-50.0f, -50.0f, -50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-50.0f, -50.0f, 50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-50.0f, 50.0f, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_TOP]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(-50.0f, 50.0f, -50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-50.0f, 50.0f, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(50.0f, 50.0f, 50.0f);
			glTexCoord2f(1, 1);
			glVertex3f(50.0f, 50.0f, -50.0f);
		glEnd();

	glPopAttrib();
	glPopMatrix();
}
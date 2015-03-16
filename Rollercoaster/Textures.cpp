#include "Textures.h"

Textures::Textures()
{
	this->textureFilenames[FLOOR_TEXTURE] = "grass.tga";
	this->textureFilenames[TRACK_TEXTURE] = "track.tga";
	this->textureFilenames[SKYBOX_TOP] = "skyboxTop.tga";
	this->textureFilenames[SKYBOX_FRONT] = "skyboxFront.tga";
	this->textureFilenames[SKYBOX_LEFT] = "skyboxLeft.tga";
	this->textureFilenames[SKYBOX_RIGHT] = "skyboxRight.tga";
	this->textureFilenames[SKYBOX_BACK] = "skyboxBack.tga";
	this->textureFilenames[DESERT_TEXTURE] = "desert.tga";
}

bool Textures::loadImage(char* textureName, int currentTexture)
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

void Textures::loadTextures(void)
{
	/* deals with the generation of texture names  */
	glGenTextures(NUM_OF_TEXTURES, this->textures);

	for (int i = 0; i < NUM_OF_TEXTURES; i++)
	{
		loadImage(this->textureFilenames[i], i);
	}
}

GLuint Textures::getTexture(int texture)
{
	return textures[texture];
}
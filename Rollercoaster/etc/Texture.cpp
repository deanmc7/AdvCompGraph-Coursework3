#include "Texture.h"
#include <iostream>

Texture::Texture(GLenum textureTarget, const std::string& fileName) : pTextureTarget(textureTarget), pFilename(fileName)
{
}

bool Texture::Load()
{
	try {
		pImage.read(pFilename);
		pImage.write(&pBlob, "RGBA");
	}
	catch (Magick::Error& error){
		std::cout << "Error loading texture " << pFilename << ":" << error.what() << std::endl;
		return false;
	}

	glGenTextures(1, &pTextureObj);
	glBindTexture(pTextureTarget, pTextureObj);
	glTexImage2D(pTextureTarget, 0, GL_RGBA, pImage.columns(), pImage.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pBlob.data());
	glTexParameterf(pTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(pTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(pTextureTarget, 0);

	return true;
}

void Texture::Bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(pTextureTarget, pTextureObj);
}
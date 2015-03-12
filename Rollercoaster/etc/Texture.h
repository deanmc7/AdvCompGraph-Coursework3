#ifndef __Texture_h_
#define __Texture_h_

#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <Magick++.h>

class Texture
{
private:
	std::string pFilename;
	GLenum pTextureTarget;
	GLenum pTextureObj;
	Magick::Image pImage;
	Magick::Blob pBlob;

public:
	Texture(GLenum textureTarget, const std::string& fileName);

	bool Load();

	void Bind(GLenum textureUnit);
};

#endif //#ifndef __Texture_h_
#ifndef __CubemapText_h_
#define __CubemapText_h_

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Magick++.h>
#include "Utility.h"

class CubemapText
{
private:
	std::string m_fileNames[6];
	GLuint m_textureObj;

public:
	CubemapText(const std::string& Directory,
		const std::string& PosXFilename,
		const std::string& NegXFilename,
		const std::string& PosYFilename,
		const std::string& NegYFilename,
		const std::string& PosZFilename,
		const std::string& NegZFilename);

	~CubemapText();

	bool Load();

	void Bind(GLenum TextUnit);
};

#endif //#ifndef __CubemapText_h_
#ifndef __Shaders_h_
#define __Shaders_h_

#include "Utility.h"



class Shaders
{
private:
	GLuint vShader, fShader;
	GLchar* vString;
	GLchar* fString;
	GLuint program;
	GLboolean needsValidating;

public:
	Shaders(void);
	~Shaders(void);

	operator GLuint();

	GLuint LoadShader(char* Filename, GLuint type);
	bool Load(char* vertexFilename, char* fragmentFilename);
	void CreateShaderObj();
	bool CompileShader();


	GLuint *UniformLocations, *AttribLocations;
};

#endif //#ifndef __Shaders_h_
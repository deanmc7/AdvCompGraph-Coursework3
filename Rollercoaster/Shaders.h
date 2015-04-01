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
	
	bool mLoaded;
	GLuint mShader;

public:
	Shaders(void);
	~Shaders(void);

	operator GLuint();

	GLuint LoadShader(char* Filename, GLuint type);
	bool Load(char* vertexFilename, char* fragmentFilename);
	void CreateShaderObj();
	bool CompileShader();

	bool isLoaded();
	uint getID();


	GLuint *UniformLocations, *AttribLocations;
};

class ShaderProgram
{
private:
	uint mProgram; // ID of program
	bool isLinked; // Whether program was linked and is ready to use
public:
	ShaderProgram();

	void createProgram();
	void deleteProgram();

	bool addShader(Shaders* mShader);
	bool linkProgram();

	void useProgram();

	uint getProgramID();

	// Setting vectors
	void setUniform(std::string sName, glm::vec2* vVectors, int iCount = 1);
	void setUniform(std::string sName, const glm::vec2 vVector);
	void setUniform(std::string sName, glm::vec3* vVectors, int iCount = 1);
	void setUniform(std::string sName, const glm::vec3 vVector);
	void setUniform(std::string sName, glm::vec4* vVectors, int iCount = 1);
	void setUniform(std::string sName, const glm::vec4 vVector);

	// Setting floats
	void setUniform(std::string sName, float* fValues, int iCount = 1);
	void setUniform(std::string sName, const float fValue);

	// Setting 3x3 matrices
	void setUniform(std::string sName, glm::mat3* mMatrices, int iCount = 1);
	void setUniform(std::string sName, const glm::mat3 mMatrix);

	// Setting 4x4 matrices
	void setUniform(std::string sName, glm::mat4* mMatrices, int iCount = 1);
	void setUniform(std::string sName, const glm::mat4 mMatrix);

	// Setting integers
	void setUniform(std::string sName, int* iValues, int iCount = 1);
	void setUniform(std::string sName, const int iValue);
	void setUniform(std::string sName, GLuint iValue);

};

#endif //#ifndef __Shaders_h_
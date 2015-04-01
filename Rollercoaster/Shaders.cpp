#include "Shaders.h"

Shaders::Shaders() : vShader(0), fShader(0), needsValidating(GL_TRUE), UniformLocations(0), AttribLocations(0), mLoaded(false)
{
}

Shaders::~Shaders()
{
}

Shaders::operator GLuint ()
{
	return program;
}

bool Shaders::Load(char* vertexFilename, char* fragmentFilename)
{
	bool error = false;

	error |= ((vShader = LoadShader(vertexFilename, GL_VERTEX_SHADER)) == 0);
	error |= ((fShader = LoadShader(fragmentFilename, GL_FRAGMENT_SHADER)) == 0);

	if (error)
	{
		return false;
	}

	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE)
	{
		return false;
	}

	if (needsValidating)
	{
		GLint success;

		glValidateProgram(program);
		glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
		if (!success)
		{
			GLchar log[MAX_LOG_SIZE];
			glGetProgramInfoLog(program, MAX_LOG_SIZE, NULL, log);
			return false;
		}

		needsValidating = GL_FALSE;
	}

	return true;
}

GLuint Shaders::LoadShader(char* filename, GLuint type)
{
	GLchar* shaderText = NULL;
	GLint shaderLength = 0;
	FILE* fp;

	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgetc(fp) != EOF)
		{
			shaderLength++;
		}
		rewind(fp);
		shaderText = (GLchar *)malloc(shaderLength + 1);
		if (shaderText != NULL)
		{
			fread(shaderText, 1, shaderLength, fp);
		}
		shaderText[shaderLength] = '\0';
		fclose(fp);
	}

	//return shaderText;
	
	mShader = glCreateShader(type);

	glShaderSource(mShader, 1, (const char**)&shaderText, NULL);
	delete[] shaderText;
	glCompileShader(mShader);

	GLint status;
	glGetShaderiv(mShader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		char log[MAX_LOG_SIZE];
		glGetShaderInfoLog(fShader, MAX_LOG_SIZE, NULL, log);
		std::cout << "Error loading shader" << log << std::endl;
		glDeleteShader(mShader);
		return 0;
	}
	mLoaded = true;

	return mShader;
	/*
	const GLchar* vStringPtr[1];
	const GLchar* fStringPtr[1];

	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	vStringPtr[0] = vString;
	glShaderSource(vShader, 1, vStringPtr, NULL);

	fStringPtr[0] = fString;
	glShaderSource(fShader, 1, fStringPtr, NULL);

	GLint isSuccessful;

	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &isSuccessful);
	if (!isSuccessful)
	{
		char log[MAX_LOG_SIZE];
		glGetShaderInfoLog(vShader, MAX_LOG_SIZE, NULL, log);
		std::cout << "Error loading Vertex shader" << log << std::endl;
		Sleep(5000);
		exit(0);
	}

	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &isSuccessful);
	if (!isSuccessful)
	{
		char log[MAX_LOG_SIZE];
		glGetShaderInfoLog(fShader, MAX_LOG_SIZE, NULL, log);
		std::cout << "Error loading Vertex shader" << log << std::endl;
		Sleep(5000);
		exit(0);
	}*/

}

void Shaders::CreateShaderObj()
{
	const GLchar* vStringPtr[1];
	const GLchar* fStringPtr[1];

	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	vStringPtr[0] = vString;
	glShaderSource(vShader, 1, vStringPtr, NULL);

	fStringPtr[0] = fString;
	glShaderSource(fShader, 1, fStringPtr, NULL);
}

bool Shaders::CompileShader()
{
	GLint isSuccessful;

	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &isSuccessful);
	if (!isSuccessful)
	{
		char log[MAX_LOG_SIZE];
		glGetShaderInfoLog(vShader, MAX_LOG_SIZE, NULL, log);
		std::cout << "Error loading Vertex shader" << log << std::endl;
		Sleep(5000);
		exit(0);
	}

	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &isSuccessful);
	if (!isSuccessful)
	{
		char log[MAX_LOG_SIZE];
		glGetShaderInfoLog(fShader, MAX_LOG_SIZE, NULL, log);
		std::cout << "Error loading Vertex shader" << log << std::endl;
		Sleep(5000);
		exit(0);
	}
}

bool Shaders::isLoaded()
{
	return mLoaded;
}

uint Shaders::getID()
{
	return mShader;
}

//SHADER PROGRAM

ShaderProgram::ShaderProgram() : isLinked(false)
{
}

void ShaderProgram::createProgram()
{
	mProgram = glCreateProgram();
}

bool ShaderProgram::addShader(Shaders* mShader)
{
	if (!mShader->isLoaded())
		return false;

	glAttachShader(mProgram, mShader->getID());
	return true;
}

bool ShaderProgram::linkProgram()
{
	glLinkProgram(mProgram);
	GLint linkStatus;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &linkStatus);
	isLinked = linkStatus == GL_TRUE;
	return isLinked;
}

void ShaderProgram::deleteProgram()
{
	if (!isLinked)
		return;
	isLinked = false;
	glDeleteProgram(mProgram);
}

void ShaderProgram::useProgram()
{
	if (isLinked)
		glUseProgram(mProgram);
}

uint ShaderProgram::getProgramID()
{
	return mProgram;
}

// Setting floats

void ShaderProgram::setUniform(std::string sName, float* fValues, int iCount)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform1fv(iLoc, iCount, fValues);
}

void ShaderProgram::setUniform(std::string sName, const float fValue)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform1fv(iLoc, 1, &fValue);
}

// Setting vectors

void ShaderProgram::setUniform(std::string sName, glm::vec2* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform2fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(std::string sName, const glm::vec2 vVector)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform2fv(iLoc, 1, (GLfloat*)&vVector);
}

void ShaderProgram::setUniform(std::string sName, glm::vec3* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform3fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(std::string sName, const glm::vec3 vVector)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform3fv(iLoc, 1, (GLfloat*)&vVector);
}

void ShaderProgram::setUniform(std::string sName, glm::vec4* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform4fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(std::string sName, const glm::vec4 vVector)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform4fv(iLoc, 1, (GLfloat*)&vVector);
}

// Setting 3x3 matrices

void ShaderProgram::setUniform(std::string sName, glm::mat3* mMatrices, int iCount)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniformMatrix3fv(iLoc, iCount, FALSE, (GLfloat*)mMatrices);
}

void ShaderProgram::setUniform(std::string sName, const glm::mat3 mMatrix)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniformMatrix3fv(iLoc, 1, FALSE, (GLfloat*)&mMatrix);
}

// Setting 4x4 matrices

void ShaderProgram::setUniform(std::string sName, glm::mat4* mMatrices, int iCount)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniformMatrix4fv(iLoc, iCount, FALSE, (GLfloat*)mMatrices);
}

void ShaderProgram::setUniform(std::string sName, const glm::mat4 mMatrix)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniformMatrix4fv(iLoc, 1, FALSE, (GLfloat*)&mMatrix);
}

// Setting integers

void ShaderProgram::setUniform(std::string sName, int* iValues, int iCount)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform1iv(iLoc, iCount, iValues);
}

void ShaderProgram::setUniform(std::string sName, const int iValue)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform1i(iLoc, iValue);
}

void ShaderProgram::setUniform(std::string sName, GLuint iValue)
{
	int iLoc = glGetUniformLocation(mProgram, sName.c_str());
	glUniform1i(iLoc, iValue);
}
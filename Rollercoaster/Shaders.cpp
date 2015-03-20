#include "Shaders.h"

Shaders::Shaders() : vShader(0), fShader(0), needsValidating(GL_TRUE), UniformLocations(0), AttribLocations(0)
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
	
	GLuint Shader = glCreateShader(type);

	glShaderSource(Shader, 1, (const char**)&shaderText, NULL);
	delete[] shaderText;
	glCompileShader(Shader);

	GLint status;
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		char log[MAX_LOG_SIZE];
		glGetShaderInfoLog(fShader, MAX_LOG_SIZE, NULL, log);
		std::cout << "Error loading shader" << log << std::endl;
		glDeleteShader(Shader);
		return 0;
	}

	return Shader;
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
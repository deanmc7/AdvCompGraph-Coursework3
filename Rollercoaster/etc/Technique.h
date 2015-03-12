#ifndef __Technique_h_
#define __Technique_h_

#include <list>
#include <GL/glew.h>
#include <GL\freeglut.h>
#include "Utility.h"

class Technique
{
private:
	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_shaderObjList;

protected:
	bool AddShader(GLenum ShaderType, const char* pFilename);

	bool Finalize();

	GLint GetUniformLocation(const char* pUniformName);

	GLint GetProgramParam(GLint param);

	GLuint m_shaderProg;

public:
	Technique();

	virtual ~Technique();

	virtual bool Init();

	void Enable();
};

#endif //#ifndef __Technique_h_
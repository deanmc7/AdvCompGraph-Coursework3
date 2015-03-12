#ifndef __SkyboxTech_h_
#define __SkyboxTech_h_

#include <GL\glew.h>
#include <Gl\freeglut.h>

#include "3dMath.h"
#include "Technique.h"
#include "Utility.h"

class SkyboxTech : public Technique
{
private:
	GLuint m_WVPLocation;
	GLuint m_textureLocation;

public:
	SkyboxTech();

	virtual bool Init();

	void SetWVP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
};

#endif //#ifndef __SkyboxTech_h_
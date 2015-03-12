#include "SkyboxTech.h"

SkyboxTech::SkyboxTech()
{

}

bool SkyboxTech::Init()
{
	if (!Technique::Init())
		return false;

	if (!AddShader(GL_VERTEX_SHADER, "skybox.vs")) {
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "skybox.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	m_textureLocation = GetUniformLocation("gCubemapTexture");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_textureLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}
}

void SkyboxTech::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}


void SkyboxTech::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}
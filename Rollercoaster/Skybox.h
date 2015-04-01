#ifndef __Skybox_h_
#define __Skybox_h_

#include "Camera.h"
#include "TGAloader.h"
#include "Textures.h"
#include "Shaders.h"

class Skybox
{
private:
	Camera* pCamera;
	Shaders mSkyboxShader;
	ShaderProgram	mProgram;
	GLuint vbo, vao, tex_cube;
	Textures* pTexture;

public:
	Skybox(Camera* pCam, Textures* texture);

	void Init();
	void Render(Textures* texture);
	void createCubeMap(GLuint* tex_cube);
	bool LoadSide(GLuint texture, GLenum side_target, int fileName);

	GLuint getCubeMap();
};

#endif //#ifndef __Skybox_h_
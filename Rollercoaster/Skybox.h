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
	GLuint vbo, vao;

public:
	Skybox(Camera* pCam);

	void Init();
	void Render(Textures* texture);
};

#endif //#ifndef __Skybox_h_
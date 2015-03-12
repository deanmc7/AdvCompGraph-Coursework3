#ifndef __Skybox_h_
#define __Skybox_h_

#include "Camera.h"
#include "TGAloader.h"

#define SKYBOX_TOP		0
#define SKYBOX_FRONT	1
#define SKYBOX_LEFT		2
#define SKYBOX_RIGHT	3
#define SKYBOX_BACK		4

class Skybox
{
private:
	GLuint textures[5];
	Camera* pCamera;
	char* textureFilenames[5];
public:
	Skybox(Camera* pCam);

	bool loadImage(char* textureName, int currentTexture);

	void loadTextures(void);

	void Render(void);
};

#endif //#ifndef __Skybox_h_
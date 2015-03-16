#ifndef __Textures_h_
#define __Textures_h_

#include "Utility.h"
#include "TGAloader.h"

class Textures
{
private:
	GLuint textures[NUM_OF_TEXTURES];
	char* textureFilenames[NUM_OF_TEXTURES];

	bool loadImage(char* textureName, int currentTexture);

public:

	Textures(void);

	void loadTextures(void);

	GLuint getTexture(int texture);
};

#endif //#ifndef __Textures_h_
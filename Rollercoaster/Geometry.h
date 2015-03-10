#ifndef __Geometry_h_
#define __Geometry_h_

#include <GL\freeglut.h>

#include "TGAloader.h"

#define NUM_OF_TEXTURES 2
#define FLOOR_TEXTURE 0
#define TRACK_TEXTURE 1

class Geometry
{
private:

	GLuint textures[NUM_OF_TEXTURES];
	GLuint sphere, track;
	GLfloat	trackHeight;
	GLfloat trackInnerRadius;
	GLfloat trackOuterRadius;
	int numOfHills;

	char* textureFilenames[NUM_OF_TEXTURES];

	bool loadImage(char* textureName, int currentTexture);

public:
	Geometry(void);

	void loadTextures(void);

	void buildTrack(void);

	void drawTrack(void);
	void drawFloor(void);
};

#endif //#ifndef __Geometry_h_
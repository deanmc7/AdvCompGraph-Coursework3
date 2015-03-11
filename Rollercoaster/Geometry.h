#ifndef __Geometry_h_
#define __Geometry_h_

#include <GL\freeglut.h>

#include "TGAloader.h"

#define NUM_OF_TEXTURES 4
#define FLOOR_TEXTURE 0
#define TRACK_TEXTURE 1
#define WATER_TEXTURE 2
#define CONCRETE_TEXTURE 3

class Geometry
{
private:

	GLuint textures[NUM_OF_TEXTURES];
	GLuint sphere, track, trackFloor, pond;
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
	void buildTrackFloor(void);
	void buildPond(void);
	void buildPondBase(int a, int b, int c, int d);
	

	void drawTrack(void);
	void drawTrackFloor(void);
	void drawFloor(void);
	void drawPond(void);
	void drawPondBase(void);

	GLfloat getTrackHeight(void);
	GLfloat getTrackInnerRadius(void);
	GLfloat getTrackOuterRadius(void);
	int getNumOfHills(void);
};

#endif //#ifndef __Geometry_h_
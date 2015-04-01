#ifndef __Track_h_
#define __Track_h_

#include "Utility.h"
#include "TGAloader.h"
#include "Textures.h"

class Track
{
private:
	GLuint sphere, track, trackFloor, column;
	GLfloat	trackHeight;
	GLfloat trackInnerRadius;
	GLfloat trackOuterRadius;
	int numOfHills;
public:
	Track(void);

	void buildTrack(void);
	void buildTrackFloor(Textures* texture);

	void drawTrack(void);

	GLfloat getTrackHeight(void);
	GLfloat getTrackInnerRadius(void);
	GLfloat getTrackOuterRadius(void);
	int getNumOfHills(void);
};

#endif //#ifndef __Track_h_
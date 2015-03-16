#ifndef __rPhysics_h_
#define __rPhysics_h_

#include "Utility.h"

class rPhysics
{
private:
	GLfloat tHeight;
	GLfloat tInnerRad, tOuterRad;
	GLfloat gravity;
	int tHills;
public:
	rPhysics(GLfloat trackHeight, GLfloat trackInnerRadius, GLfloat trackOuterRadius, int numOfHills, GLfloat grav);

	GLfloat ODE(float speed, float pos);
	GLfloat RK4(float speed, float pos);
	GLfloat Euler(float speed, float pos);
};

#endif //#ifndef __rPhysics_h_
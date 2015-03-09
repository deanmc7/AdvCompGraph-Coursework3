#ifndef __rPhysics_h_
#define __rPhysics_h_

#include <GL\freeglut.h>
#include <math.h>

class rPhysics
{
private:
	GLfloat tHeight;
	GLfloat tRad;
	GLfloat gravity;
	int tHills;
public:
	rPhysics(GLfloat trackHeight, GLfloat trackRadius, int numOfHills, GLfloat grav);

	GLfloat ODE(float speed, float pos);
	GLfloat RK4(float speed, float pos);
	GLfloat Euler(float speed, float pos);
};

#endif //#ifndef __rPhysics_h_
#ifndef __Camera_h_
#define __Camera_h_

#include <GL\freeglut.h>
#include <math.h>

#include "Keys.h"

#define PI 3.1415926532L

class Camera
{
private:
	double camX, camY, camZ;
	double camAngle;
public:
	Camera();
	Camera(double x, double y, double z, double angle);
	
	void Init();
	
	bool KeyInput(KEY key);
	void SpecialKeyInput(int key, int x, int y);

	double getX();
	double getY();
	double getZ();
	double getAngle();
};

#endif //#ifndef __Camera_h_
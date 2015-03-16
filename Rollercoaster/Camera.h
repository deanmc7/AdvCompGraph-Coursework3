#ifndef __Camera_h_
#define __Camera_h_

#include "Utility.h"
#include "Keys.h"

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

	vec3 position;
};

#endif //#ifndef __Camera_h_
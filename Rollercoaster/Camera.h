#ifndef __Camera_h_
#define __Camera_h_

#include "Utility.h"
#include "Car.h"
#include "Keys.h"

class Camera
{
private:
	double camX, camY, camZ;
	double startX, startY, startZ;
	vec3 startPos;
	double camAngle;
	int follow;
public:
	Camera();
	Camera(double x, double y, double z, double angle);
	
	void Init();
	
	bool KeyInput(KEY key);
	void SpecialKeyInput(int key, int x, int y);
	void KeyInput(unsigned char key, int x, int y);
	void setFollow(int carNum);
	int getFollow();
	void followCart(Car* cart);
	void ResetPos();

	double getX();
	double getY();
	double getZ();
	double getAngle();

	vec3 position;
};

#endif //#ifndef __Camera_h_
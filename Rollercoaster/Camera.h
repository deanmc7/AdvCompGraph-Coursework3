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
	double camAngle;
	int follow;

	glm::vec3 position;
	glm::vec3 startPos;
	glm::vec3 camView;
	glm::vec3 camUp;
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
	glm::vec3 getPos();
	double getAngle();
	glm::mat4 getLook();

};

#endif //#ifndef __Camera_h_
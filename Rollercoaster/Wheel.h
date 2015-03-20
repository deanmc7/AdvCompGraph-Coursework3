#ifndef __Wheel_h_
#define __Wheel_h_

#include "rPhysics.h"
#include "Utility.h"
#include "Mesh.h"
#include "Textures.h"
#include "Car.h"

class Wheel
{
private:
	rPhysics* physics;

	Mesh* meshLoader;
	int wheelMesh;

	GLfloat wRadius;
	float rad_to_deg;

	//TO BE USED FOR WHEEL ROTATION
	double CAR_WHEEL_RADIUS;
	float wheelCircumference;
	float percentage;
	GLfloat	wheel_rotation;
	float arcLength;   // used to calculate the Wheel rotation
public:
	Wheel();

	void BuildWheel(void);

	void RenderWheel(void);

	void Update(double x, double y, double z, double offsetX, double offsetY, double offsetZ, GLfloat thetaPos, int hills, GLfloat tHeight);
};

#endif //#ifndef __Wheel_h_
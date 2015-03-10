#ifndef __Car_h_
#define __Car_h_

#include <GL\freeglut.h>
#include <math.h>

#include "rPhysics.h"

#define M_PI       3.14159265358979323846

class Car
{
private:
	rPhysics* physics;

	GLuint cars;

	GLfloat timeStep;
	GLfloat thetaPos, thetaVel, thetaAccel;
	GLfloat tInnerRadius, tOuterRadius, tHeight;
	GLfloat grav;
	int tHills;
	double carX, carY, carZ;
	GLfloat cRadius;

	float rad_to_deg;

	//TO BE USED FOR WHEEL ROTATION
	double CAR_WHEEL_RADIUS;
	float wheelCircumference;
	float percentage;
	GLfloat	wheel_rotation;
	float arcLength;   // used to calculate the Wheel rotation
public:
	Car(GLfloat carRadius, GLfloat time_step, GLfloat trackInnerRadius, GLfloat trackOuterRadius, GLfloat trackHeight, GLfloat gravity, int numOfHills);

	~Car(void);

	void BuildCar(void);

	void RenderCar(void);

	void Init(void);

	void CalculatePos(float& position, float& velocity, float& acceleration);

	void Display(double x, double y, double z);

	double getCarX(void);
	double getCarY(void);
	double getCarZ(void);
};

#endif //#ifndef __Car_h_
#include "Car.h"

Car::Car(GLfloat carRadius, GLfloat time_step, GLfloat trackRadius, GLfloat trackHeight, GLfloat gravity, int numOfHills)
	: cRadius(carRadius), timeStep(time_step), tHeight(trackHeight), tRadius(trackRadius), grav(gravity), tHills(numOfHills)
{
	physics = new rPhysics(tHeight, tRadius, tHills, grav);

	thetaPos	= timeStep;
	thetaVel	= timeStep * 400;
	thetaAccel	= timeStep * 40;

	arcLength = 0.0;
	wheel_rotation = 0.0;
	rad_to_deg = 57.2957795;
}

Car::~Car()
{

}

void Car::Init()
{
	CalculatePos(thetaPos, thetaVel, thetaAccel);
	carX = (tRadius * cos(thetaPos));
	carY = tHeight* sin(tHills * thetaPos) + cRadius;
	carZ = (tRadius * sin(thetaPos));
}

void Car::CalculatePos(float& position, float& velocity, float& acceleration)
{
	float speed, pos;

	if (acceleration <= timeStep)
	{
		velocity		= timeStep * 400;
		acceleration	= timeStep * 40;
	}

	acceleration = physics->RK4(velocity, position);
	//acceleration = physics->Euler(velocity, position);

	speed	= velocity + timeStep*(acceleration);
	pos		= position + timeStep*(velocity);

	position = pos;
	velocity = speed;
}

void Car::Display(double x, double y, double z)
{
	this->Init();
	glPushMatrix();
		glTranslatef(x, y, z);
		glColor3f(1.0, 1.0, 0.0);
		glRotatef((-thetaPos*rad_to_deg) - 90, 0, 1, 0);
		glRotatef((cos(tHills*thetaPos)*10.0f), 0.0, 0.0, 1.0);
		CAR_WHEEL_RADIUS = cRadius;  //WILL HAVE TO BE CHANGE WHEN YOU USE YOUR OWN TRAIN AND WHEELS
		// Calculate the arclength distance covered for the change in theta
		arcLength = ((tHeight * tHills * cos(tHills * thetaPos)) * (tHeight * tHills * cos(tHills * thetaPos))) + 1.0f;
		// The arclength calculation is an integration, therefore we must
		// sum this bit with all the previous arcLengths
		arcLength += sqrt(arcLength); //DISTANCE TRAVELLED ON CURVE BETWEEN TO FRAME
		// We must now divide by the wheel circumference
		wheelCircumference = 2.0f * M_PI * CAR_WHEEL_RADIUS; //WHEEL CIRCUMFERENCE
		percentage = arcLength / wheelCircumference; //PERCENTAGE OF DISTANCE TRAVELLED BETWEEN FRAMES
		// Multiplying the percentage by 360.0 gives us the amount to
		// turn the wheels by
		wheel_rotation = -percentage * 360.0f;  //WHEEL ROTATION ANGLE
		glRotatef(wheel_rotation, 0.0, 0.0, 1.0); //Apply wheel rotation
		glutWireTorus(cRadius / 2, cRadius, 50, 100);
	glPopMatrix();
}

double Car::getCarX()
{
	return carX;
}

double Car::getCarY()
{
	return carY;
}

double Car::getCarZ()
{
	return carZ;
}
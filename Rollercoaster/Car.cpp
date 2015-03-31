#include "Car.h"

Car::Car(GLfloat trackOffset, GLfloat time_step, GLfloat trackInnerRadius, GLfloat trackOuterRadius,
	GLfloat trackHeight, GLfloat gravity, int numOfHills, GLfloat offset, GLfloat speed, Textures* mTexture)
	: heightOffset(trackOffset), timeStep(time_step), tHeight(trackHeight), tInnerRadius(trackInnerRadius),
	tOuterRadius(trackOuterRadius), grav(gravity), tHills(numOfHills), carSpeed(speed), carMesh(0)
{
	physics = new rPhysics(tHeight, tInnerRadius, tOuterRadius, tHills, grav);
	texture = mTexture;
	meshLoader = new Mesh();
	wheelFL = new Wheel();
	wheelFR = new Wheel();
	wheelRL = new Wheel();
	wheelRR = new Wheel();

	thetaPos	= timeStep * offset;
	thetaVel	= timeStep * carSpeed;
	thetaAccel	= timeStep * 40;

	arcLength = 0.0;
	wheel_rotation = 0.0;
	rad_to_deg = 57.2957795;
}

Car::~Car()
{

}

void Car::BuildCar()
{
	carMesh = meshLoader->Load("cart.obj");
}

void Car::BuildWheel()
{
	wheelFL->BuildWheel();
	wheelFR->BuildWheel();
	wheelRL->BuildWheel();
	wheelRR->BuildWheel();
}

void Car::RenderCar()
{
	glCallList(carMesh);
}

void Car::Init()
{
	carX = ((tInnerRadius + tOuterRadius) / 2) * cos(thetaPos);
	carY = tHeight * sin(tHills * thetaPos) + heightOffset;
	carZ = ((tInnerRadius + tOuterRadius) / 2) * sin(thetaPos);
}

void Car::CalculatePos(float& position, float& velocity, float& acceleration)
{
	float speed, pos;

	if (acceleration <= timeStep)
	{
		velocity		= timeStep * carSpeed;
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
	CalculatePos(thetaPos, thetaVel, thetaAccel);
	this->Init();
	glPushMatrix();
		glTranslatef(x, y, z);
		yaw = (-thetaPos*rad_to_deg) - 90;
		pitch = (cos(tHills*thetaPos)*29.5f);
		glRotatef(yaw, 0, 1, 0);
		glRotatef(pitch , 0.0, 0.0, 1.0);
		this->RenderCar();
		wheelFL->Update(x, y, z, 9.054f, 2.511f, 7.286f, thetaPos, tHills, tHeight);
		wheelRL->Update(x, y, z, -4.692f, 2.511f, 7.286f, thetaPos, tHills, tHeight);
		wheelFR->Update(x, y, z, 9.054f, 2.511f, -7.505f, thetaPos, tHills, tHeight);
		wheelRR->Update(x, y, z, -4.659f, 2.511f, -7.505f, thetaPos, tHills, tHeight);
	glPopMatrix();
}

void Car::swapSpeeds(GLfloat& car1Speed, GLfloat& car2Speed)
{
	GLfloat temp;
	temp = car1Speed;
	car1Speed = car2Speed;
	car2Speed = temp;
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

double Car::getRad()
{
	return heightOffset;
}

float Car::getYaw()
{
	return yaw;
}

void Car::setSpeed(GLfloat value)
{
	carSpeed = value;
}

GLfloat Car::getSpeed()
{
	return carSpeed;
}
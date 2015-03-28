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
	//mCarMesh->Display(vertices, vertexBuffer, uvBuffer, texture, CART_TEXTURE, normals, uvs);
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
	/*	glTranslatef(x, y, z);
		glColor3f(1.0, 1.0, 0.0);
		glRotatef((-thetaPos*rad_to_deg) - 90, 0, 1, 0);
		glRotatef((cos(tHills*thetaPos)*10.0f), 0.0, 0.0, 1.0);
		CAR_WHEEL_RADIUS = heightOffset;  //WILL HAVE TO BE CHANGE WHEN YOU USE YOUR OWN TRAIN AND WHEELS
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
		glutWireTorus(heightOffset / 2, heightOffset, 50, 100);*/
		glTranslatef(x, y, z);
		yaw = (-thetaPos*rad_to_deg) - 90;
		glRotatef(yaw, 0, 1, 0);
		glRotatef((cos(tHills*thetaPos)*25.0f), 0.0, 0.0, 1.0);
		this->RenderCar();
		wheelFL->Update(x, y, z, 9.054f, 2.511f, 7.286f, thetaPos, tHills, tHeight);
		//glTranslatef(-38.389f, 13.807f, 58.193f);
		wheelRL->Update(x, y, z, -4.692f, 2.511f, 7.286f, thetaPos, tHills, tHeight);
		//glTranslatef(78.249f, 13.807f, -58.081f);
		wheelFR->Update(x, y, z, 9.054f, 2.511f, -7.505f, thetaPos, tHills, tHeight);
		//glTranslatef(-40.153f, 13.807f, -58.094f);
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
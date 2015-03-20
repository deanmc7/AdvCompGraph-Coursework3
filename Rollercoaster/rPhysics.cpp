#include "rPhysics.h"

rPhysics::rPhysics(GLfloat trackHeight, GLfloat trackInnerRadius, GLfloat trackOuterRadius, int numOfHills, GLfloat grav)
	: tHeight(trackHeight), tInnerRad(trackInnerRadius), tOuterRad(trackOuterRadius), tHills(numOfHills), gravity(grav)
{

}

GLfloat rPhysics::ODE(float speed, float pos)
{
	int	n = tHills;
	GLfloat R = tInnerRad + tOuterRad / 2;
	GLfloat H = tHeight;
	GLfloat g = gravity;

	GLfloat numerator	= (float)(((n*n*n)*(H*H)*(speed * speed)*sin(n*pos) - n*g*H)*cos(n*pos));
	GLfloat denominator = (float)((R*R) + (n*n)*(H*H)*((cos(n*pos))*(cos(n*pos))));
	std::cout << numerator << std::endl << denominator << std::endl;
	return (numerator / denominator);
}

GLfloat rPhysics::RK4(float speed, float pos)
{
	float k1, k2, k3, k4;
	float j1, j2, j3;
	float acceleration;

	k1 = ODE(speed, pos);
	j1 = speed + k1;

	k2 = ODE(speed + k1 / 2, pos + j1 / 2);
	j2 = speed + k2;

	k3 = ODE(speed + k2 / 2, pos + j2 / 2);
	j3 = speed + k3;

	k4 = ODE(speed + k3, pos + speed + k3);

	acceleration = (1 / 6) * (k1 + (2 * k2) + (2 * k3) + k4);

	return (acceleration);
}

GLfloat rPhysics::Euler(float speed, float pos)
{
	float k1;
	float acceleration;

	k1 = ODE(speed, pos);

	acceleration = k1;

	return (acceleration);
}
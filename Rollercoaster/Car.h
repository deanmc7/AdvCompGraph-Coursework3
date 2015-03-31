#ifndef __Car_h_
#define __Car_h_

#include "rPhysics.h"
#include "Utility.h"
#include "Mesh.h"
#include "Textures.h"
#include "Wheel.h"

class Wheel;

class Car
{
private:
	rPhysics* physics;
	Textures* texture;
	Wheel* wheelFL;
	Wheel* wheelFR;
	Wheel* wheelRL;
	Wheel* wheelRR;
	Mesh* meshLoader;
	std::vector<glm::vec4> vertices;
	std::vector<vec3> normals;
	std::vector<vec2> uvs;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLfloat yaw;
	GLfloat pitch;

	int carMesh;

	GLfloat timeStep;
	GLfloat thetaPos, thetaVel, thetaAccel;
	GLfloat tInnerRadius, tOuterRadius, tHeight;
	GLfloat grav;
	GLfloat carSpeed;
	int tHills;
	double carX, carY, carZ;
	GLfloat heightOffset;

	float rad_to_deg;

	//TO BE USED FOR WHEEL ROTATION
	double CAR_WHEEL_RADIUS;
	float wheelCircumference;
	float percentage;
	GLfloat	wheel_rotation;
	float arcLength;   // used to calculate the Wheel rotation
public:
	Car(GLfloat trackOffset, GLfloat time_step, GLfloat trackInnerRadius, GLfloat trackOuterRadius, GLfloat trackHeight,
		GLfloat gravity, int numOfHills, GLfloat offset, GLfloat speed, Textures* mTexture);

	~Car();

	void BuildCar();
	void BuildWheel();

	void RenderCar();

	void Init();

	void CalculatePos(float& position, float& velocity, float& acceleration);

	void Display(double x, double y, double z);

	void swapSpeeds(GLfloat& car1Speed, GLfloat& car2Speed);

	double getCarX();
	double getCarY();
	double getCarZ();
	double getRad();
	float getYaw();
	void setSpeed(GLfloat value);
	GLfloat getSpeed();
};

#endif //#ifndef __Car_h_
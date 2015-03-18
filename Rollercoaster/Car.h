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

	int carMesh;

	GLfloat timeStep;
	GLfloat thetaPos, thetaVel, thetaAccel;
	GLfloat tInnerRadius, tOuterRadius, tHeight;
	GLfloat grav;
	GLfloat carSpeed;
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
	Car(GLfloat carRadius, GLfloat time_step, GLfloat trackInnerRadius, GLfloat trackOuterRadius, GLfloat trackHeight, 
		GLfloat gravity, int numOfHills, GLfloat offset, GLfloat speed, Textures* mTexture);

	~Car(void);

	void BuildCar(void);
	void BuildWheel(void);

	void RenderCar(void);

	void Init(void);

	void CalculatePos(float& position, float& velocity, float& acceleration);

	void Display(double x, double y, double z);

	void swapSpeeds(GLfloat& car1Speed, GLfloat& car2Speed);

	double getCarX(void);
	double getCarY(void);
	double getCarZ(void);
	double getRad(void);
	void setSpeed(GLfloat value);
	GLfloat getSpeed(void);
};

#endif //#ifndef __Car_h_
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
	Textures* texture;

	Mesh* meshLoader;
	int wheelMesh;
	std::vector<glm::vec4> vertices;
	std::vector<vec3> normals;
	std::vector<vec2> uvs;
	GLuint vertexBuffer;
	GLuint uvBuffer;

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
	Wheel(Textures* mTexture);

	int BuildWheel(void);

	void RenderWheel();

	void Update(double x, double y, double z, double offsetX, double offsetY, double offsetZ, GLfloat thetaPos, int hills, GLfloat tHeight);
};

#endif //#ifndef __Wheel_h_
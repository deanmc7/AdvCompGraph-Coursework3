#include "Wheel.h"

Wheel::Wheel(Textures* mTexture) : wheelMesh(0)
{
	texture = mTexture;
	meshLoader = new Mesh();

	arcLength = 0.0;
	wheel_rotation = 0.0;
	rad_to_deg = 57.2957795;

	this->BuildWheel();
}

int Wheel::BuildWheel(void)
{
	//mWheelMesh->Load(vertices, normals, uvs);
	//mWheelMesh->InitShader();
	return wheelMesh = meshLoader->Load("wheel.obj");
}

void Wheel::RenderWheel()
{
		//glTranslatef(x, y, z);
	//mWheelMesh->Display(vertices, vertexBuffer, uvBuffer, texture, CART_TEXTURE, normals, uvs);
	glCallList(wheelMesh);
}

void Wheel::Update(double x, double y, double z, double offsetX, double offsetY, double offsetZ, GLfloat thetaPos, int hills, GLfloat tHeight)
{
	glPushMatrix();
		glTranslatef(offsetX, offsetY, offsetZ);
		//glTranslatef(x, y, z);
		//glRotatef((-thetaPos*rad_to_deg) - 90, 0, 1, 0);
		//glRotatef((cos(hills*thetaPos)*10.0f), 0.0, 0.0, 1.0);
		CAR_WHEEL_RADIUS = cRadius;  //WILL HAVE TO BE CHANGE WHEN YOU USE YOUR OWN TRAIN AND WHEELS
		// Calculate the arclength distance covered for the change in theta
		arcLength = ((tHeight * hills * cos(hills * thetaPos)) * (tHeight * hills * cos(hills * thetaPos))) + 1.0f;
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
		RenderWheel();
	glPopMatrix();
}
#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(double x, double y, double z, double angle) 
	: camX(x), camY(y), camZ(z), camAngle(angle)
{

}

void Camera::Init()
{

}

bool Camera::KeyInput(KEY key)
{
	bool out = false;

	/* switch control structure */
	switch (key)
	{
		/* when the up-arrow on the keyboard is pressed */
	case KEY_UP:
	{
		double rads = camAngle / 180.0L * PI;
		/* the smaller the number divided by the faster you glide forward */
		double dx = -sin(rads) / 0.1;// 1.5;
		/* the smaller the number divided by the faster you glide forward */
		double dz = cos(rads) / 0.1;// 1.5;

		camX += dx;
		camZ += dz;

		out = true;
	}
		break;

		/* when the back-arrow on the keyboard is pressed */
	case KEY_DOWN:
	{
		double rads = camAngle / 180.0L * PI;
		/* the smaller the number divided by the faster you glide forward */
		double dx = -sin(rads) / 0.1; //3.0;
		/* the smaller the number divided by the faster you glide forward */
		double dz = cos(rads) / 0.1;// 3.0;

		camX -= dx;
		camZ -= dz;

		out = true;
	}
		break;

		/* when the right-arrow on the keyboard is pressed */
	case KEY_RIGHT:
		camAngle += 5;
		out = true;
		break;

		/* when the left-arrow on the keyboard is pressed */
	case KEY_LEFT:
		camAngle -= 5;
		out = true;
		break;

		/* when anything else is pressed */
	default:
		break;
	}

	return out;
}

void Camera::SpecialKeyInput(int key, int x, int y)
{
	/* switch control structure */
	switch (key)
	{
		/* when the up-arrow on the keyboard is pressed */
	case GLUT_KEY_UP:
	{
		double rads = camAngle / 180.0L * PI;
		/* the smaller the number divided by the faster you glide forward */
		double dx = -sin(rads) / 0.1;// 1.5;
		/* the smaller the number divided by the faster you glide forward */
		double dz = cos(rads) / 0.1;// 1.5;

		camX += dx;
		camZ += dz;
	}
		break;

		/* when the back-arrow on the keyboard is pressed */
	case GLUT_KEY_DOWN:
	{
		double rads = camAngle / 180.0L * PI;
		/* the smaller the number divided by the faster you glide forward */
		double dx = -sin(rads) / 0.1; //3.0;
		/* the smaller the number divided by the faster you glide forward */
		double dz = cos(rads) / 0.1;// 3.0;

		camX -= dx;
		camZ -= dz;
	}
		break;

		/* when the right-arrow on the keyboard is pressed */
	case GLUT_KEY_RIGHT:
		camAngle += 5;
		break;

		/* when the left-arrow on the keyboard is pressed */
	case GLUT_KEY_LEFT:
		camAngle -= 5;
		break;

		/* when anything else is pressed */
	default:
		break;
	}
}

double Camera::getX()
{
	return camX;
}

double Camera::getY()
{
	return camY;
}

double Camera::getZ()
{
	return camZ;
}

double Camera::getAngle()
{
	return camAngle;
}
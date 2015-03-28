#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(double x, double y, double z, double angle) 
	: camX(x), camY(y), camZ(z), camAngle(angle), follow(0)
{
	position = vec3(camX, camY, camZ);
	startPos= vec3(camX, camY, camZ);
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
		double rads = camAngle / 180.0L * M_PI;
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
		double rads = camAngle / 180.0L * M_PI;
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
		double rads = camAngle / 180.0L * M_PI;
		/* the smaller the number divided by the faster you glide forward */
		double dx = -sin(rads) / 0.1;// 1.5;
		/* the smaller the number divided by the faster you glide forward */
		double dz = cos(rads) / 0.1;// 1.5;

		position.x += dx;
		position.z += dz;
	}
		break;

		/* when the back-arrow on the keyboard is pressed */
	case GLUT_KEY_DOWN:
	{
		double rads = camAngle / 180.0L * M_PI;
		/* the smaller the number divided by the faster you glide forward */
		double dx = -sin(rads) / 0.1; //3.0;
		/* the smaller the number divided by the faster you glide forward */
		double dz = cos(rads) / 0.1;// 3.0;

		position.x -= dx;
		position.z -= dz;
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

void Camera::KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		this->setFollow(1);
		break;
	case '2':
		this->setFollow(2);
		break;
	case '3':
		this->setFollow(3);
		break;
	case 'a':
		glTranslated(0.0, 0.0, 50.0);
		glutPostRedisplay();
		break;
	case 'z':
		glTranslated(0.0, 0.0, -50.0);
		glutPostRedisplay();
		break;
	case 'r':
	case 'R':
		this->setFollow(0);
		this->ResetPos();
		break;
	case '.':
		glRotated(10.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case',':
		glRotated(10.0, 0.0, -1.0, 0.0);
		glutPostRedisplay();
		break;
	}
}

void Camera::setFollow(int carNum)
{
	follow = carNum;
}

int Camera::getFollow()
{
	return follow;
}

void Camera::followCart(Car* cart)
{
	/*position.x = -cart->getCarX();
	position.y = -cart->getCarY();
	position.z = -cart->getCarZ();
	camAngle = -cart->getYaw();*/

	glLoadIdentity();
	position.x = cart->getCarX() + cos(90.0f) * (5.0f);
	position.y = 10.0f;
	position.z = cart->getCarZ() + cos(90.0f) * (5.0f);
	gluLookAt(position.x, position.y, position.z, -cart->getCarX(), -cart->getCarY(), -cart->getCarX(), 0.0, 1.0, 0.0);
}

void Camera::ResetPos()
{
	gluLookAt(startPos.x, startPos.y, startPos.z, -100.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

double Camera::getX()
{
	return position.x;
}

double Camera::getY()
{
	return position.y;
}

double Camera::getZ()
{
	return position.z;
}

double Camera::getAngle()
{
	return camAngle;
}
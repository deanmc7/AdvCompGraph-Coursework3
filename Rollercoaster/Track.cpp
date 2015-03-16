#include "Track.h"

Track::Track(void)
{
	this->trackHeight = 20.0f;
	this->trackInnerRadius = 90.0f;
	this->trackOuterRadius = 110.0f;
	this->numOfHills = 4;
}

void Track::buildTrack(void)
{
	double x = -3.14;

	this->sphere = glGenLists(1);
	this->track = glGenLists(2);

	glNewList(this->sphere, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(1, 20, 10);
	glEndList();

//	glNewList(this->track, GL_COMPILE);
		for (x; x < 3.14; x += 0.005)
		{
			glPushMatrix();

				glTranslatef(this->trackInnerRadius * cos(x), this->trackHeight * sin(numOfHills * x), this->trackInnerRadius * sin(x));

				glCallList(this->sphere);

			glPopMatrix();

			glPushMatrix();

				glTranslatef(this->trackOuterRadius * cos(x), this->trackHeight * sin(numOfHills * x), this->trackOuterRadius * sin(x));

				glCallList(this->sphere);

			glPopMatrix();
		}
	//glEndList();
}

void Track::buildTrackFloor(Textures* texture)
{
	double x = -3.14;

	for (x; x < 3.14; x += 0.005)
	{
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glPushMatrix();
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, texture->getTexture(TRACK_TEXTURE));

				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(trackInnerRadius*cos(x), trackHeight * sin(numOfHills*x), trackInnerRadius * sin(x));
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(trackOuterRadius*cos(x), trackHeight * sin(numOfHills*x), trackOuterRadius * sin(x));
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(trackInnerRadius*cos((x - 0.05)), trackHeight * sin(numOfHills*(x - 0.05)), trackInnerRadius * sin((x - 0.05)));
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(trackOuterRadius*cos((x - 0.05)), trackHeight * sin(numOfHills*(x - 0.05)), trackOuterRadius * sin((x - 0.05)));
			glPopMatrix();
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}

void Track::drawTrack(void)
{
	glCallList(this->track);
}

GLfloat Track::getTrackHeight(void)
{
	return this->trackHeight;
}

GLfloat Track::getTrackInnerRadius(void)
{
	return this->trackInnerRadius;
}

GLfloat Track::getTrackOuterRadius(void)
{
	return this->trackOuterRadius;
}

int Track::getNumOfHills(void)
{
	return this->numOfHills;
}
#include "Geometry.h"

Geometry::Geometry(void)
{
	this->trackHeight = 20.0f;
	this->trackInnerRadius = 90.0f;
	this->trackOuterRadius = 110.0f;
	this->numOfHills = 4;
	this->textureFilenames[0] = "grass.tga";
	this->textureFilenames[1] = "track.tga";
}

bool Geometry::loadImage(char* textureName, int currentTexture)
{
	/* image loading type */
	TGAloader Img;

	/* loads the texture */
	if (Img.Load(textureName) != IMG_OK)
		return false;

	/* the texture handle is set to the current loaded texture */
	glBindTexture(GL_TEXTURE_2D, this->textures[currentTexture]);

	/* setup the texture if it is a standard solid 24bit image (no transparency) */
	if (Img.GetBPP() == 24)
	{
		/* specifies the solid two-dimensional texture */
		glTexImage2D(GL_TEXTURE_2D, 0, 3, Img.GetWidth(), Img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, Img.GetImg());
	}
	/* else setup the texture if it is a 32bit image with an alpha channel */
	else if (Img.GetBPP() == 32)
	{
		/* specifies the transparent two-dimensional texture */
		glTexImage2D(GL_TEXTURE_2D, 0, 4, Img.GetWidth(), Img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Img.GetImg());
	}
	else
	{
		return false;
	}

	/* sets the texture parameters - for reference, consult Prog 8.6's discussion */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true;
}

void Geometry::loadTextures(void)
{
	/* deals with the generation of texture names  */
	glGenTextures(NUM_OF_TEXTURES, this->textures);

	for (int i = 0; i < NUM_OF_TEXTURES; i++)
	{
		loadImage(this->textureFilenames[i], i);
	}
}

void Geometry::buildTrack(void)
{
	double x = -3.14;

	this->sphere = glGenLists(1);
	this->track = glGenLists(2);

	glNewList(this->sphere, GL_COMPILE);
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(1, 20, 10);
	glEndList();

	glNewList(this->track, GL_COMPILE);
		for (x; x < 3.14; x += 0.005)
		{
			glColor3f(0.0, 1.0, 0.0);

			glPushMatrix();

				glTranslatef(this->trackInnerRadius * cos(x), this->trackHeight * sin(numOfHills * x), this->trackInnerRadius * sin(x));

				glCallList(this->sphere);

			glPopMatrix();

			glPushMatrix();

				glTranslatef(this->trackOuterRadius * cos(x), this->trackHeight * sin(numOfHills * x), this->trackOuterRadius * sin(x));

				glCallList(this->sphere);

			glPopMatrix();

			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

			glBindTexture(GL_TEXTURE_2D, this->textures[TRACK_TEXTURE]);

			glBegin(GL_QUADS);
				glPushMatrix();

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
	glEndList();
}

void Geometry::drawTrack(void)
{
	glCallList(this->track);
}

void Geometry::drawFloor(void)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, this->textures[FLOOR_TEXTURE]);
		glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-300.0, -20.0, -300.0);
			glTexCoord2f(0.0, 100.0);
			glVertex3f(-300.0, -20.0, 300.0);
			glTexCoord2f(100.0, 100.0); //the bigger the higher the resulution
			glVertex3f(300.0, -20.0, 300.0);
			glTexCoord2f(100.0, 0.0);
			glVertex3f(300.0, -20.0, -300.0);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
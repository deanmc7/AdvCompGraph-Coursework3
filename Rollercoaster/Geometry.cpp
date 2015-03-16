#include "Geometry.h"

Geometry::Geometry(void)
{
}

void Geometry::drawFloor(Textures* texture)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture->getTexture(FLOOR_TEXTURE));
		glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-300.0, -30.0, -300.0);
			glTexCoord2f(0.0, 100.0);
			glVertex3f(-300.0, -30.0, 300.0);
			glTexCoord2f(100.0, 100.0); //the bigger the higher the resulution
			glVertex3f(300.0, -30.0, 300.0);
			glTexCoord2f(100.0, 0.0);
			glVertex3f(300.0, -30.0, -300.0);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
#include "Skybox.h"

float points[] = {
	-100.0f, 100.0f, -100.0f,
	-100.0f, -100.0f, -100.0f,
	100.0f, -100.0f, -100.0f,
	100.0f, -100.0f, -100.0f,
	100.0f, 100.0f, -100.0f,
	-100.0f, 100.0f, -100.0f,

	-100.0f, -100.0f, 100.0f,
	-100.0f, -100.0f, -100.0f,
	-100.0f, 100.0f, -100.0f,
	-100.0f, 100.0f, -100.0f,
	-100.0f, 100.0f, 100.0f,
	-100.0f, -100.0f, 100.0f,

	100.0f, -100.0f, -100.0f,
	100.0f, -100.0f, 100.0f,
	100.0f, 100.0f, 100.0f,
	100.0f, 100.0f, 100.0f,
	100.0f, 100.0f, -100.0f,
	100.0f, -100.0f, -100.0f,

	-100.0f, -100.0f, 100.0f,
	-100.0f, 100.0f, 100.0f,
	100.0f, 100.0f, 100.0f,
	100.0f, 100.0f, 100.0f,
	100.0f, -100.0f, 100.0f,
	-100.0f, -100.0f, 100.0f,

	-100.0f, 100.0f, -100.0f,
	100.0f, 100.0f, -100.0f,
	100.0f, 100.0f, 100.0f,
	100.0f, 100.0f, 100.0f,
	-100.0f, 100.0f, 100.0f,
	-100.0f, 100.0f, -100.0f,

	-100.0f, -100.0f, -100.0f,
	-100.0f, -100.0f, 100.0f,
	100.0f, -100.0f, -100.0f,
	100.0f, -100.0f, -100.0f,
	-100.0f, -100.0f, 100.0f,
	100.0f, -100.0f, 100.0f
};

Skybox::Skybox(Camera* pCam, Textures* texture) : pCamera(pCam), pTexture(texture), tex_cube(0)
{
}

void Skybox::Init()
{
	/*
	if (!mSkyboxShader.Load("skybox.vs", "skybox.fs"))
	{
		std::cout << "error loading skybox shader\n";
		return;
	}

	mSkyboxShader.UniformLocations = new GLuint[1];
	mSkyboxShader.UniformLocations[0] = glGetUniformLocation(mSkyboxShader, "CameraPosition");*/
	/*mSkyboxShader.LoadShader("skybox.vs", GL_VERTEX_SHADER);
	mSkyboxShader.LoadShader("skybox.fs", GL_FRAGMENT_SHADER);

	mProgram.createProgram();
	mProgram.addShader(&mSkyboxShader);
	mProgram.linkProgram();*/
	
	/*GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);*/
}

void Skybox::Render(Textures* texture)
{
	glPushMatrix();
		
		glLoadIdentity();
		gluLookAt(0, 0, 0,
			pCamera->getX(), pCamera->getY(), pCamera->getZ(),
			0, 1, 0);
		glRotatef(pCamera->getAngle(), 0.0, 1.0, 0.0);

		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);

		glColor4f(1, 1, 1, 1);

		//mProgram.useProgram();
		//mProgram.setUniform("CameraPosition", pCamera->getPos());

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_FRONT));
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(200.0f, -200.0f, -200.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-200.0f, -200.0f, -200.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-200.0f, 200.0f, -200.0f);
			glTexCoord2f(0, 0);
			glVertex3f(200.0f, 200.0f, -200.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_LEFT));
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(200.0f, -200.0f, 200.0f);
			glTexCoord2f(1, 1);
			glVertex3f(200.0f, -200.0f, -200.0f);
			glTexCoord2f(1, 0);
			glVertex3f(200.0f, 200.0f, -200.0f);
			glTexCoord2f(0, 0);
			glVertex3f(200.0f, 200.0f, 200.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_BACK));
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(-200.0f, -200.0f, 200.0f);
			glTexCoord2f(1, 1);
			glVertex3f(200.0f, -200.0f, 200.0f);
			glTexCoord2f(1, 0);
			glVertex3f(200.0f, 200.0f, 200.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-200.0f, 200.0f, 200.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_RIGHT));
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(-200.0f, -200.0f, -200.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-200.0f, -200.0f, 200.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-200.0f, 200.0f, 200.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-200.0f, 200.0f, -200.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture->getTexture(SKYBOX_TOP));
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1);
			glVertex3f(-200.0f, 200.0f, -200.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-200.0f, 200.0f, 200.0f);
			glTexCoord2f(0, 0);
			glVertex3f(200.0f, 200.0f, 200.0f);
			glTexCoord2f(0, 1);
			glVertex3f(200.0f, 200.0f, -200.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		glPopAttrib();
		//glUseProgram(0);
	glPopMatrix();

	/*createCubeMap(&tex_cube);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);	*/
}

void Skybox::createCubeMap(GLuint* tex_cube) 
{
	// generate a cube-map texture to hold all the sides
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);

	// load each image and copy into a side of the cube-map texture
	assert(
		LoadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, SKYBOX_FRONT));
	assert(
		LoadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, SKYBOX_BACK));
	assert(
		LoadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, SKYBOX_TOP));
	/*assert(
		LoadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom));*/
	assert(
		LoadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, SKYBOX_LEFT));
	assert(
		LoadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, SKYBOX_RIGHT));
	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool Skybox::LoadSide(GLuint texture, GLenum side_target, int fileName) 
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int x, y, n;
	int force_channels = 4;
	GLuint*  image_data = pTexture->getCubeTexture(fileName);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", fileName);
		return false;
	}
	// non-power-of-2 dimensions check
	/*if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf(
			stderr, "WARNING: image %s is not power-of-2 dimensions\n", fileName
			);
	}*/

	// copy image data into 'target' side of cube map
	glTexImage2D(
		side_target,
		0,
		GL_RGB32UI,
		512,
		512,
		0,
		GL_RGB,
		GL_UNSIGNED_INT,
		image_data
		);
	return true;
}

GLuint Skybox::getCubeMap()
{
	return tex_cube;
}
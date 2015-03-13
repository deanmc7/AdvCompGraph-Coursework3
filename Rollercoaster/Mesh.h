#ifndef __Mesh_h_
#define __Mesh_h_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <GL\glew.h>
#include <GL\glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL\freeglut.h>

class Mesh
{
private:
	const char* pathway;
	GLuint vboVertices, vboNormals, iboElements;
	GLint attribute_v_coord;
	GLint attribute_v_normal;
	GLint uniform_m, uniform_v, uniform_p;
	GLint uniform_m_3x3_inv_transp, uniform_v_inv;
	glm::mat4 object2world;
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> elements;
public:
	Mesh(const char* pathway);

	bool Load(std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements);

	void Draw(void);

	void Upload(void);

	void DrawBoundingBox(void);
};

#endif //#ifndef __Mesh_h_
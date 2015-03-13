/*https://gitlab.com/wikibooks-opengl/modern-tutorials/blob/master/obj-viewer/obj-viewer.cpp*/
#include "Mesh.h"

Mesh::Mesh(const char* path) : pathway(path), vboVertices(0), vboNormals(0), iboElements(0), object2world(glm::mat4(1))
{
	this->attribute_v_coord = -1;
	this->attribute_v_normal = -1;
	this->uniform_m = -1;
	this->uniform_v = -1;
	this->uniform_p = -1;
	this->uniform_m_3x3_inv_transp = -1; 
	this->uniform_v_inv = -1;
}

bool Mesh::Load(std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<int> &elements)
{
	std::ifstream in(pathway, std::ios::in);
	if (!in)
	{
		std::cerr << "Failed to open " << pathway << std::endl;
		exit(1);
	}

	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream s(line.substr(2));
			glm::vec4 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;
			v.w = 1.0f;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a;
			s >> b;
			s >> c;
			a--;
			b--;
			c--;
			elements.push_back(a);
			elements.push_back(b);
			elements.push_back(c);
		}
		else if (line[0] == '#')
		{
			/*Ignore*/
		}
		else
		{
			/*Ignore*/
		}
	}
}

void Mesh::Draw(void)
{
	this->Load(vertices, normals, elements);
	glBegin(GL_QUADS);
	for (int i = 0; i < vertices.size(); i++)
	{
		glVertex3f(vertices.at(elements[i]).x, vertices.at(elements[i]).y, vertices.at(elements[i]).z);
	}
	glEnd();
}
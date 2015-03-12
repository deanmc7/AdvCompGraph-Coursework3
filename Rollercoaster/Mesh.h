#ifndef __Mesh_h_
#define __Mesh_h_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm\glm.hpp>

class Mesh
{
private:
	const char* path;
public:
	Mesh(const char* pathway);

	bool Load(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUvs, std::vector<glm::vec3>& outNormals);
};

#endif //#ifndef __Mesh_h_
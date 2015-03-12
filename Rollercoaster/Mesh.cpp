#include "Mesh.h"

bool Mesh::Load(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUvs, std::vector<glm::vec3>& outNormals)
{
	std::ifstream in(path, std::ios::in);
	if (!in)
	{
		std::cerr << "Failed to open " << path << std::endl;
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
			ver
		}
	}
}
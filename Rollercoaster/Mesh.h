#ifndef __Mesh_h_
#define __Mesh_h_

#include "Utility.h"
#include "Textures.h"
#include "Shaders.h"

class Mesh
{
private:
	const char* pathway;
	Shaders		mMeshShader;

public:
	Mesh(const char* pathway);

	bool Load(std::vector<glm::vec4>& vertices, std::vector<vec3>& normals, std::vector<vec2>& uvs);

	void Draw(GLuint vertexBuffer, GLuint uvBuffer,
		std::vector<glm::vec4>& vertices, std::vector<vec3>& normals, std::vector<vec2>& uvs);

	void InitShader();

	void Display(std::vector<glm::vec4>& vertices, GLuint vertexBuffer, GLuint uvBuffer, Textures* texture, int textureName,
		std::vector<vec3>& normals, std::vector<vec2>& uvs);
};

#endif //#ifndef __Mesh_h_
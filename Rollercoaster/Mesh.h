#ifndef __Mesh_h_
#define __Mesh_h_

#include "Utility.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>


#include "Textures.h"
#include "Shaders.h"

struct coordinate{
	float x, y, z;
	coordinate(float a, float b, float c);
};


struct face{
	int facenum;
	bool four;
	int faces[4];
	int texcoord[4];
	int mat;
	face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m);
	face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m);
};


struct material{
	std::string name;
	float alpha, ns, ni;
	float dif[3], amb[3], spec[3];
	int illum;
	int texture;
	material(const char* na, float al, float n, float ni2, float* d, float* a, float* s, int i, int t);
};

struct texcoord{
	float u, v;
	texcoord(float a, float b);
};

class Mesh
{
private:
	std::vector<uint> vertexIndices, uvIndices, normalIndices;
	std::vector<coordinate*> temp_vertices;
	std::vector<texcoord*> temp_uvs;
	std::vector<coordinate*> temp_normals;
	std::vector<material*> temp_materials;
	std::vector<face*> temp_faces;
	std::vector<std::string*> line;
	std::vector<uint> lists;

	/*std::vector<std::string*> coord;
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;
	std::vector<unsigned int> texture;
	std::vector<unsigned int> lists;
	std::vector<material*> materials;
	std::vector<texcoord*> texturecoordinate;*/

	Shaders		mMeshShader;
	ILuint		devilError;

	std::vector<uint> texture;

	bool ismaterial, isnormals, istexture;

public:
	Mesh();

	int Load(const char* filename);

	void clean();

	uint loadTexture(const char* filename);

	void Draw(GLuint vertexBuffer, GLuint uvBuffer,
		std::vector<glm::vec4>& vertices, std::vector<vec3>& normals, std::vector<vec2>& uvs);

	void InitShader();

	void Display(std::vector<glm::vec4>& vertices, GLuint vertexBuffer, GLuint uvBuffer, Textures* texture, int textureName,
		std::vector<vec3>& normals, std::vector<vec2>& uvs);
};

#endif //#ifndef __Mesh_h_
/*https://gitlab.com/wikibooks-opengl/modern-tutorials/blob/master/obj-viewer/obj-viewer.cpp*/
#include "Mesh.h"

Mesh::Mesh(const char* path) : pathway(path)
{
}

bool Mesh::Load(std::vector<glm::vec4>& vertices, std::vector<vec3>& normals, std::vector<vec2>& uvs)
{
	/*std::ifstream in(pathway, std::ios::in);
	if (!in)
	{
		std::cerr << "Failed to open " << pathway << std::endl;
		exit(1);
	}

	std::string line;
	while (std::getline(in, line))
	{
		if (line.size() > 0)
		{
			if (line[0] == 'v')
			{
				std::istringstream s(line.substr(2));
				glm::glm::vec4 v;
				s >> v.x;
				s >> v.y;
				s >> v.z;
				v.w = 1.0f;
				vertices.push_back(v);
			}
			else if (line[0] == 'f')
			{

				std::stringstream s(line.substr(2));
				GLushort a, b, c, d;
				s >> a;
				s >> b;
				s >> c;
				s >> d;
				a--;
				b--;
				c--;
				d--;
				vertices_elements.push_back(a);
				vertices_elements.push_back(b);
				vertices_elements.push_back(c);
				vertices_elements.push_back(d);
			}
			else if (line[0] == 'vt')
			{
				std::istringstream s(line.substr(2));
				
			}
			else if (line[0] == 'vn')
			{

			}
			else if (line[0] == '#')
			{
				/*Ignore
			}
			else
			{
				/*Ignore
			}
		}
	}*/

	printf("Loading OBJ file....\n", pathway);

	std::vector<uint> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec4> temp_vertices;
	std::vector<vec2> temp_uvs;
	std::vector<vec3> temp_normals;

	FILE* file = fopen(pathway, "r");
	if (file == NULL)
	{
		printf("Error opening file\n");
		getchar();
		return false;
	}

	while (1)
	{
		char line[128];

		int in = fscanf(file, "%s", line);
		
		if (in == EOF)
			break;

		if (strcmp(line, "v") == 0)
		{
			glm::vec4 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex.w = 1.0f;
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(line, "vt") == 0)
		{
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(line, "vn") == 0)
		{
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(line, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			uint vertexIndex[4], uvIndex[4], normalIndex[4];
			GLint matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], 
				&vertexIndex[3], &uvIndex[3], &normalIndex[3]);
			if (matches != 12)
			{
				printf("Faces cannot be read!\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			vertexIndices.push_back(vertexIndex[3]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]); 
			uvIndices.push_back(uvIndex[3]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			normalIndices.push_back(normalIndex[3]);
		}
		else
		{
			char redundantBuffer[1024];
			fgets(redundantBuffer, 1024, file);
		}
	}

	for (uint i = 0; i < vertexIndices.size(); i++)
	{
		uint vIndex = vertexIndices[i];
		uint uvIndex = uvIndices[i];
		uint nIndex = normalIndices[i];

		glm::vec4 vertex = temp_vertices[vIndex - 1];
		vec2 uv = temp_uvs[uvIndex - 1];
		vec3 normal = temp_normals[nIndex - 1];

		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);
	}

	return true;
}

void Mesh::Draw(GLuint vertexBuffer, GLuint uvBuffer,
	std::vector<glm::vec4>& vertices, std::vector<vec3>& normals, std::vector<vec2>& uvs)
{
	/*glBegin(GL_QUADS);
	for (int i = 0; i < mVertices.size(); i++)
	{
		glVertex4f(mVertices.at(mElements[i]).x, mVertices.at(mElements[i]).y, mVertices.at(mElements[i]).z, mVertices.at(mElements[i]).w);
	}
	glEnd();*/

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
}

void Mesh::InitShader()
{
	if (!mMeshShader.Load("TransformVertexShader.vs", "TextureFragmentShader.fs"))
	{
		std::cout << "error loading Mesh shader\n";
		return;
	}

	mMeshShader.UniformLocations = new GLuint[2];
	mMeshShader.UniformLocations[0] = glGetUniformLocation(mMeshShader, "MVP");
	mMeshShader.UniformLocations[1] = glGetUniformLocation(mMeshShader, "myTextureSampler");
}

void Mesh::Display(std::vector<glm::vec4>& vertices, GLuint vertexBuffer, GLuint uvBuffer, Textures* texture, int textureName,
	std::vector<vec3>& normals, std::vector<vec2>& uvs)
{
	//glUseProgram(mMeshShader);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
	
	/*glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(mMeshShader.UniformLocations[0], 1, GL_FALSE, &MVP[0][0]);*/
	
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTexture(textureName));
	//glUniform1i(mMeshShader.UniformLocations[1], 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glDrawArrays(GL_QUADS, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisable(GL_TEXTURE_2D);
}
#include "Mesh.h"

coordinate::coordinate(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

face::face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m){
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	texcoord[0] = t1;
	texcoord[1] = t2;
	texcoord[2] = t3;
	mat = m;
	four = false;
}

face::face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m){
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	faces[3] = f4;
	texcoord[0] = t1;
	texcoord[1] = t2;
	texcoord[2] = t3;
	texcoord[3] = t4;
	mat = m;
	four = true;
}

material::material(const char* na, float al, float n, float ni2, float* d, float* a, float* s, int i, int t)
{
	name = na;
	alpha = al;
	ni = ni2;
	ns = n;
	dif[0] = d[0];
	dif[1] = d[1];
	dif[2] = d[2];

	amb[0] = a[0];
	amb[1] = a[1];
	amb[2] = a[2];

	spec[0] = s[0];
	spec[1] = s[1];
	spec[2] = s[2];

	illum = i;
	texture = t;
}

texcoord::texcoord(float a, float b)
{
	u = a;
	v = b;
}

Mesh::Mesh()// : ismaterial(false), isnormals(false), istexture(false)
{
	ismaterial = false;
	isnormals = false;
	istexture = false;

	ilInit();

	devilError = ilGetError();

	if (devilError != IL_NO_ERROR)
	{
		printf("Devil Error (ilInit: %s\n", iluErrorString(devilError));
		exit(2);
	}
}

int Mesh::Load(const char* filename)
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
	std::string name = filename;
	//printf("Loading OBJ file...." + name + "\n", filename);
	std::cout << "Loading OBJ file... " + name + "\n";
	istexture = false;

	std::ifstream in(filename);
	if (!in.is_open())
	{
		std::cout << "Not opened" << std::endl;
		return -1;
	}
	char buf[256];
	int curmat = 0;

	while (!in.eof())
	{
		in.getline(buf, 256);
		line.push_back(new std::string(buf));
	}

	for (unsigned int i = 0; i<line.size(); i++)
	{
		if ((*line[i]).empty() || (*line[i])[0] == '#' || (*line[i])[0] == 'o')
			continue;

		else if ((*line[i])[0] == 'v' && (*line[i])[1] == ' ')
		{
			vec3 vertices;
			sscanf_s(line[i]->c_str(), "v %f %f %f", &vertices.x, &vertices.y, &vertices.z);
			temp_vertices.push_back(new coordinate(vertices.x, vertices.y, vertices.z));
		}
		else if ((*line[i])[0] == 'v' && (*line[i])[1] == 'n')
		{
			vec3 normals;
			sscanf_s(line[i]->c_str(), "vn %f %f %f", &normals.x, &normals.y, &normals.z);
			temp_normals.push_back(new coordinate(normals.x, normals.y, normals.z));
			isnormals = true;
		}
		else if ((*line[i])[0] == 'f')	//if it's a face
		{
			int a, b, c, d, e;
			if (count(line[i]->begin(), line[i]->end(), ' ') == 5)
			{
				if (line[i]->find("//") != std::string::npos)
				{
					sscanf_s(line[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
					temp_faces.push_back(new face(b, a, c, d, e, 0, 0, 0, 0, curmat));
				}
				else if (line[i]->find("/") != std::string::npos)
				{
					int t[4];
					sscanf_s(line[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b, &e, &t[3], &b);
					temp_faces.push_back(new face(b, a, c, d, e, t[0], t[1], t[2], t[3], curmat));
				}
				else
				{
					sscanf_s(line[i]->c_str(), "f %d %d %d %d", &a, &b, &c, &d);
					temp_faces.push_back(new face(-1, a, b, c, d, 0, 0, 0, 0, curmat));
				}
			}
			else{
				if (line[i]->find("//") != std::string::npos)
				{
					sscanf_s(line[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
					temp_faces.push_back(new face(b, a, c, d, 0, 0, 0, curmat));
				}
				else if (line[i]->find("/") != std::string::npos)
				{
					int t[3];
					sscanf_s(line[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b);
					temp_faces.push_back(new face(b, a, c, d, t[0], t[1], t[2], curmat));
				}
				else
				{
					sscanf_s(line[i]->c_str(), "f %d %d %d", &a, &b, &c);
					temp_faces.push_back(new face(-1, a, b, c, 0, 0, 0, curmat));
				}
			}
		}
		else if ((*line[i])[0] == 'u' && (*line[i])[1] == 's' && (*line[i])[2] == 'e')
		{
			char tmp[200];
			sscanf(line[i]->c_str(), "usemtl %s", tmp);
			for (unsigned int i = 0; i<temp_materials.size(); i++)
			{
				if (strcmp(temp_materials[i]->name.c_str(), tmp) == 0)
				{
					curmat = i;
					break;
				}
			}
		}
		else if ((*line[i])[0] == 'm' && (*line[i])[1] == 't' && (*line[i])[2] == 'l' && (*line[i])[3] == 'l')

		{
			char tmpfilen[200];
			sscanf(line[i]->c_str(), "mtllib %s", tmpfilen);

			std::ifstream mtlin(tmpfilen);
			if (!mtlin.is_open())
			{
				std::cout << "connot open the material file" << std::endl;
				clean();
				return -1;
			}

			ismaterial = true;
			std::vector<std::string> tmp;
			char c[200];
			while (!mtlin.eof())
			{
				mtlin.getline(c, 200);
				tmp.push_back(c);
			}
			char name[200];
			char filename[200];
			float amb[3], dif[3], spec[3], alpha, ns, ni;
			int illum;

			unsigned int texture;
			bool ismat = false;
			strcpy_s(filename, "\0");

			for (unsigned int i = 0; i<tmp.size(); i++)
			{
				if (tmp[i].empty() || tmp[i][0] == '#')
					continue;

				if (tmp[i][0] == 'n' && tmp[i][1] == 'e' && tmp[i][2] == 'w')
				{
					if (ismat)
					{
						if (strcmp(filename, "\0") != 0)
						{
							temp_materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texture));
							strcpy_s(filename, "\0");
						}
						else
						{
							temp_materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
						}
					}

					ismat = false;
					sscanf(tmp[i].c_str(), "newmtl %s", name);
				}
				else if (tmp[i][0] == 'N' && tmp[i][1] == 's')
				{
					sscanf_s(tmp[i].c_str(), "Ns %f", &ns);
					ismat = true;
				}
				else if (tmp[i][0] == 'K' && tmp[i][1] == 'a')
				{
					sscanf_s(tmp[i].c_str(), "Ka %f %f %f", &amb[0], &amb[1], &amb[2]);
					ismat = true;
				}
				else if (tmp[i][0] == 'K' && tmp[i][1] == 'd')
				{
					sscanf_s(tmp[i].c_str(), "Kd %f %f %f", &dif[0], &dif[1], &dif[2]);
					ismat = true;
				}
				else if (tmp[i][0] == 'K' && tmp[i][1] == 's')
				{
					sscanf_s(tmp[i].c_str(), "Ks %f %f %f", &spec[0], &spec[1], &spec[2]);
					ismat = true;
				}
				else if (tmp[i][0] == 'N' && tmp[i][1] == 'i')
				{
					sscanf_s(tmp[i].c_str(), "Ni %f", &ni);
					ismat = true;
				}
				else if (tmp[i][0] == 'd' && tmp[i][1] == ' ')
				{
					sscanf_s(tmp[i].c_str(), "d %f", &alpha);
					ismat = true;
				}
				else if (tmp[i][0] == 'i' && tmp[i][1] == 'l')
				{
					sscanf_s(tmp[i].c_str(), "illum %d", &illum);
					ismat = true;
				}
				else if (tmp[i][0] == 'm' && tmp[i][1] == 'a')	//and the texture
				{
					sscanf(tmp[i].c_str(), "map_Kd %s", filename);
					texture = loadTexture(filename);	//read the filename, and use the loadTexture function to load it, and get the id.
					ismat = true;
				}
			}
			if (ismat)
			{
				if (strcmp(filename, "\0") != 0)
				{
					temp_materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texture));
				}
				else
				{
					temp_materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
				}
			}
		}
		else if ((*line[i])[0] == 'v' && (*line[i])[1] == 't')
		{
			float u, v;
			sscanf_s(line[i]->c_str(), "vt %f %f", &u, &v);
			temp_uvs.push_back(new texcoord(u, 1 - v));
			istexture = true;
		}
	}
	if (temp_materials.size() == 0)
		ismaterial = false;
	else
		ismaterial = true;

	//std::cout << temp_vertices.size() << " " << temp_normals.size() << " " << temp_faces.size() << " " << temp_materials.size() << std::endl; 
	int num;
	num = glGenLists(1);
	glNewList(num, GL_COMPILE);
	int last = -1;
	for (unsigned int i = 0; i<temp_faces.size(); i++)
	{
		if (last != temp_faces[i]->mat && ismaterial)
		{
			//set all of the material property
			float diffuse[] = { temp_materials[temp_faces[i]->mat]->dif[0], temp_materials[temp_faces[i]->mat]->dif[1], temp_materials[temp_faces[i]->mat]->dif[2], 1.0 };
			float ambient[] = { temp_materials[temp_faces[i]->mat]->amb[0], temp_materials[temp_faces[i]->mat]->amb[1], temp_materials[temp_faces[i]->mat]->amb[2], 1.0 };
			float specular[] = { temp_materials[temp_faces[i]->mat]->spec[0], temp_materials[temp_faces[i]->mat]->spec[1], temp_materials[temp_faces[i]->mat]->spec[2], 1.0 };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, temp_materials[temp_faces[i]->mat]->ns);
			last = temp_faces[i]->mat;
			if (temp_materials[temp_faces[i]->mat]->texture == -1)
				glDisable(GL_TEXTURE_2D);
			else{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, temp_materials[temp_faces[i]->mat]->texture);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
					ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
					ilGetData());
			}
		}
		if (temp_faces[i]->four)	//if quad
		{
			glBegin(GL_QUADS);
			if (isnormals)	//if there are normals
				glNormal3f(temp_normals[temp_faces[i]->facenum - 1]->x, temp_normals[temp_faces[i]->facenum - 1]->y, temp_normals[temp_faces[i]->facenum - 1]->z);	//use them

			if (istexture && temp_materials[temp_faces[i]->mat]->texture != -1)	//if there are textures
				glTexCoord2f(temp_uvs[temp_faces[i]->texcoord[0] - 1]->u, temp_uvs[temp_faces[i]->texcoord[0] - 1]->v);	//set the texture coorinate

			glVertex3f(temp_vertices[temp_faces[i]->faces[0] - 1]->x, temp_vertices[temp_faces[i]->faces[0] - 1]->y, temp_vertices[temp_faces[i]->faces[0] - 1]->z);

			if (istexture && temp_materials[temp_faces[i]->mat]->texture != -1)
				glTexCoord2f(temp_uvs[temp_faces[i]->texcoord[1] - 1]->u, temp_uvs[temp_faces[i]->texcoord[1] - 1]->v);

			glVertex3f(temp_vertices[temp_faces[i]->faces[1] - 1]->x, temp_vertices[temp_faces[i]->faces[1] - 1]->y, temp_vertices[temp_faces[i]->faces[1] - 1]->z);

			if (istexture && temp_materials[temp_faces[i]->mat]->texture != -1)
				glTexCoord2f(temp_uvs[temp_faces[i]->texcoord[2] - 1]->u, temp_uvs[temp_faces[i]->texcoord[2] - 1]->v);

			glVertex3f(temp_vertices[temp_faces[i]->faces[2] - 1]->x, temp_vertices[temp_faces[i]->faces[2] - 1]->y, temp_vertices[temp_faces[i]->faces[2] - 1]->z);

			if (istexture && temp_materials[temp_faces[i]->mat]->texture != -1)
				glTexCoord2f(temp_uvs[temp_faces[i]->texcoord[3] - 1]->u, temp_uvs[temp_faces[i]->texcoord[3] - 1]->v);

			glVertex3f(temp_vertices[temp_faces[i]->faces[3] - 1]->x, temp_vertices[temp_faces[i]->faces[3] - 1]->y, temp_vertices[temp_faces[i]->faces[3] - 1]->z);
			glEnd();
		}
		else{
			glBegin(GL_TRIANGLES);
			if (isnormals)	//if there are normals
				glNormal3f(temp_normals[temp_faces[i]->facenum - 1]->x, temp_normals[temp_faces[i]->facenum - 1]->y, temp_normals[temp_faces[i]->facenum - 1]->z);

			if (istexture && temp_materials[temp_faces[i]->mat]->texture != -1)
				glTexCoord2f(temp_uvs[temp_faces[i]->texcoord[0] - 1]->u, temp_uvs[temp_faces[i]->texcoord[0] - 1]->v);


			glVertex3f(temp_vertices[temp_faces[i]->faces[0] - 1]->x, temp_vertices[temp_faces[i]->faces[0] - 1]->y, temp_vertices[temp_faces[i]->faces[0] - 1]->z);

			if (istexture && temp_materials[temp_faces[i]->mat]->texture != -1)
				glTexCoord2f(temp_uvs[temp_faces[i]->texcoord[1] - 1]->u, temp_uvs[temp_faces[i]->texcoord[1] - 1]->v);

			glVertex3f(temp_vertices[temp_faces[i]->faces[1] - 1]->x, temp_vertices[temp_faces[i]->faces[1] - 1]->y, temp_vertices[temp_faces[i]->faces[1] - 1]->z);


			if (istexture && temp_materials[temp_faces[i]->mat]->texture != -1)
				glTexCoord2f(temp_uvs[temp_faces[i]->texcoord[2] - 1]->u, temp_uvs[temp_faces[i]->texcoord[2] - 1]->v);

			glVertex3f(temp_vertices[temp_faces[i]->faces[2] - 1]->x, temp_vertices[temp_faces[i]->faces[2] - 1]->y, temp_vertices[temp_faces[i]->faces[2] - 1]->z);
			glEnd();
		}
	}
	
	glEndList();
	clean();
	lists.push_back(num);
	return num;
}

void Mesh::clean()
{
	//delete all the dynamically allocated memory
	for (unsigned int i = 0; i<line.size(); i++)
		delete line[i];
	for (unsigned int i = 0; i<temp_faces.size(); i++)
		delete temp_faces[i];
	for (unsigned int i = 0; i<temp_normals.size(); i++)
		delete temp_normals[i];
	for (unsigned int i = 0; i<temp_vertices.size(); i++)
		delete temp_vertices[i];
	for (unsigned int i = 0; i<temp_materials.size(); i++)
		delete temp_materials[i];
	for (unsigned int i = 0; i<temp_uvs.size(); i++)
		delete temp_uvs[i];
	//and all elements from the vector
	line.clear();
	temp_faces.clear();
	temp_normals.clear();
	temp_vertices.clear();
	temp_materials.clear();
	temp_uvs.clear();
}

uint Mesh::loadTexture(const char* filename)
{
	ILuint devilID;
	ilGenImages(1, &devilID);
	ilLoadImage(filename);
	ilBindImage(devilID);
	ilLoadImage(filename);
	devilError = ilGetError();

	if (devilError != IL_NO_ERROR)
	{
			printf("Devil Error (ilLoadImage: %s\n", iluErrorString(devilError));
		exit(2);
	}

	texture.push_back(devilID);
	return devilID;
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
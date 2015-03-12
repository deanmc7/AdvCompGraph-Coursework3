#ifndef __Skybox_h_
#define __Skybox_h_

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

#include "Camera.h"
#include "SkyboxTech.h"
#include "CubemapText.h"
#include "Mesh.h"

class Skybox
{
private:
	SkyboxTech*		pSkyboxTech;
	const Camera*	pCamera;
	CubemapText*	pCubemapTex;
	Mesh*			pMesh;
	PersProjInfo	pPersProjInfo;

public:
	Skybox(const Camera* pCam);
	~Skybox();

	bool Init(const std::string& Directory,
		const std::string& PosXFilename,
		const std::string& NegXFilename,
		const std::string& PosYFilename,
		const std::string& NegYFilename,
		const std::string& PosZFilename,
		const std::string& NegZFilename);

	void Render();
};

#endif //#ifndef __Skybox_h_
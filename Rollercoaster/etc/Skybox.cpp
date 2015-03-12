#include "Skybox.h"

Skybox::Skybox(const Camera* pCam) : pCamera(pCam), pSkyboxTech(nullptr), pCubemapTex(nullptr)
{
	
}

bool Skybox::Init(const std::string& Directory,
	const std::string& PosXFilename,
	const std::string& NegXFilename,
	const std::string& PosYFilename,
	const std::string& NegYFilename,
	const std::string& PosZFilename,
	const std::string& NegZFilename)
{
	pSkyboxTech = new SkyboxTech();

	if (!pSkyboxTech->Init()) {
		printf("Error initializing the skybox technique\n");
		return false;
	}

	pSkyboxTech->Enable();
	pSkyboxTech->SetTextureUnit(0);

	pCubemapTex = new CubemapText(Directory,
		PosXFilename,
		NegXFilename,
		PosYFilename,
		NegYFilename,
		PosZFilename,
		NegZFilename);

	if (!pCubemapTex->Load()) {
		return false;
	}

	pMesh = new Mesh();
	pMesh->LoadMesh("sphere.obj");
}

void Skybox::Render()
{
	pSkyboxTech->Enable();

	GLint OldCullFaceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
	GLint OldDepthFuncMode;
	glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	pCubemapTex->Bind(GL_TEXTURE0);
	pMesh->Render();

	glCullFace(OldCullFaceMode);
	glDepthFunc(OldDepthFuncMode);
}
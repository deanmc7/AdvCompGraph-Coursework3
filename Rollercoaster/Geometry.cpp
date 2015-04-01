#include "Geometry.h"

Geometry::Geometry(void)
{
	mMeshLoader = new Mesh();
}

void Geometry::Init(void)
{
	mColumn = mMeshLoader->Load("column.obj");
	mDesert = mMeshLoader->Load("desert.obj");
}

void Geometry::drawTerrain(void)
{
	glCallList(this->mDesert);
}

void Geometry::drawColumn(void)
{
	glCallList(this->mColumn);
}
#include "Geometry.h"

Geometry::Geometry(void)
{
	mMeshLoader = new Mesh();
}

void Geometry::Init(void)
{
	//mCreature = mMeshLoader->Load("creature.obj");
	mDesert = mMeshLoader->Load("desert.obj");
	//mCastle = mMeshLoader->Load("castle.obj");
}

void Geometry::drawCreature(void)
{
	glCallList(this->mCreature);
}

void Geometry::drawTerrain(void)
{
	glCallList(this->mDesert);
}

void Geometry::drawCastle()
{
	glCallList(this->mCastle);
}
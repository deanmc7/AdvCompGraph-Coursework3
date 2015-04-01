#ifndef __Geometry_h_
#define __Geometry_h_

#include "Utility.h"
#include "TGAloader.h"
#include "Textures.h"
#include "Mesh.h"

class Geometry
{
private:
	Mesh*		mMeshLoader;
	int mDesert, mCreature, mCastle, mColumn;

public:
	Geometry(void);
	
	void Init(void);

	void drawTerrain(void);
	void drawColumn(void);
};

#endif //#ifndef __Geometry_h_
#ifndef __Geometry_h_
#define __Geometry_h_

#include "Utility.h"
#include "TGAloader.h"
#include "Textures.h"

class Geometry
{
private:

public:
	Geometry(void);
	
	void drawFloor(Textures* texture);
};

#endif //#ifndef __Geometry_h_
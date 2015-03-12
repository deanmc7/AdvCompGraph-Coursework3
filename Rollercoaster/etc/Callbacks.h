#ifndef __Callbacks_h_
#define __Callbacks_h_

#include "Keys.h"

class Callbacks
{
public:
	
	virtual void KeyboardCallback(KEY key){};

	virtual void RenderCallback(){};

	virtual void ReshapeCallback(int width, int height){};
};

#endif //#ifndef __Callbacks_h_
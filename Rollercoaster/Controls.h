#ifndef __Controls_h_
#define __Controls_h_

#include "Utility.h"
#include "Camera.h"

void ComputeMatrices(int width, int height);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif //#ifndef __Controls_h_
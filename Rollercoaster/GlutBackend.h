#ifndef __GlutBackend_h_
#define __GlutBackend_h_

#include <stdio.h>
#include <GL/freeglut.h>

#include "TypeDefs.h"
#include "Callbacks.h"


void BackendInit(int argc, char** argv, bool depth);

bool gCreateWindow(unsigned int width, unsigned int height, const char* title);

void BackendRun(Callbacks* mCallback);

void BackendSwapBuffers();

void BackendLeaveMainLoop();

KEY GlutKeytoCustomKey(uint key);

#endif
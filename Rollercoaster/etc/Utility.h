#ifndef __Utility_h_
#define __Utility_h_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

#define INVALID_UNIFORM_LOCATION 0xffffffff
#define INVALID_OGL_VALUE 0xffffffff

bool ReadFile(const char* pFileName, string& outFile);

#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define RANDOM rand
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#endif //#ifndef __Utility_h_
#ifndef __Utility_h_
#define __Utility_h_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <GL\glew.h>
#include <GL\glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL\freeglut.h>

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()

typedef unsigned int        UINT;

#endif //#ifndef __Utility_h_
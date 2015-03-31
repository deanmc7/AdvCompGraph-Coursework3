#ifndef __Utility_h_
#define __Utility_h_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <math.h>
#include "Math3d.h"
#include <algorithm>
#include <cstdio>
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GL\glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL\freeglut.h>
#include "Math3d.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)
#define GLCheckError() (glGetError() == GL_NO_ERROR)

#define M_PI       3.14159265358979323846
#define INVALID_UNIFORM_LOCATION 0xffffffff
#define MAX_LOG_SIZE 2048

#define ESCAPE 27
#define GRAVITY -9.807
#define CAR1SPEED 2000.0f
#define CAR2SPEED 1000.0f
#define CAR3SPEED 200.0f

#define NUM_OF_TEXTURES 9
#define FLOOR_TEXTURE	0
#define TRACK_TEXTURE	1
#define SKYBOX_TOP		2
#define SKYBOX_FRONT	3
#define SKYBOX_LEFT		4
#define SKYBOX_RIGHT	5
#define SKYBOX_BACK		6
#define DESERT_TEXTURE	7
#define CART_TEXTURE	8
//#define WHEEL_TEXTURE	9

#define FOG_EQUATION_LINEAR		0
#define FOG_EQUATION_EXP		1
#define FOG_EQUATION_EXP2		2

#define ESZ(elem) (int)elem.size()

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

#endif //#ifndef __Utility_h_
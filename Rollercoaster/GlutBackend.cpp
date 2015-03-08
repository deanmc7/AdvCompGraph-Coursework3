#include "GlutBackend.h"

static Callbacks* mCallbacks = NULL;
static bool withDepth = false;

static void SpecialKey(int key, int x, int y)
{
	KEY mKey = GlutKeytoCustomKey(key);
	mCallbacks->KeyboardCallback(mKey);
}

static void KeyboardCallback(unsigned char key, int x, int y)
{
	if (
		((key >= '0') && (key <= '9')) ||
		((key >= 'A') && (key <= 'Z')) ||
		((key >= 'a') && (key <= 'z'))
		) {
		KEY OgldevKey = (KEY)key;
		mCallbacks->KeyboardCallback(OgldevKey);
	}
	else {
		return;
	}
}

static void RenderCallback()
{
	mCallbacks->RenderCallback();
}

static void IdleCallback()
{
	mCallbacks->RenderCallback();
}

static void ReshapeCallback(int width, int height)
{
	mCallbacks->ReshapeCallback(width, height);
}

static void InitCallbacks()
{
	glutDisplayFunc(RenderCallback);
	glutIdleFunc(IdleCallback);
	glutSpecialFunc(SpecialKey);
	glutKeyboardFunc(KeyboardCallback);
	glutReshapeFunc(ReshapeCallback);
}

void BackendInit(int argc, char** argv, bool depth)
{
	glutInit(&argc, argv);

	withDepth = depth;

	uint displayMode = GLUT_DOUBLE | GLUT_RGBA;

	if (depth)
		displayMode |= GLUT_DEPTH;
	
	glutInitDisplayMode(displayMode);
}

bool gCreateWindow(uint width, uint height, const char* title)
{
	glutInitWindowSize(width, height);
	glutCreateWindow(title);

	return true;
}

void BackendRun(Callbacks* Callback)
{
	if (!Callback)
		return;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	if (withDepth)
		glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	mCallbacks = Callback;
	InitCallbacks();
	glutMainLoop();
}

void BackendSwapBuffers()
{
	glutSwapBuffers();
}

void BackendLeaveMainLoop()
{
	glutLeaveMainLoop();
}

KEY GlutKeytoCustomKey(uint key)
{
	switch (key) {
	case GLUT_KEY_F1:
		return KEY_F1;
	case GLUT_KEY_F2:
		return KEY_F2;
	case GLUT_KEY_F3:
		return KEY_F3;
	case GLUT_KEY_F4:
		return KEY_F4;
	case GLUT_KEY_F5:
		return KEY_F5;
	case GLUT_KEY_F6:
		return KEY_F6;
	case GLUT_KEY_F7:
		return KEY_F7;
	case GLUT_KEY_F8:
		return KEY_F8;
	case GLUT_KEY_F9:
		return KEY_F9;
	case GLUT_KEY_F10:
		return KEY_F10;
	case GLUT_KEY_F11:
		return KEY_F11;
	case GLUT_KEY_F12:
		return KEY_F12;
	case GLUT_KEY_LEFT:
		return KEY_LEFT;
	case GLUT_KEY_UP:
		return KEY_UP;
	case GLUT_KEY_RIGHT:
		return KEY_RIGHT;
	case GLUT_KEY_DOWN:
		return KEY_DOWN;
	case GLUT_KEY_PAGE_UP:
		return KEY_PAGE_UP;
	case GLUT_KEY_PAGE_DOWN:
		return KEY_PAGE_DOWN;
	case GLUT_KEY_HOME:
		return KEY_HOME;
	case GLUT_KEY_END:
		return KEY_END;
	case GLUT_KEY_INSERT:
		return KEY_INSERT;
	case GLUT_KEY_DELETE:
		return KEY_DELETE;
	default:
		exit(1);
	}

	return KEY_UNDEFINED;
}
//**********************************
// OpenGL Draw Instanced Array
// 28/03/2010 - 06/04/2010
//**********************************
// Christophe Riccio
// ogl-samples@g-truc.net
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include <glf/glf.hpp>

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Draw Instanced Array";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/instanced-array.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/instanced-array.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(3);
	int const SAMPLE_MINOR_VERSION(3);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount(6);
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec2);
	glm::vec2 const PositionData[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(-1.0f,-1.0f)
	};

	GLsizei const InstanceCount(5);
	GLsizeiptr const ColorSize = VertexCount * sizeof(glm::vec4);
	glm::vec4 const ColorData[VertexCount] =
	{
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
	};

	GLuint VertexArrayName(0);
	GLuint ProgramName(0);
	GLuint PositionBufferName(0);
	GLuint ColorBufferName(0);
	GLint UniformMVP(0);

	typedef void (GLAPIENTRY * PFNGLVERTEXARRAYVERTEXATTRIBDIVISORPROCGTC) (GLuint VertexArray, GLuint index, GLuint divisor);
	PFNGLVERTEXARRAYVERTEXATTRIBDIVISORPROCGTC glVertexArrayVertexAttribDivisorGTC = 0;
}//namespace

bool initTest()
{
	bool Validated = true;
	glEnable(GL_DEPTH_TEST);

	return Validated && glf::checkError("initTest");
}

bool initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertexShaderName);
		glAttachShader(ProgramName, FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);

		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
	}

	return Validated && glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &PositionBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, PositionBufferName);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ColorBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferName);
    glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, PositionBufferName, glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexArrayVertexAttribDivisorGTC(VertexArrayName, glf::semantic::attr::POSITION, 0);
	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, ColorBufferName, glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexArrayVertexAttribDivisorGTC(VertexArrayName, glf::semantic::attr::COLOR, 1);

	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::COLOR);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	glVertexArrayVertexAttribDivisorGTC = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISORPROCGTC)glutGetProcAddress("glVertexArrayVertexAttribDivisor");
	if(!glVertexArrayVertexAttribDivisorGTC)
		glVertexArrayVertexAttribDivisorGTC = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISORPROCGTC)glutGetProcAddress("glVertexArrayVertexAttribDivisorARB");
	else if(!glVertexArrayVertexAttribDivisorGTC)
		glVertexArrayVertexAttribDivisorGTC = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISORPROCGTC)glutGetProcAddress("glVertexArrayVertexAttribDivisorEXT");
	else if(!glVertexArrayVertexAttribDivisorGTC)
		glVertexArrayVertexAttribDivisorGTC = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISORPROCGTC)glutGetProcAddress("glVertexArrayVertexAttribDivisorNV");
	else if(!glVertexArrayVertexAttribDivisorGTC)
		glVertexArrayVertexAttribDivisorGTC = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISORPROCGTC)glutGetProcAddress("glVertexArrayVertexAttribDivisorAMD");

	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_ARB_viewport_array");
	Validated = Validated && glf::checkExtension("GL_ARB_separate_shader_objects");
	Validated = Validated && glf::checkExtension("GL_EXT_direct_state_access");
	Validated = Validated && (glVertexArrayVertexAttribDivisorGTC != 0);

	if(Validated)
		Validated = initTest();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initVertexArray();

	return Validated && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteBuffers(1, &PositionBufferName);
	glDeleteBuffers(1, &ColorBufferName);
	glDeleteProgram(ProgramName);
	glDeleteVertexArrays(1, &VertexArrayName);

	return glf::checkError("end");
}

void display()
{
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y + 45.0f, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x + 45.0f, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glProgramUniformMatrix4fv(ProgramName, UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));

	float Depth(1.0f);
	glClearBufferfv(GL_DEPTH, 0, &Depth);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)[0]);

	glUseProgram(ProgramName);

	glBindVertexArray(VertexArrayName);
	glDrawArraysInstanced(GL_TRIANGLES, 0, VertexCount, InstanceCount);

	glf::swapBuffers();
	glf::checkError("display");
}

int main(int argc, char* argv[])
{
	if(glf::run(
		argc, argv,
		glm::ivec2(::SAMPLE_SIZE_WIDTH, ::SAMPLE_SIZE_HEIGHT), 
		::SAMPLE_MAJOR_VERSION, 
		::SAMPLE_MINOR_VERSION))
		return 0;
	return 1;
}

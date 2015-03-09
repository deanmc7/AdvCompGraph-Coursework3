//**********************************
// OpenGL Tessellation
// 14/05/2010 - 26/06/2010
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
	std::string const SAMPLE_NAME = "OpenGL Tessellation";	
	std::string const SAMPLE_VERTEX_SHADER(glf::DATA_DIRECTORY + "400/tess.vert");
	std::string const SAMPLE_CONTROL_SHADER(glf::DATA_DIRECTORY + "400/tess.cont");
	std::string const SAMPLE_EVALUATION_SHADER(glf::DATA_DIRECTORY + "400/tess.eval");
	std::string const SAMPLE_GEOMETRY_SHADER(glf::DATA_DIRECTORY + "400/tess.geom");
	std::string const SAMPLE_FRAGMENT_SHADER(glf::DATA_DIRECTORY + "400/tess.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(0);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 4;
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fc4f);
	glf::vertex_v2fc4f const VertexData[VertexCount] =
	{
		glf::vertex_v2fc4f(glm::vec2(-1.0f,-1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2( 1.0f,-1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2( 1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2(-1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
	};

	GLuint ProgramName(0);
	GLuint ArrayBufferName(0);
	GLuint VertexArrayName(0);
	GLint UniformMVP(0);
}//namespace

bool initProgram()
{
	bool Validated = true;
	
	if(Validated)
	{
		GLuint VertexShader = glf::createShader(GL_VERTEX_SHADER, SAMPLE_VERTEX_SHADER);
		GLuint ControlShader = glf::createShader(GL_TESS_CONTROL_SHADER, SAMPLE_CONTROL_SHADER);
		GLuint EvaluationShader = glf::createShader(GL_TESS_EVALUATION_SHADER, SAMPLE_EVALUATION_SHADER);
		GLuint GeometryShader = glf::createShader(GL_GEOMETRY_SHADER, SAMPLE_GEOMETRY_SHADER);
		GLuint FragmentShader = glf::createShader(GL_FRAGMENT_SHADER, SAMPLE_FRAGMENT_SHADER);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertexShader);
		glAttachShader(ProgramName, ControlShader);
		glAttachShader(ProgramName, EvaluationShader);
		glAttachShader(ProgramName, GeometryShader);
		glAttachShader(ProgramName, FragmentShader);
		glDeleteShader(VertexShader);
		glDeleteShader(ControlShader);
		glDeleteShader(EvaluationShader);
		glDeleteShader(GeometryShader);
		glDeleteShader(FragmentShader);
		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexArray()
{
	// Build a vertex array object
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::COLOR);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &ArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool begin()
{
	bool Validated = glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

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
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteBuffers(1, &ArrayBufferName);
	glDeleteProgram(ProgramName);

	return glf::checkError("end");
}

void display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glViewport(0, 0, Window.Size.x, Window.Size.y);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	glUseProgram(ProgramName);
	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	glBindVertexArray(VertexArrayName);
	glPatchParameteri(GL_PATCH_VERTICES, VertexCount);
	glDrawArraysInstanced(GL_PATCHES, 0, VertexCount, 1);

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	if(glf::run(
		argc, argv,
		glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT), 
		SAMPLE_MAJOR_VERSION, 
		SAMPLE_MINOR_VERSION))
		return 0;
	return 1;
}
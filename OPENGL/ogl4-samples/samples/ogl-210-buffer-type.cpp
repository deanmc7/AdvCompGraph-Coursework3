//**********************************
// OpenGL buffer type
// 10/05/2010
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
	std::string const SAMPLE_NAME = "OpenGL buffer type";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "210/flat-color.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "210/flat-color.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 2;
	int const SAMPLE_MINOR_VERSION = 1;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 6;
	GLsizeiptr const PositionSizeF64 = VertexCount * sizeof(glm::dvec2);
	glm::dvec2 const PositionDataF64[VertexCount] =
	{
		glm::dvec2(-1.0f, -1.0f),
		glm::dvec2( 1.0f, -1.0f),
		glm::dvec2( 1.0f,  1.0f),
		glm::dvec2( 1.0f,  1.0f),
		glm::dvec2(-1.0f,  1.0f),
		glm::dvec2(-1.0f, -1.0f)
	};

	GLsizeiptr const PositionSizeF32 = VertexCount * sizeof(glm::vec2);
	glm::vec2 const PositionDataF32[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(-1.0f,-1.0f)
	};

	GLsizeiptr const PositionSizeI8 = VertexCount * sizeof(glm::i8vec2);
	glm::i8vec2 const PositionDataI8[VertexCount] =
	{
		glm::i8vec2(-1,-1),
		glm::i8vec2( 1,-1),
		glm::i8vec2( 1, 1),
		glm::i8vec2( 1, 1),
		glm::i8vec2(-1, 1),
		glm::i8vec2(-1,-1)
	};

	GLsizeiptr const PositionSizeI32 = VertexCount * sizeof(glm::i32vec2);
	glm::i32vec2 const PositionDataI32[VertexCount] =
	{
		glm::i32vec2(-1,-1),
		glm::i32vec2( 1,-1),
		glm::i32vec2( 1, 1),
		glm::i32vec2( 1, 1),
		glm::i32vec2(-1, 1),
		glm::i32vec2(-1,-1)
	};

	enum buffer_index
	{
		BUFFER_F64,
		BUFFER_F32,
		BUFFER_I8,
		BUFFER_I32,
		BUFFER_MAX
	};

	GLuint VertexArrayName = 0;
	GLuint ProgramName = 0;
	GLuint BufferName[BUFFER_MAX]= {0, 0, 0, 0};
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;

	glm::ivec4 Viewport[BUFFER_MAX];
	GLenum BufferType[BUFFER_MAX];
}//namespace

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

		glBindAttribLocation(ProgramName, glf::semantic::attr::POSITION, "Position");
		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName, "Diffuse");
	}

	// Set some variables 
	if(Validated)
	{
		// Bind the program for use
		glUseProgram(ProgramName);

		// Set uniform value
		glUniform4fv(UniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		// Unbind the program
		glUseProgram(0);
	}

	return Validated && glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(BUFFER_MAX, BufferName);

	// Allocate and copy buffers memory
    glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_F64]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeF64, PositionDataF64, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_F32]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeF32, PositionDataF32, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_I8]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeI8, PositionDataI8, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_I32]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeI32, PositionDataI32, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool begin()
{
	Viewport[BUFFER_F64] = glm::ivec4(0, 0, Window.Size >> 1);
	BufferType[BUFFER_F64] = GL_DOUBLE;
	Viewport[BUFFER_F32] = glm::ivec4(Window.Size.x >> 1, 0, Window.Size >> 1);
	BufferType[BUFFER_F32] = GL_FLOAT;
	Viewport[BUFFER_I8]  = glm::ivec4(Window.Size.x >> 1, Window.Size.y >> 1, Window.Size >> 1);
	BufferType[BUFFER_I8]  = GL_BYTE;
	Viewport[BUFFER_I32] = glm::ivec4(0, Window.Size.y >> 1, Window.Size >> 1);
	BufferType[BUFFER_I32] = GL_INT;

	bool Validated = true;
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();

	return Validated && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteBuffers(BUFFER_MAX, BufferName);
	glDeleteProgram(ProgramName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslateZ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslateZ, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 ViewRotateY = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 View = ViewRotateY;
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind program
	glUseProgram(ProgramName);

	// Set the value of MVP uniform.
	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	for(std::size_t Index = 0; Index < BUFFER_MAX; ++Index)
	{
		// Set the display viewport
		glViewport(
			Viewport[Index].x, 
			Viewport[Index].y, 
			Viewport[Index].z, 
			Viewport[Index].w);

		// Bind vertex attribute
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[Index]);
			glVertexAttribPointer(glf::semantic::attr::POSITION, 2, BufferType[Index], GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Draw
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
			glDrawArrays(GL_TRIANGLES, 0, VertexCount);
		glDisableVertexAttribArray(glf::semantic::attr::POSITION);
	}

	// Unbind program
	glUseProgram(0);

	glf::checkError("display");
	glf::swapBuffers();
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
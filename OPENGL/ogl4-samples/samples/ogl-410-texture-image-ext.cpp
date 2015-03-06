//**********************************
// OpenGL Texture image
// 09/07/2010 - 10/03/2011
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
	std::string const SAMPLE_NAME("OpenGL Texture image");
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "410/texture-image.vert");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "410/texture-image.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken256-rgba8.dds");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(1);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	struct vertex
	{
		vertex
		(
			glm::vec2 const & Position,
			glm::vec2 const & Texcoord
		) :
			Position(Position),
			Texcoord(Texcoord)
		{}

		glm::vec2 Position;
		glm::vec2 Texcoord;
	};

	// With DDS textures, v texture coordinate are reversed, from top to bottom
	GLsizei const VertexCount(6);
	GLsizeiptr const VertexSize = VertexCount * sizeof(vertex);
	vertex const VertexData[VertexCount] =
	{
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f)),
		vertex(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f))
	};

	namespace program
	{
		enum type
		{
			VERT,
			FRAG,
			MAX
		};
	}//namespace program

	glm::uvec2 ImageSize(0);

	GLuint VertexArrayName(0);
	GLuint PipelineName(0);
	GLuint ProgramName[program::MAX] = {0, 0};

	GLuint BufferName(0);
	GLuint TextureName(0);

	GLuint UniformMVP(0);
	GLuint UniformImageData(0);
	GLuint UniformImageSize(0);
}//namespace

bool initProgram()
{
	bool Validated = true;

	glGenProgramPipelines(1, &PipelineName);
	glBindProgramPipeline(PipelineName);

	if(Validated)
	{
		std::string VertexSourceContent = glf::loadFile(VERT_SHADER_SOURCE);
		char const * VertexSourcePointer = VertexSourceContent.c_str();
		ProgramName[program::VERT] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &VertexSourcePointer);
		Validated = Validated && glf::checkProgram(ProgramName[program::VERT]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT, ProgramName[program::VERT]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	if(Validated)
	{
		std::string FragmentSourceContent = glf::loadFile(FRAG_SHADER_SOURCE);
		char const * FragmentSourcePointer = FragmentSourceContent.c_str();
		ProgramName[program::FRAG] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &FragmentSourcePointer);
		Validated = Validated && glf::checkProgram(ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAG]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName[program::VERT], "MVP");
		UniformImageData = glGetUniformLocation(ProgramName[program::FRAG], "ImageData");
		UniformImageSize = glGetUniformLocation(ProgramName[program::FRAG], "ImageSize");
	}

	return Validated && glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &BufferName);
    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initTexture2D()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &TextureName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set image
	gli::texture2D Texture = gli::load(TEXTURE_DIFFUSE);
	for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
	{
		glTexImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			GL_RGBA8, 
			GLsizei(Texture[Level].dimensions().x), 
			GLsizei(Texture[Level].dimensions().y), 
			0,  
			GL_BGRA, 
			GL_UNSIGNED_BYTE, 
			Texture[Level].data());
	}
	ImageSize = glm::uvec2(Texture[0].dimensions());
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	return glf::checkError("initTexture2D");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_EXT_direct_state_access");
	Validated = Validated && glf::checkExtension("GL_EXT_shader_image_load_store");

	if(Validated)
		Validated = initTexture2D();
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
	glDeleteBuffers(1, &BufferName);
	glDeleteTextures(1, &TextureName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteProgram(ProgramName[program::VERT]);
	glDeleteProgram(ProgramName[program::FRAG]);
	glDeleteProgramPipelines(1, &PipelineName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, float(Window.Size.x) / Window.Size.y, 0.1f, 1000.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glProgramUniformMatrix4fv(ProgramName[program::VERT], UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glProgramUniform1i(ProgramName[program::FRAG], UniformImageData, 0);
	glProgramUniform2uiv(ProgramName[program::FRAG], UniformImageSize, 1, &ImageSize[0]);

	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glBindProgramPipeline(PipelineName);

	glBindImageTextureEXT(0, TextureName, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);

	glBindVertexArray(VertexArrayName);
	glDrawArraysInstanced(GL_TRIANGLES, 0, VertexCount, 1);

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

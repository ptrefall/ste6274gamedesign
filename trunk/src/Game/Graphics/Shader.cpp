#include "Shader.h"
#include <GL/glew.h>
#include <GL/wglew.h>

using namespace Graphics;

Shader::Shader(U32 id, const T_String &filename, const T_String &source) 
: id(id), name(filename), source(source), uniformBlockSlotBinding(0) 
{
}

Shader::~Shader() 
{
	if(name == T_String())
		GL( glDeleteProgram(id); )
	else
		GL( glDeleteShader(id); )
}

void Shader::link()
{
	GLint linked;
	int infologLength = 0;
	int charsWritten  = 0;
	GLchar *infoLog;

	// Link the program object and print out the info log
	GL( glLinkProgram(id); )

	GL( glGetProgramiv(id, GL_LINK_STATUS, &linked); )
	GL( glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infologLength); )
	if (infologLength > 0)
	{
		infoLog = (GLchar *)malloc(infologLength);
		if (infoLog == NULL)
			printf("Could not allocate InfoLog buffer for Shader program");

		GL( glGetProgramInfoLog(id, infologLength, &charsWritten, infoLog); )
		if(charsWritten > 0)
			printf("Program InfoLog: %s", infoLog);

		free(infoLog);
	}

	if(!linked)
		throw T_Exception("Failed to link shader program!");
}

void Shader::bind() 
{ 
	GL( glUseProgram(id); )
}

void Shader::unbind() 
{ 
	GL( glUseProgram(0); )
}

U32 Shader::createUniformBlockSlotBinding(const T_String &block_name)
{
	for(U32 i = 0; i < block_names.size(); i++)
	{
		if(block_names[i]->name == block_name)
		{
			// Block names that are duplicate indicates that this shader should be duplicated...
			//CL_Console::write_line(cl_format("The shader %1 seems to require a unique copy for each instance, due to the following Uniform Block: %2", name, block_name));
			return block_names[i]->slot;
		}
	}

	UniformBlock *block = new UniformBlock(block_name, uniformBlockSlotBinding);
	block_names.push_back(block);
	uniformBlockSlotBinding++;
	return block->slot;
}

U32 Shader::getUniformBlockSlotBinding(const T_String &block_name)
{
	for(U32 i = 0; i < block_names.size(); i++)
	{
		if(block_names[i]->name == block_name)
			return block_names[i]->slot;
	}

	//CL_Console::write_line(cl_format("The shader %1 couldn't find the Uniform Block: %2", name, block_name));
	return 0;
}

#include "ShaderSystem.h"
#include "Shader.h"

#include <GL/glew.h>
#include <GL/wglew.h>

#include <stdio.h>
#include <io.h>
#include <fcntl.h>

using namespace Graphics;

ShaderSystem::ShaderSystem()
{
}

ShaderSystem::~ShaderSystem()
{
}

Shader *ShaderSystem::create(U32 type0, const T_String &s0, U32 type1, const T_String &s1, U32 type2, const T_String &s2)
{
	Shader *shader0 = createFromFile(type0, s0);
	Shader *shader1 = createFromFile(type1, s1);
	Shader *shader2 = createFromFile(type2, s2);

	Shader *program = createProgram(shader0,shader1,shader2);
	if(shader0)delete shader0;
	if(shader1)delete shader1;
	if(shader2)delete shader2;
	return program;
}

Shader *ShaderSystem::createFromFile(U32 type, const T_String &filename)
{
	if(type == 0)
		return 0x0;

	S32 fd;
	char name[100];
	S32 size = -1;
	strcpy(name, filename.c_str());

	fd = _open(name, _O_RDONLY);
	if (fd != -1)
	{
		size = _lseek(fd, 0, SEEK_END) + 1;
		_close(fd);
	}

	if(size <= 0)
		throw T_Exception("Failed to load shader file");

	FILE *fh;
	char *shaderText = (GLchar *) malloc(size);
	S32 count;

	fh = fopen(name, "r");
	if (!fh)
		throw T_Exception("Failed to load shader file");

	// Get the shader from a file.
	fseek(fh, 0, SEEK_SET);
	count = (int) fread(shaderText, 1, size, fh);
	shaderText[count] = '\0';

	return createFromString(type, filename, shaderText);
}

Shader *ShaderSystem::createFromString(U32 type, const T_String &name, const T_String &shaderString)
{
	GLint compiled;
	int infologLength = 0;
	int charsWritten  = 0;
	GLchar *infoLog;

	Shader *shader = new Shader(glCreateShader(type), name, shaderString);
	
	const char *cs = shader->source.c_str();
	glShaderSource(shader->id, 1, &cs, NULL);
	glCompileShader(shader->id);
	
	// Check for errors
	glGetShaderiv(shader->id, GL_COMPILE_STATUS, &compiled);
	glGetShaderiv(shader->id, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0)
	{
		infoLog = (GLchar *)malloc(infologLength);
		if (infoLog == NULL)
			printf("Could not allocate InfoLog buffer for shader %s", shader->name.c_str());

		glGetShaderInfoLog(shader->id, infologLength, &charsWritten, infoLog);
		if(charsWritten > 0)
			printf("Shader %s InfoLog: %s", shader->name.c_str(), infoLog);

		free(infoLog);
	}

	if (!compiled)
	{
		const T_String shader_name = shader->name;
		delete shader;
		throw T_Exception(("Shader " + shader_name + " failed to compile").c_str());
	}

	return shader;
}

Shader *ShaderSystem::createProgram(Shader *s0, Shader *s1, Shader *s2)
{	
	//Create a program object, and attach the shaders
	Shader *program = new Shader(glCreateProgram(), T_String(), T_String());
	if(s0)glAttachShader(program->id, s0->id);
	if(s1)glAttachShader(program->id, s1->id);
	if(s2)glAttachShader(program->id, s2->id);

	return program;
}

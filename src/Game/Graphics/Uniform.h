#pragma once

#include "types_config.h"
#include "Utils.h"

namespace Graphics
{

class Uniform
{
public:
	/// Uniform constructor for storing F32 data.
	Uniform(U32 type, const T_String &name, F32 *data) : type(type), name(name), f(data), i(0x0), ui(0x0), loc(-1) {}
	/// Uniform constructor for storing S32 data.
	Uniform(U32 type, const T_String &name, S32 *data) : type(type), name(name), i(data), f(0x0), ui(0x0), loc(-1) {}
	/// Uniform constructor for storing U32 data.
	Uniform(U32 type, const T_String &name, U32 *data) : type(type), name(name), ui(data), i(0x0), f(0x0), loc(-1) {}
	/// Uniform destructor.
	~Uniform() {}

	/**
		* The type of the uniform data.
		* This can be all from GL_FLOAT_MAT4, to GL_INT or GL_UNSIGNED_INT
		*/
	const U32 type;
	/// The name of the uniform, this name should correspond to the uniform value's name in the shader.
	const T_String name;

	/**
		* Finds the location of the uniform value in the shader. 
		* This must be called before attempting to render.
		*/
	S32 findLocation(U32 shader_program)
	{
		loc = glGetUniformLocation(shader_program, name.c_str());
		return loc;
	}

	/**
		* Binds the uniform to the location in the shader.
		* If location has not been found, it won't work.
		* Shader must be enabled before this will work.
		*/
	void bind()
	{
		// Must have found a location in shader before we're able to bind this uniform.
		if(loc < 0)
			return;

		// If there's no data, then there's nothing to bind. Return.
		if(f == 0x0 && i == 0x0 && ui == 0x0)
			return;

		switch(type)
		{
		case GL_FLOAT:
			glUniform1fv(loc, 1, f);
			break;
		case GL_INT:
			glUniform1iv(loc, 1, i);
			break;
		case GL_UNSIGNED_INT:
			glUniform1iv(loc, 1, (S32*)ui);
			break;
		case GL_FLOAT_VEC2:
			glUniform2fv(loc, 1, f);
			break;
		case GL_FLOAT_VEC3:
			glUniform3fv(loc, 1, f);
			break;
		case GL_FLOAT_VEC4:
			glUniform4fv(loc, 1, f);
			break;
		case GL_FLOAT_MAT3:
			glUniformMatrix3fv(loc, 1, GL_FALSE, f);
			break;
		case GL_FLOAT_MAT4:
			glUniformMatrix4fv(loc, 1, GL_FALSE, f);
			break;
		};
	}

	/// Update the F32 data of the uniform.
	void setData(const F32 *f) { this->f = f; }
	/// Update the S32 data of the uniform.
	void setData(const S32 *i) { this->i = i; }
	/// Update the U32 data of the uniform.
	void setData(const U32 *ui) { this->ui = ui; }

protected:
	/// The F32 data of the uniform.
	const F32 *f;
	/// The S32 data of the uniform.
	const S32 *i;
	/// The U32 data of the uniform.
	const U32 *ui;

	/// The location of the uniform in the shader. Will be -1 if not found.
	S32 loc;
};
}

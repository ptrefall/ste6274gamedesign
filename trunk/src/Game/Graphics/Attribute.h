#pragma once

#include <types_config.h>
#include "Utils.h"

namespace Graphics
{

class Attribute
{
public:
	/**
		* Attribute constructor.
		* Binds some data via the vertex attribute pointer to
		* the shader program.
		*/
	Attribute(U32 shader_program, const char *attribName, S32 size, GLenum type, bool normalized, S32 stride, void* pointer, U32 divisor = 0)
	{
		S32 location = glGetAttribLocation(shader_program, attribName);
		if(location < 0)
		{
			//CL_Console::write_line(cl_format("Failed to load attribute %1", attribName));
			return;
		}
			
		GL( glVertexAttribPointer(location, size, type, normalized, stride, pointer); )
		GL( glEnableVertexAttribArray(location); )
		if(divisor > 0)
			GL( glVertexAttribDivisor((U32)location, divisor); )
	}

	Attribute(S32 location, S32 size, GLenum type, bool normalized, S32 stride, void* pointer, U32 divisor = 0)
	{
		if(location < 0)
		{
			//CL_Console::write_line(cl_format("Failed to load attribute %1", attribName));
			return;
		}
		
		GL( glEnableVertexAttribArray(location); )
		GL( glVertexAttribPointer(location, size, type, normalized, stride, pointer); )
		/*if(divisor > 0)
			GL( glVertexAttribDivisor((U32)location, divisor); )*/
	}
};
}

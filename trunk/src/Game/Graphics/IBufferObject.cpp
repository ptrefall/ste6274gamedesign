#include "IBufferObject.h"
#include <GL/glew.h>
#include <GL/wglew.h>

using namespace Graphics;

IBufferObject::IBufferObject(const U32 &type,  
							 const U32 &draw_type) 
: type(type), id(-1), bufferBound(false), draw_type(draw_type)
{
	GL( glGenBuffers(1, &id); )
}

IBufferObject::~IBufferObject()
{
	GL( glDeleteBuffers(1, &id); )
}

void IBufferObject::init(const U32 &size)
{
	bind(0);
	GL( glBufferData(type, size, NULL, draw_type); )
	unbind();
}

bool IBufferObject::bind(const U32 &shader_id)
{
	GL( glBindBuffer(type, id); )
	bufferBound = true;
	return true;
}

void IBufferObject::internal_buffer(const U32 &offset, const U32 &size, const void *data)
{
	if(bufferBound)
		GL( glBufferSubData(type, offset, size, data); )
}

void IBufferObject::unbind()
{
	GL( glBindBuffer(type, 0); )
	bufferBound = false;
}


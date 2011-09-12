#include "VertexBufferObject.h"
#include "Attribute.h"

#include <GL/glew.h>
#include <GL/wglew.h>

using namespace Graphics;

VertexBufferObject::VertexBufferObject(const U32 size, 
									   const U32 index_count,
									   const U32 *indices,
									   const U32 draw_type)
: IBufferObject(GL_ARRAY_BUFFER, draw_type), has_indices(true), indices_bound(true)
{
	// Vertex buffer objects also needs an index buffer object
	GL( glGenBuffers(1, &index_id); )
	GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id); )
	GL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U32)*index_count, &indices[0], draw_type); )

	IBufferObject::init(size);
}

VertexBufferObject::VertexBufferObject(const U32 size, 
									   const U32 draw_type)
: IBufferObject(GL_ARRAY_BUFFER, draw_type), has_indices(false), indices_bound(false)
{
	IBufferObject::init(size);
}

VertexBufferObject::~VertexBufferObject()
{
	if(has_indices)
		GL( glDeleteBuffers(1, &index_id); )
}

bool VertexBufferObject::bind(const U32 &shader_id)
{
	IBufferObject::bind(shader_id);
	bound_shader_id = shader_id;
	bound_offset = 0;
	return true;
}

void VertexBufferObject::buffer(const T_String &attrib,
								const U32 &attrib_count,
								const U32 &type,
								const U32 &count,
								const void *data,
								const S32 &attrib_location)
{
	if(!bufferBound)
		return;

	U32 data_size = 0;
	if(type == GL_FLOAT)
		data_size = sizeof(F32)*count;
	else if(type == GL_INT)
		data_size = sizeof(S32)*count;
	else if(type == GL_BOOL)
		data_size = sizeof(bool)*count;

	IBufferObject::internal_buffer(bound_offset, data_size, data);
	if(attrib_location >= 0)
		Attribute(attrib_location, attrib_count, type, GL_FALSE, 0, BUFFER_OFFSET(bound_offset));
	else
		Attribute(bound_shader_id, attrib.c_str(), attrib_count, type, GL_FALSE, 0, BUFFER_OFFSET(bound_offset));
	bound_offset += data_size;
}

void VertexBufferObject::buffer(const U32 &type,
								const U32 &count,
								const void *data)
{
	if(!bufferBound)
		return;

	U32 data_size = 0;
	if(type == GL_FLOAT)
		data_size = sizeof(F32)*count;
	else if(type == GL_INT)
		data_size = sizeof(S32)*count;
	else if(type == GL_BOOL)
		data_size = sizeof(bool)*count;

	IBufferObject::internal_buffer(bound_offset, data_size, data);
	bound_offset += data_size;
}

void VertexBufferObject::unbind()
{
	IBufferObject::unbind();
	bound_shader_id = 0;
}

void VertexBufferObject::bindIndices()
{
	indices_bound = true;
	GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id); )
}

void VertexBufferObject::unbindIndices()
{
	indices_bound = false;
	GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); )
}

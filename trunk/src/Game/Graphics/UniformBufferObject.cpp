#include "UniformBufferObject.h"
#include "Shader.h"

#include <GL/glew.h>
#include <GL/wglew.h>

using namespace Graphics;

UniformBufferObject::UniformBufferObject(const U32 layout, 
										 const U32 draw_type,
										 const T_String &block_name,
										 const T_Vector<T_String>::Type &var_names)
: IBufferObject(GL_UNIFORM_BUFFER, draw_type), 
  layout(layout),
  block_name(block_name), 
  var_names(var_names), 
  bound_shader_id(0),
  bound_data(0x0)
{
	
}

UniformBufferObject::~UniformBufferObject()
{
}

void UniformBufferObject::initForProgram(Shader &shader)
{
	//Don't duplicate...
	if(getDataIndex(shader.id) >= 0)
	{
		//CL_Console::write_line(cl_format("GL ERROR: Uniform block %1 returned because shader program %2 has already been loaded for it!"), block_name, shader.name);
		return;
	}

	ProgramBlockData *data = new ProgramBlockData(shader.id);
	data->block_id = glGetUniformBlockIndex(shader.id, block_name.c_str());
	if(data->block_id == GL_INVALID_INDEX)
		throw T_Exception(("GL ERROR: Uniform block " + block_name + " returned an invalid index!").c_str());
	
	glGetActiveUniformBlockiv(shader.id, data->block_id,	GL_UNIFORM_BLOCK_DATA_SIZE,		  &data->size);
	glGetActiveUniformBlockiv(shader.id, data->block_id,	GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &data->active);

	//If first program data
	if(programData.empty())
		IBufferObject::init(data->size);

	U32 bindingPoS32Index = shader.createUniformBlockSlotBinding(block_name);
	glUniformBlockBinding(shader.id, data->block_id, bindingPoS32Index); //Define the binding poS32 of the UBO
	glBindBufferBase(type, bindingPoS32Index, id); //Bind the buffer to the binding poS32

	glGetActiveUniformBlockiv(shader.id, data->block_id, GL_UNIFORM_BLOCK_BINDING, &data->bind);

	const GLchar **cnames = new const GLchar*[var_names.size()];
	for(U32 i = 0; i < var_names.size(); i++)
	{
		cnames[i] = var_names[i].c_str();
	}

	data->indices = new U32[data->active];
	glGetUniformIndices(shader.id, data->active, cnames, data->indices);

	data->offsets = new S32[data->active];
	data->types = new S32[data->active];
	data->array_sizes = new S32[data->active];
	data->block_indices = new S32[data->active];
	data->array_strides = new S32[data->active];
	data->matrix_strides = new S32[data->active];
	data->matrix_is_row_major = new S32[data->active];

	glGetActiveUniformsiv(shader.id, data->active, data->indices, GL_UNIFORM_OFFSET, data->offsets);
	glGetActiveUniformsiv(shader.id, data->active, data->indices, GL_UNIFORM_TYPE, data->types);
	glGetActiveUniformsiv(shader.id, data->active, data->indices, GL_UNIFORM_SIZE, data->array_sizes);
	glGetActiveUniformsiv(shader.id, data->active, data->indices, GL_UNIFORM_ARRAY_STRIDE, data->array_strides);
	glGetActiveUniformsiv(shader.id, data->active, data->indices, GL_UNIFORM_MATRIX_STRIDE, data->matrix_strides);
	glGetActiveUniformsiv(shader.id, data->active, data->indices, GL_UNIFORM_IS_ROW_MAJOR, data->matrix_is_row_major);
	//glGetActiveUniformsiv(shader.id, data->active, data->indices, GL_UNIFORM_BLOCK_INDEX, data->block_indices);
	glGetActiveUniformBlockiv(shader.id, data->block_id, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, data->block_indices);

	programData.push_back(data);
}

bool UniformBufferObject::bind(const U32 &shader_id)
{
	bound_shader_id = shader_id;
	for(U32 i = 0; i < programData.size(); i++)
	{
		if(programData[i]->shader_id == bound_shader_id)
		{
			bound_data = programData[i];
			break;
		}
	}
	// It doesn't always matter which shader...
	if(bound_data == 0x0 && !programData.empty())
		bound_data = programData[0];
	//else
	//	IBufferObject::unbind();

	if(!bufferBound && bound_data != 0x0)
		IBufferObject::bind(shader_id);

	return bufferBound;
}

void UniformBufferObject::buffer(const U32 &index, 
								 const void *data, 
								 const U32 &array_index)
{
	if(!bufferBound)
		return;
	if(bound_data == 0x0)
		return;

	//S32 i = bound_data->block_indices[index];
	S32 i = index;

	U32 data_size = 0;
	if(bound_data->types[i] == GL_FLOAT)
		data_size = sizeof(float);
	else if(bound_data->types[i] == GL_FLOAT_VEC3)
		data_size = sizeof(float)*3;
	else if(bound_data->types[i] == GL_FLOAT_VEC4)
		data_size = sizeof(float)*4;
	else if(bound_data->types[i] == GL_FLOAT_MAT3)
		data_size = sizeof(float)*3*3;
	else if(bound_data->types[i] == GL_FLOAT_MAT4)
		data_size = sizeof(float)*4*4;

	U32 offset = bound_data->offsets[i];
	if(bound_data->array_sizes[i] > 1)
	{
		offset += bound_data->array_strides[i]*array_index;
	}

	if(bound_data->matrix_strides[i] > 0)
	{
		if(bound_data->matrix_is_row_major[i] == 1)
		{
		}
		else
		{
		}
	}

	IBufferObject::internal_buffer(offset, data_size, data);
}

void UniformBufferObject::unbind()
{
	IBufferObject::unbind();
	bound_shader_id = 0;
	bound_data = 0x0;
}

void UniformBufferObject::bindBase(Shader &shader)
{
	glBindBufferBase(type, shader.getUniformBlockSlotBinding(block_name), id);
	//glUniformBlockBinding(shader.id, getBlockId(shader.id), shader.getUniformBlockSlotBinding(block_name));
}

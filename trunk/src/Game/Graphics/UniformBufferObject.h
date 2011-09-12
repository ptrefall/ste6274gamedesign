#pragma once

#include "IBufferObject.h"
#include "Utils.h"
	
namespace Graphics
{

class Shader;

enum UniformBufferLayout
{
	LAYOUT_STL140 = 0,
	LAYOUT_PACKED,
	LAYOUT_SHARED,
	LAYOUT_COUNT
};

class UniformBufferObject : public IBufferObject
{
public:
	/// UniformBufferObject constructor.
	UniformBufferObject(const U32 layout, 
						const U32 draw_type,
						const T_String &block_name,
						const T_Vector<T_String>::Type &var_names);
	/// IBufferObject destructor.
	virtual ~UniformBufferObject();

	///
	void initForProgram(Shader &shader);

	///
	virtual bool bind(const U32 &shader_id);
	///
	void buffer(const U32 &index,
				const void *data, 
				const U32 &array_index = 0);
	///
	virtual void unbind();

	void bindBase(Shader &shader);

	const S32 &getBlockId(const U32 &shader_id) const { return programData[getDataIndex(shader_id)]->block_id; }
	const S32 &getBind(const U32 &shader_id) const { return programData[getDataIndex(shader_id)]->bind; }

	const U32 getDataIndex(const U32 &shader_id) const
	{
		for(U32 i = 0; i < programData.size(); i++)
		{
			if(programData[i]->shader_id == shader_id)
				return i;
		}

		throw T_Exception("Failed to find shader in uniform buffer program data");
	}

	///
	const U32 layout;

protected:
	struct ProgramBlockData
	{
		U32 shader_id;
		S32 block_id;
		S32 bind;
		S32 size;
		S32 active;
		U32 *indices;
		S32 *offsets;
		S32 *types;
		S32 *array_sizes;
		S32 *array_strides;
		S32 *matrix_strides;
		S32 *matrix_is_row_major;
		S32 *block_indices;

		ProgramBlockData(U32 shader_id) : shader_id(shader_id) {}
	};

	T_Vector<ProgramBlockData*>::Type programData;

	const T_String block_name;
	const T_Vector<T_String>::Type var_names;
	U32 bound_shader_id;
	ProgramBlockData *bound_data;
};

typedef UniformBufferObject UBO;

}

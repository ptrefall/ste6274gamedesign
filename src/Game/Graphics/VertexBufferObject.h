#pragma once

#include "IBufferObject.h"
#include "Utils.h"

namespace Graphics
{

class VertexBufferObject : public IBufferObject
{
public:
	/// VertexBufferObject constructor.
	VertexBufferObject(const U32 size,
						const U32 index_count,
						const U32 *indices,
						const U32 draw_type);

	VertexBufferObject(const U32 size,
						const U32 draw_type);
	/// VertexBufferObject destructor.
	virtual ~VertexBufferObject();

	///
	virtual bool bind(const U32 &shader_id);
	///
	void buffer(const T_String &attrib,
				const U32 &attrib_count,
				const U32 &type,
				const U32 &count,
				const void *data,
				const S32 &attrib_location = -1);

	void buffer(const U32 &type,
				const U32 &count,
				const void *data);
	///
	virtual void unbind();

	U32 getBoundOffset() const { return bound_offset; }

	void bindIndices();
	void unbindIndices();

protected:
	bool has_indices;
	U32 index_id;
	U32 bound_shader_id;
	U32 bound_offset;
	bool indices_bound;
};

typedef VertexBufferObject VBO;
}

#pragma once

#include "types_config.h"
#include "Utils.h"

namespace Graphics
{

class IBufferObject
{
public:
	IBufferObject(const U32 &type, const U32 &draw_type);
	virtual ~IBufferObject();

	virtual bool bind(const U32 &shader_id);
	virtual void unbind();
	bool isBound() const { return bufferBound; }
	const U32 type;
	const U32 &getId() const { return id; }

protected:
	void init(const U32 &size);
	void internal_buffer(const U32 &offset, const U32 &size, const void *data);

	U32 id;
	bool bufferBound;
	const U32 draw_type;
};
}

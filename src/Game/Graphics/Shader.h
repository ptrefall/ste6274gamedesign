#pragma once

#include "types_config.h"
#include "Utils.h"

namespace Graphics
{

class Shader
{
public:
	/// Shader constructor.
	Shader(U32 id, const T_String &filename, const T_String &source);
	/// Shader destructor.
	~Shader();

	void link();

	/// Enable the shader. This set's the shader as the currently active shader.
	void bind();
	/// Disable the shader. This set's the active shader to 0.
	void unbind();

	///
	U32 createUniformBlockSlotBinding(const T_String &block_name);
	///
	U32 getUniformBlockSlotBinding(const T_String &block_name);

	/// The shader id given by OpenGL when the shader is created.
	const U32 id;
	/// The name of the shader.
	const T_String name;
	/// The source of the shader.
	const T_String source;

	///
	U32 uniformBlockSlotBinding;
	///
	struct UniformBlock
	{
		///
		T_String name;
		///
		U32 slot;
		UniformBlock(const T_String &name, const U32 &slot) : name(name), slot(slot) {}
	};
	T_Vector<UniformBlock*>::Type block_names;
};
}

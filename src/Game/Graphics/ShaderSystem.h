#pragma once

#include "types_config.h"
#include "Utils.h"

namespace Graphics
{

class Shader;
class ShaderSystem
{
public:
	ShaderSystem();
	~ShaderSystem();

	Shader *create(U32 type0, const T_String &s0, U32 type1 = 0, const T_String &s1 = T_String(), U32 type2 = 0, const T_String &s2 = T_String());

protected:
	Shader *createFromFile(U32 type, const T_String &filename);
	Shader *createFromString(U32 type, const T_String &name, const T_String &shaderString);

	Shader *createProgram(Shader *s0, Shader *s1, Shader *s2);
};
}

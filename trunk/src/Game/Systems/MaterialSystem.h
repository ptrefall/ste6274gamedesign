#pragma once

#include <types_config.h>

namespace Components { class Material; }
namespace Graphics { class Uniform; }

namespace Systems
{
struct TextureData
{
	const U32 gl_id;
	const S32 bpp;
	const S32 w;
	const S32 h;
	const S32 format;
	const unsigned char *bits;
	unsigned int slot;

	TextureData(const U32 &gl_id, const S32 &bpp, const S32 &w, const S32 &h, const S32 &format, const unsigned char *bits, const unsigned int &slot) 
		: gl_id(gl_id), bpp(bpp), w(w), h(h), format(format), bits(bits), slot(slot) {}
};

struct MaterialData
{
	T_HashedString id;
	std::vector<TextureData*> textures;
	std::vector<Graphics::Uniform*> uniforms;

	MaterialData(const T_HashedString &id) : id(id) {}
};

class MaterialSystem
{
public:
	MaterialSystem();
	~MaterialSystem();

	void loadMaterial(Components::Material *material, const T_String &location, const T_String &filename, const T_String &extension, bool ao, bool bu, bool di, bool il, bool sp);

private:
	TextureData *loadTexture(const T_String &filename, const unsigned int &slot);
	std::vector<MaterialData*> materials;
};
}

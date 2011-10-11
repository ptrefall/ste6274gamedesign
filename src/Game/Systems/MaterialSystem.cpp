#include "MaterialSystem.h"
#include <Game/Components/Material.h>
#include <Game/Graphics/Utils.h>
#include <Game/Graphics/Uniform.h>
#include <IL/il.h>
#include <IL/ilu.h>

using namespace Systems;

MaterialSystem::MaterialSystem()
{
	glEnable(GL_TEXTURE_2D);
	ilInit();
}

MaterialSystem::~MaterialSystem()
{
	for(unsigned int i = 0; i < materials.size(); i++)
	{
		for(unsigned int j = 0; j < materials[i]->textures.size(); j++)
		{
			glDeleteTextures(1, &materials[i]->textures[j]->gl_id);
			delete materials[i]->textures[j];
		}
		delete materials[i];
	}
}

void MaterialSystem::loadMaterial(Components::Material *material, const T_String &location, const T_String &filename, const T_String &extension, bool ao, bool bu, bool di, bool il, bool sp)
{
	T_HashedString id(filename);
	//Check if this material is already loaded
	for(unsigned int i = 0; i < materials.size(); i++)
	{
		if(materials[i]->id.getId() == id.getId())
		{
			MaterialData *data = materials[i];
			material->injectData(data);
			return;
		}
	}

	//Else, let's load it!
	MaterialData *data = new MaterialData(id);
	if(ao)
	{
		T_String abs_filename = location + filename + T_String("_AO") + extension;
		TextureData *tex = loadTexture(abs_filename,0);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_ao", &tex->slot));
	}
	if(bu)
	{
		T_String abs_filename = location + filename + T_String("_BU") + extension;
		TextureData *tex = loadTexture(abs_filename,1);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_bu", &tex->slot));
	}
	if(di)
	{
		T_String abs_filename = location + filename + T_String("_DI") + extension;
		TextureData *tex = loadTexture(abs_filename,2);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_di", &tex->slot));
	}
	if(il)
	{
		T_String abs_filename = location + filename + T_String("_IL") + extension;
		TextureData *tex = loadTexture(abs_filename,3);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_il", &tex->slot));
	}
	if(sp)
	{
		T_String abs_filename = location + filename + T_String("_SP") + extension;
		TextureData *tex = loadTexture(abs_filename,4);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_sp", &tex->slot));
	}

	material->injectData(data);
	materials.push_back(data);
}

void MaterialSystem::loadMaterial(Components::SkyboxGeometry *material, const T_String &location, const T_String &filename, const T_String &extension)
{
	T_HashedString id(filename);
	//Check if this material is already loaded
	for(unsigned int i = 0; i < materials.size(); i++)
	{
		if(materials[i]->id.getId() == id.getId())
		{
			MaterialData *data = materials[i];
			material->injectData(data);
			return;
		}
	}

	//TODO: Complete impl for SkyboxGeometry!!!

	//Else, let's load it!
	MaterialData *data = new MaterialData(id);
	if(ao)
	{
		T_String abs_filename = location + filename + T_String("_AO") + extension;
		TextureData *tex = loadTexture(abs_filename,0);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_ao", &tex->slot));
	}
	if(bu)
	{
		T_String abs_filename = location + filename + T_String("_BU") + extension;
		TextureData *tex = loadTexture(abs_filename,1);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_bu", &tex->slot));
	}
	if(di)
	{
		T_String abs_filename = location + filename + T_String("_DI") + extension;
		TextureData *tex = loadTexture(abs_filename,2);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_di", &tex->slot));
	}
	if(il)
	{
		T_String abs_filename = location + filename + T_String("_IL") + extension;
		TextureData *tex = loadTexture(abs_filename,3);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_il", &tex->slot));
	}
	if(sp)
	{
		T_String abs_filename = location + filename + T_String("_SP") + extension;
		TextureData *tex = loadTexture(abs_filename,4);
		data->textures.push_back(tex);
		data->uniforms.push_back(new Graphics::Uniform(GL_UNSIGNED_INT, "tex_sp", &tex->slot));
	}

	material->injectData(data);
	materials.push_back(data);
}

TextureData *MaterialSystem::loadTexture(const T_String &filename, const unsigned int &slot)
{
	ILuint img_id;
	ilGenImages(1, &img_id);

	ilBindImage(img_id);
	int success = ilLoadImage(filename.c_str());
	if(!success)
	{
		ILenum err = ilGetError();
		return NULL_PTR;
	}

	if(ilGetInteger(IL_IMAGE_ORIGIN) != IL_ORIGIN_LOWER_LEFT)
	{     
		iluFlipImage();
	}

	success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	if(!success)
	{
		ILenum err = ilGetError();
		return NULL_PTR;
	}

	S32 bpp = ilGetInteger(IL_IMAGE_BPP);
	S32 w = ilGetInteger(IL_IMAGE_WIDTH);
	S32 h = ilGetInteger(IL_IMAGE_HEIGHT);
	S32 format = ilGetInteger(IL_IMAGE_FORMAT);
	unsigned char *bits = ilGetData();

	U32 gl_id;
	glGenTextures(1, &gl_id);
    glBindTexture(GL_TEXTURE_2D, gl_id);

	glTexImage2D(GL_TEXTURE_2D,
                 0,
                 format,
                 w,
                 h,
                 0,
                 format,
                 GL_UNSIGNED_BYTE,
                 bits);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenerateMipmap(GL_TEXTURE_2D);

	return new TextureData(gl_id, bpp, w, h, format, bits, slot);
}

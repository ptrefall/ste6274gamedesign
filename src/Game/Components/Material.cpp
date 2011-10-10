#include "Material.h"
#include <Game/Systems/MaterialSystem.h>
#include <Game/Graphics/Utils.h>
#include <Game/Graphics/Uniform.h>

using namespace Components;
using namespace Totem;

Material::Material(Entity &owner, const T_String &name, Systems::MaterialSystem &materialSystem)
: Component(owner, name), materialSystem(materialSystem), 
  loadMaterialEventId("LOAD_MATERIAL"), bindBindablesEventId("BIND_BINDABLES")
{
	owner.registerToEvent8<T_String, T_String, T_String, bool, bool, bool, bool, bool>(loadMaterialEventId).connect(this, &Material::onLoadMaterialEvent);
	owner.registerToEvent1<U32>(bindBindablesEventId).connect(this, &Material::onBindBindablesEvent);
}

Material::~Material()
{
}

void Material::update(const F32 &deltaTime)
{
	
}

void Material::onLoadMaterialEvent( const T_String &location, const T_String &filename, const T_String &extension,
									const bool &ao, const bool &bu, const bool &di, 
									const bool &il, const bool &sp)
{
	materialSystem.loadMaterial(this, location, filename, extension, ao,bu,di,il,sp);
}

void Material::onBindBindablesEvent(const U32 &program_id)
{
	glEnable(GL_TEXTURE_2D);
	for(U32 i = 0; i < data->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + data->textures[i]->slot);
		glBindTexture(GL_TEXTURE_2D, data->textures[i]->gl_id);
		data->uniforms[i]->findLocation(program_id);
		data->uniforms[i]->bind();
	}
}

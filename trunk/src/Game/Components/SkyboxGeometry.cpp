#include "SkyboxGeometry.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Game/Systems/MaterialSystem.h>
#include <Game/Graphics/Utils.h>
#include <Game/Graphics/Uniform.h>

using namespace Components;
using namespace Totem;

SkyboxGeometry::SkyboxGeometry(Entity &owner, const T_String &name, Systems::MaterialSystem &materialSystem)
: Component(owner, name), materialSystem(materialSystem), 
  loadMaterialEventId("LOAD_MATERIAL"), bindBindablesEventId("BIND_BINDABLES")
{
	indices = owner.addPropertyList<unsigned int>("Indices");
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	texCoords = owner.addPropertyList<glm::vec2>("TexCoords");

	size = owner.addProperty<F32>("Size", 4000.0f);

	owner.registerToEvent3<T_String, T_String, T_String>(loadMaterialEventId).connect(this, &SkyboxGeometry::onLoadMaterialEvent);
	owner.registerToEvent1<U32>(bindBindablesEventId).connect(this, &SkyboxGeometry::onBindBindablesEvent);

	initialize();
}

SkyboxGeometry::~SkyboxGeometry()
{
}

void SkyboxGeometry::onLoadMaterialEvent( const T_String &location, const T_String &filename, const T_String &extension)
{
	materialSystem.loadMaterial(this, location, filename, extension);
}

void SkyboxGeometry::onBindBindablesEvent(const U32 &program_id)
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


void SkyboxGeometry::initialize()
{
	unsigned int faces[12][3] = {{0,1,2}, {2,3,0}, {4,5,6}, {6,7,4}, {8,9,10}, {10,11,8}, 
								 {12,13,14}, {14,15,12}, {16,17,18}, {18,19,16}, {20,21,22}, {22,23,20} };
	for(unsigned int i = 0; i < 12; i++)
	{
		indices[i*3+0] = faces[i][0]; 
		indices[i*3+1] = faces[i][1]; 
		indices[i*3+2] = faces[i][2];
	}

	vertices.push_back(glm::vec3( size.get(), -size.get(), -size.get()));
	vertices.push_back(glm::vec3(-size.get(), -size.get(), -size.get()));
	vertices.push_back(glm::vec3(-size.get(),  size.get(), -size.get()));
	vertices.push_back(glm::vec3( size.get(),  size.get(), -size.get()));

	vertices.push_back(glm::vec3( size.get(), -size.get(),  size.get()));
	vertices.push_back(glm::vec3( size.get(), -size.get(), -size.get()));
	vertices.push_back(glm::vec3( size.get(),  size.get(), -size.get()));
	vertices.push_back(glm::vec3( size.get(),  size.get(),  size.get()));

	vertices.push_back(glm::vec3(-size.get(), -size.get(),  size.get()));
	vertices.push_back(glm::vec3( size.get(), -size.get(),  size.get()));
	vertices.push_back(glm::vec3( size.get(),  size.get(),  size.get()));
	vertices.push_back(glm::vec3(-size.get(),  size.get(),  size.get()));

	vertices.push_back(glm::vec3(-size.get(), -size.get(), -size.get()));
	vertices.push_back(glm::vec3(-size.get(), -size.get(),  size.get()));
	vertices.push_back(glm::vec3(-size.get(),  size.get(),  size.get()));
	vertices.push_back(glm::vec3(-size.get(),  size.get(), -size.get()));

	vertices.push_back(glm::vec3(-size.get(),  size.get(), -size.get()));
	vertices.push_back(glm::vec3(-size.get(),  size.get(),  size.get()));
	vertices.push_back(glm::vec3( size.get(),  size.get(),  size.get()));
	vertices.push_back(glm::vec3( size.get(),  size.get(), -size.get()));

	vertices.push_back(glm::vec3(-size.get(), -size.get(), -size.get()));
	vertices.push_back(glm::vec3(-size.get(), -size.get(),  size.get()));
	vertices.push_back(glm::vec3( size.get(), -size.get(),  size.get()));
	vertices.push_back(glm::vec3( size.get(), -size.get(), -size.get()));

	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));

	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));

	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));

	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));

	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));

	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));


}

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
  loadMaterialEventId("LOAD_MATERIAL"), bindBindablesEventId("BIND_BINDABLES"), customRendererId("CUSTOM_RENDERER")
{
	indices = owner.addPropertyList<unsigned int>("Indices");
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	texCoords = owner.addPropertyList<glm::vec2>("TexCoords");

	size = owner.addProperty<F32>("Size", 5000.0f);

	owner.registerToEvent3<T_String, T_String, T_String>(loadMaterialEventId).connect(this, &SkyboxGeometry::onLoadMaterialEvent);
	//owner.registerToEvent1<U32>(bindBindablesEventId).connect(this, &SkyboxGeometry::onBindBindablesEvent);
	
	owner.registerFunction1<const U32 &, T_Void>(customRendererId).bind(this, &SkyboxGeometry::customRenderFunc);

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

T_Void SkyboxGeometry::customRenderFunc(const U32 &program_id)
{
	GL( glEnable(GL_TEXTURE_2D); );
	U32 tex_index = 0;

	data->uniforms[tex_index]->findLocation(program_id);
	data->uniforms[tex_index]->bind();
	GL( glActiveTexture(GL_TEXTURE0 + data->textures[tex_index]->slot); );
	GL( glBindTexture(GL_TEXTURE_2D, data->textures[tex_index]->gl_id); );

	//Draw two triangles (one face) of cube, then switch texture
	
	for(U32 i = 0; i < indices.size(); i += 6)
	{
		unsigned int index0 = indices[i+0].get();
		unsigned int index1 = indices[i+1].get();
		unsigned int index2 = indices[i+2].get();

		unsigned int index3 = indices[i+3].get();
		unsigned int index4 = indices[i+4].get();
		unsigned int index5 = indices[i+5].get();

		glBegin(GL_TRIANGLES);

		glTexCoord2f(texCoords[index0].get().s, texCoords[index0].get().t);
		glVertex3f(vertices[index0].get().x, vertices[index0].get().y, vertices[index0].get().z);

		glTexCoord2f(texCoords[index1].get().s, texCoords[index1].get().t);
		glVertex3f(vertices[index1].get().x, vertices[index1].get().y, vertices[index1].get().z);

		glTexCoord2f(texCoords[index2].get().s, texCoords[index2].get().t);
		glVertex3f(vertices[index2].get().x, vertices[index2].get().y, vertices[index2].get().z);
			
		glTexCoord2f(texCoords[index3].get().s, texCoords[index3].get().t);
		glVertex3f(vertices[index3].get().x, vertices[index3].get().y, vertices[index3].get().z);

		glTexCoord2f(texCoords[index4].get().s, texCoords[index4].get().t);
		glVertex3f(vertices[index4].get().x, vertices[index4].get().y, vertices[index4].get().z);
			
		glTexCoord2f(texCoords[index5].get().s, texCoords[index5].get().t);
		glVertex3f(vertices[index5].get().x, vertices[index5].get().y, vertices[index5].get().z);

		GL( glEnd(); );
	}
	
	return (T_Void)NULL_PTR;
}

void SkyboxGeometry::initialize()
{
	unsigned int faces[12][3] = {{0,1,2}, {2,3,0}, {4,5,6}, {6,7,4}, {8,9,10}, {10,11,8}, 
								 {12,13,14}, {14,15,12}, {16,17,18}, {18,19,16}, {20,21,22}, {22,23,20} };
	indices.resize(36, 0);
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

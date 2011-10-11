#pragma once

#include <Component.h>
#include <glm/glm.hpp>

namespace Systems { struct MaterialData; class MaterialSystem; };

namespace Components
{
	class SkyboxGeometry : public Totem::Component
	{
	public:
		COMPONENT_1(SkyboxGeometry, Systems::MaterialSystem);
		SkyboxGeometry(Totem::Entity &owner, const T_String &name, Systems::MaterialSystem &materialSystem);
		virtual ~SkyboxGeometry();

		void injectData(Systems::MaterialData *data) { this->data = data; }
		Systems::MaterialData *getData() { return data; }

	private:
		void initialize();

		Systems::MaterialSystem &materialSystem;
		Systems::MaterialData *data;

		Totem::PropertyList<unsigned int> indices;
		Totem::PropertyList<glm::vec3> vertices;
		Totem::PropertyList<glm::vec2> texCoords;

		Totem::Property<F32> size;

		//Events
		T_HashedString loadMaterialEventId;
		void onLoadMaterialEvent(const T_String &location, const T_String &filename, const T_String &extension);

		T_HashedString bindBindablesEventId;
		void onBindBindablesEvent(const U32 &program_id);
	};
}

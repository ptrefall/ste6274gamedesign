#pragma once

#include <Component.h>

namespace Systems { struct MaterialData; class MaterialSystem; };

namespace Components
{
	class Material : public Totem::Component
	{
	public:
		COMPONENT_1(Material, Systems::MaterialSystem);
		Material(Totem::Entity &owner, const T_String &name, Systems::MaterialSystem &materialSystem);
		virtual ~Material();

		virtual void update(const F32 &deltaTime);

		void injectData(Systems::MaterialData *data) { this->data = data; }
		Systems::MaterialData *getData() { return data; }

	private:
		Systems::MaterialSystem &materialSystem;
		Systems::MaterialData *data;

		//Events
		T_HashedString loadMaterialEventId;
		void onLoadMaterialEvent(const T_String &location, const T_String &filename, const T_String &extension, const bool &ao, const bool &bu, const bool &di, const bool &il, const bool &sp);

		T_HashedString bindBindablesEventId;
		void onBindBindablesEvent(const U32 &program_id);
	};
}

#pragma once

#include <Component.h>
#include <glm/glm.hpp>

namespace Systems { class MeshSystem; }

namespace Components
{
	class MeshGeometry : public Factotum::Component
	{
	public:
		COMPONENT_1(MeshGeometry, Systems::MeshSystem)
		MeshGeometry(Factotum::Entity &owner, const T_String &name, Systems::MeshSystem &meshSystem);
		virtual ~MeshGeometry();

	private:
		Systems::MeshSystem &meshSystem;

		Factotum::PropertyList<unsigned int> indices;
		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> colors;
	};
}

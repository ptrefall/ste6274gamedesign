#pragma once

#include <Component.h>
#include <glm/glm.hpp>


namespace Components
{
	class MeshGeometry : public Factotum::Component
	{
	public:
		COMPONENT_0(MeshGeometry)
		MeshGeometry(Factotum::Entity &owner, const T_String &name);
		virtual ~MeshGeometry();

	private:
		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> colors;
	};
}

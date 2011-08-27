#pragma once

#include <Component.h>
#include <glm/glm.hpp>


namespace Components
{
	class MeshRenderer : public Factotum::Component
	{
	public:
		COMPONENT_0(MeshRenderer)
		MeshRenderer(Factotum::Entity &owner, const T_String &name);
		virtual ~MeshRenderer();

	private:
		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> colors;
	};
}

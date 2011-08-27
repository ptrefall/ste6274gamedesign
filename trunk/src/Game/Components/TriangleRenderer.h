#pragma once

#include <Component.h>
#include <glm/glm.hpp>

namespace Components
{
	class TriangleRenderer : public Factotum::Component
	{
	public:
		COMPONENT_0(TriangleRenderer)
		TriangleRenderer(Factotum::Entity &owner, const T_String &name);
		virtual ~TriangleRenderer();

	private:
		void initialize();

		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> colors;
		Factotum::Property<F32> size;
	};
}

#pragma once

#include <Component.h>
#include <glm/glm.hpp>

namespace Components
{
	class TriangleGeometry : public Totem::Component
	{
	public:
		COMPONENT_0(TriangleGeometry);
		TriangleGeometry(Totem::Entity &owner, const T_String &name);
		virtual ~TriangleGeometry();

	private:
		void initialize();

		Totem::PropertyList<unsigned int> indices;
		Totem::PropertyList<glm::vec3> vertices;
		Totem::PropertyList<glm::vec3> colors;

		Totem::Property<F32> size;

		
	};
}

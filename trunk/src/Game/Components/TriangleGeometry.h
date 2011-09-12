#pragma once

#include <Component.h>
#include <glm/glm.hpp>

namespace Components
{
	class TriangleGeometry : public Factotum::Component
	{
	public:
		COMPONENT_0(TriangleGeometry);
		TriangleGeometry(Factotum::Entity &owner, const T_String &name);
		virtual ~TriangleGeometry();

	private:
		void initialize();

		Factotum::PropertyList<unsigned int> indices;
		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> colors;

		Factotum::Property<F32> size;

		
	};
}

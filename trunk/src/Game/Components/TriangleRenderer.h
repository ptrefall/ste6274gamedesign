#pragma once

#include <Component.h>
#include <glm/glm.hpp>

namespace Systems { class RenderSystem; }
namespace Components
{
	class TriangleRenderer : public Factotum::Component
	{
	public:
		COMPONENT_1(TriangleRenderer, Systems::RenderSystem)
		TriangleRenderer(Factotum::Entity &owner, const T_String &name, Systems::RenderSystem &renderSystem);
		virtual ~TriangleRenderer();

	private:
		void initialize();

		Systems::RenderSystem &renderSystem;

		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> colors;

		Factotum::Property<U32> render_group;
		Factotum::Property<F32> size;
	};
}

#pragma once

#include <Component.h>
#include <glm/glm.hpp>


namespace Systems { class RenderSystem; }
namespace Components
{
	class Renderable : public Factotum::Component
	{
	public:
		COMPONENT_1(Renderable, Systems::RenderSystem)
		Renderable(Factotum::Entity &owner, const T_String &name, Systems::RenderSystem &renderSystem);
		virtual ~Renderable();

		void compile();
		void render();

		const T_String &getRenderGroup();
		const bool &isCompiled() const { return compiled; }

	private:
		Systems::RenderSystem &renderSystem;

		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> colors;

		Factotum::Property<U32> render_group;
		Factotum::Property<bool> compiled;
	};
}

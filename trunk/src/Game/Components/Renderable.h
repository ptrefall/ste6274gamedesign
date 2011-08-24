#pragma once

#include <Component.h>

namespace Systems { class RenderSystem; }
namespace Components
{
	class Renderable : public Factotum::Component
	{
	public:
		COMPONENT_1(Renderable, Systems::RenderSystem)
		Renderable(Factotum::Entity &owner, const T_String &name, Systems::RenderSystem &renderSystem);
		virtual ~Renderable();

		void render();

	private:
		Systems::RenderSystem &renderSystem;
	};
}
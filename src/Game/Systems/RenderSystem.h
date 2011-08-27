#pragma once

#include <types_config.h>

namespace Components { class Renderable; }

namespace Systems
{

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void addRenderable(Components::Renderable *renderable);
	void compile();
	void render();

private:
	T_Vector<Components::Renderable*>::Type renderables;
};

}

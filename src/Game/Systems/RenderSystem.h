#pragma once

#include <types_config.h>
#include <Game/Graphics/ShaderSystem.h>

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

	Graphics::ShaderSystem &getShaderSystem() { return shaderSystem; }

private:
	T_Vector<Components::Renderable*>::Type renderables;
	Graphics::ShaderSystem shaderSystem;
};

}

#include "TriangleRenderer.h"
#include "../Systems/RenderSystem.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>

using namespace Components;
using namespace Factotum;

TriangleRenderer::TriangleRenderer(Entity &owner, const T_String &name, Systems::RenderSystem &renderSystem)
: Component(owner, name), renderSystem(renderSystem)
{
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	colors = owner.addPropertyList<glm::vec3>("Colors");

	render_group = owner.addProperty<U32>("RenderGroup", T_HashedString("Triangle").getId());
	size = owner.addProperty<F32>("Size", 2.0f);

	if(renderSystem.hasGroup(render_group.get()) == false)
	{
		initialize(); //We want to render triangles instanced, so only initialize once for the render group....
		renderSystem.addGroup(render_group.get(), true);
	}
	else
		renderSystem.incrementGroup(render_group.get());
}

TriangleRenderer::~TriangleRenderer()
{
}

void TriangleRenderer::initialize()
{
	vertices.push_back(glm::vec3(-size.get(), 0.0f, -4.0f));
	vertices.push_back(glm::vec3(size.get(), 0.0f, -4.0f));
	vertices.push_back(glm::vec3(0.0f, size.get(), -4.0f));

	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
}

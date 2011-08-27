#include "Renderable.h"
#include "../Systems/RenderSystem.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>

using namespace Components;
using namespace Factotum;

Renderable::Renderable(Entity &owner, const T_String &name, Systems::RenderSystem &renderSystem)
: Component(owner, name), renderSystem(renderSystem)
{
	renderSystem.addRenderable(this);

	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	colors = owner.addPropertyList<glm::vec3>("Colors");

	render_group = owner.addProperty<T_String>("RenderGroup", "None");
	compiled = owner.addProperty<bool>("Compiled", false);
}

Renderable::~Renderable()
{
}

void Renderable::compile()
{
	compiled = true;
}

void Renderable::render()
{
	if(vertices.empty() || vertices.size() != colors.size())
		return;

	glBegin(GL_TRIANGLES);
	for(U32 i = 0; i < vertices.size(); i++)
	{
		const glm::vec3 &vertex = vertices[i].get();
		const glm::vec3 &color = colors[i].get();
		glColor4f(color.r, color.g, color.b, 1.0f);
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}
	glEnd();
}

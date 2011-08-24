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
}

Renderable::~Renderable()
{
}

void Renderable::render()
{
	glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex3f(-2.0f, 0.0f, -4.0f);
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex3f(2.0f, 0.0f, -4.0f);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 2.0f, -4.0f);
	glEnd();

}

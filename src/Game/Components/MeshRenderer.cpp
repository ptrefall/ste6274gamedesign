#include "MeshRenderer.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>

using namespace Components;
using namespace Factotum;

MeshRenderer::MeshRenderer(Entity &owner, const T_String &name)
: Component(owner, name)
{
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	colors = owner.addPropertyList<glm::vec3>("Colors");

	render_group = owner.addProperty<U32>("RenderGroup", T_HashedString("Mesh").getId());
}

MeshRenderer::~MeshRenderer()
{
}

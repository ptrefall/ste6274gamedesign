#include "TriangleGeometry.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace Components;
using namespace Factotum;

TriangleGeometry::TriangleGeometry(Entity &owner, const T_String &name)
: Component(owner, name)
{
	indices = owner.addPropertyList<unsigned int>("Indices");
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	colors = owner.addPropertyList<glm::vec3>("Colors");

	size = owner.addProperty<F32>("Size", 2.0f);

	initialize(); //We want to render triangles instanced, so only initialize once for the render group....
}

TriangleGeometry::~TriangleGeometry()
{
}

void TriangleGeometry::initialize()
{
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	vertices.push_back(glm::vec3(-size.get(), 0.0f, -8.0f));
	vertices.push_back(glm::vec3(size.get(), 0.0f, -8.0f));
	vertices.push_back(glm::vec3(0.0f, size.get(), -8.0f));

	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
}

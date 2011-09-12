#include "MeshGeometry.h"

using namespace Components;
using namespace Factotum;

MeshGeometry::MeshGeometry(Entity &owner, const T_String &name)
: Component(owner, name)
{
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	colors = owner.addPropertyList<glm::vec3>("Colors");
}

MeshGeometry::~MeshGeometry()
{
}

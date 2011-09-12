#include "MeshGeometry.h"
#include <Game/Systems/MeshSystem.h>

using namespace Components;
using namespace Factotum;

MeshGeometry::MeshGeometry(Entity &owner, const T_String &name, Systems::MeshSystem &meshSystem)
: Component(owner, name), meshSystem(meshSystem)
{
	meshSystem.addMesh(this);

	indices = owner.addPropertyList<unsigned int>("Indices");
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	colors = owner.addPropertyList<glm::vec3>("Colors");
}

MeshGeometry::~MeshGeometry()
{
}

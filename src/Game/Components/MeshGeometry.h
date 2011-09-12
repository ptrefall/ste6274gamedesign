#pragma once

#include <Component.h>
#include <glm/glm.hpp>
#include <aiMesh.h>

namespace Systems { class MeshSystem; }

namespace Components
{
	class MeshGeometry : public Factotum::Component
	{
	public:
		COMPONENT_1(MeshGeometry, Systems::MeshSystem)
		MeshGeometry(Factotum::Entity &owner, const T_String &name, Systems::MeshSystem &meshSystem);
		virtual ~MeshGeometry();

		void injectData(const aiMesh &mesh_data);

	private:
		Systems::MeshSystem &meshSystem;

		Factotum::PropertyList<unsigned int> indices;
		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> normals;
		Factotum::PropertyList<glm::vec3> tangents;
		Factotum::PropertyList<glm::vec3> colors;
		Factotum::PropertyList<glm::vec2> texCoords;

		//Events
		T_HashedString loadMeshEventId;
		void onLoadMeshEvent(const T_String &location, const T_String &filename);
	};
}

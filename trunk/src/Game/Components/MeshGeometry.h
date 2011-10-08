#pragma once

#include <Component.h>
#include <glm/glm.hpp>
#include <aiMesh.h>

namespace Systems { class MeshSystem; }

namespace Components
{
	class MeshGeometry : public Totem::Component
	{
	public:
		COMPONENT_1(MeshGeometry, Systems::MeshSystem)
		MeshGeometry(Totem::Entity &owner, const T_String &name, Systems::MeshSystem &meshSystem);
		virtual ~MeshGeometry();

		void injectData(const aiMesh &mesh_data);

	private:
		Systems::MeshSystem &meshSystem;

		Totem::PropertyList<unsigned int> indices;
		Totem::PropertyList<glm::vec3> vertices;
		Totem::PropertyList<glm::vec3> normals;
		Totem::PropertyList<glm::vec3> tangents;
		Totem::PropertyList<glm::vec3> colors;
		Totem::PropertyList<glm::vec2> texCoords;

		//Events
		T_HashedString loadMeshEventId;
		void onLoadMeshEvent(const T_String &location, const T_String &filename);
	};
}

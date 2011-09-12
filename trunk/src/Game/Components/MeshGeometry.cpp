#include "MeshGeometry.h"
#include <Game/Systems/MeshSystem.h>

using namespace Components;
using namespace Factotum;

MeshGeometry::MeshGeometry(Entity &owner, const T_String &name, Systems::MeshSystem &meshSystem)
: Component(owner, name), meshSystem(meshSystem), loadMeshEventId("LOAD_MESH")
{
	indices = owner.addPropertyList<unsigned int>("Indices");
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	normals = owner.addPropertyList<glm::vec3>("Normals");
	tangents = owner.addPropertyList<glm::vec3>("Tangents");
	colors = owner.addPropertyList<glm::vec3>("Colors");
	texCoords = owner.addPropertyList<glm::vec2>("TexCoords");

	owner.registerToEvent2<T_String, T_String>(loadMeshEventId).connect(this, &MeshGeometry::onLoadMeshEvent);
}

MeshGeometry::~MeshGeometry()
{
}

void MeshGeometry::onLoadMeshEvent(const T_String &location, const T_String &filename)
{
	meshSystem.loadMesh(this, location, filename);
}

void MeshGeometry::injectData(const aiMesh &mesh_data)
{
	for(unsigned int i = 0; i < mesh_data.mNumFaces; i++)
	{
		for(unsigned int j = 0; j < mesh_data.mFaces[i].mNumIndices; j++)
		{
			indices.push_back(mesh_data.mFaces[i].mIndices[j]);
		}
	}

	for(unsigned int i = 0; i < mesh_data.mNumVertices; i++)
	{
		vertices.push_back(glm::vec3(mesh_data.mVertices[i][0], mesh_data.mVertices[i][1], mesh_data.mVertices[i][2]));
		normals.push_back(glm::vec3(mesh_data.mNormals[i][0], mesh_data.mNormals[i][1], mesh_data.mNormals[i][2]));

		if(mesh_data.HasTextureCoords(0))
			texCoords.push_back(glm::vec2(mesh_data.mTextureCoords[0][i][0], mesh_data.mTextureCoords[0][i][1]));

		if(mesh_data.HasTangentsAndBitangents())
			tangents.push_back(glm::vec3(mesh_data.mTangents[i][0], mesh_data.mTangents[i][1], mesh_data.mTangents[i][2]));
	}
}

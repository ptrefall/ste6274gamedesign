#pragma once

#include <types_config.h>
#include <aiMesh.h>
#include <aiScene.h>
namespace Assimp { class Importer; }

namespace Components { class MeshGeometry; }

namespace Systems
{

class MeshSystem
{
public:
	MeshSystem();
	~MeshSystem();

	void addMesh(Components::MeshGeometry *mesh);

	//Mesh *createMesh(const T_String &relative_path, const T_String &filename, bool loadTextures);
	//std::vector<Mesh*> createMesh(const T_String &relative_path, const T_String &filename, Renderer::Shader &shader, bool loadTextures);

private:
	//Mesh *copyMesh(Mesh *mesh, Renderer::Shader &shader, const T_String &name);

	Assimp::Importer *importer;

	///
	std::vector<Components::MeshGeometry*> meshes;
};
}

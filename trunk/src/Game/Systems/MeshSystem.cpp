#include "MeshSystem.h"

//AssImp includes
#include <assimp.hpp>
#include <aiPostProcess.h>

using namespace Systems;

MeshSystem::MeshSystem()
: importer(new Assimp::Importer())
{
}

MeshSystem::~MeshSystem()
{
}

void MeshSystem::addMesh(Components::MeshGeometry *mesh)
{
#if _DEBUG
	if(mesh == NULL_PTR)
		return; //BAD CODER!

	for(U32 i = 0; i < meshes.size(); i++)
	{
		if(meshes[i] == mesh)
			return; //Already exist! BAD, BAD CODER!
	}
#endif

	meshes.push_back(mesh);
}

/*Mesh *MeshSystem::createMesh(const CL_String &relative_path, const CL_String &filename, Renderer::Shader &shader, bool loadTextures, const unsigned int &mesh_index)
{
	//Each sub-mesh in file get's it's own mesh based on mesh index.
	CL_String name = cl_format("%1%2", filename, mesh_index);

	//Check if this sub-mesh is already loaded
	for(unsigned int i = 0; i < meshes.size(); i++)
	{
		if(meshes[i]->getName() == name)
		{
			return copyMesh(meshes[i], shader, name);
		}
	}

	CL_String abs_filename = cl_format("%1%2/%3", engine.getFileSystem().getRootPath(), relative_path, filename);
	
	const aiScene *scene = importer->ReadFile(abs_filename.c_str(), aiProcessPreset_TargetRealtime_Quality);
	if(scene == 0x0)
	{
		CL_Console::write_line(cl_format("Failed to load mesh from file: %1", abs_filename));
		return 0x0;
	}

	if(scene->mNumMeshes > 1)
		CL_Console::write_line(cl_format("Warning: You've asked to load a single mesh from %1, but %2 meshes was found in file!", filename, scene->mNumMeshes));

	aiMesh *ai_mesh = scene->mMeshes[mesh_index];
	if(ai_mesh == 0x0)
	{
		CL_Console::write_line(cl_format("Failed to load mesh with index %1 from file: %2", mesh_index, abs_filename));
		return 0x0;
	}

	int num_siblings = scene->mNumMeshes - 1;
	Mesh *mesh = new Mesh(engine, shader, name, ai_mesh, num_siblings);
	meshes.push_back(mesh);
	return mesh;
}

std::vector<Mesh*> MeshSystem::createMesh(const CL_String &relative_path, const CL_String &filename, Renderer::Shader &shader, bool loadTextures)
{
	std::vector<Mesh*> mesh_list;
	std::vector<int> mesh_indices_to_load;

	//Each sub-mesh in file get's it's own mesh based on mesh index.
	CL_String name = cl_format("%1%2", filename, 0);

	//Check if this sub-mesh is already loaded
	for(unsigned int i = 0; i < meshes.size(); i++)
	{
		//If we found a match, gather all siblings 
		if(meshes[i]->getName() == name)
		{
			//Found first mesh, so push it on the list
			mesh_list.push_back(copyMesh(meshes[i], shader, name));

			int num_siblings = meshes[i]->getNumSiblings();

			//If it has no siblings, just pack this single mesh into the array and return
			if(num_siblings <= 0)
				return mesh_list;
			else
			{
				unsigned int num_meshes = num_siblings+1;
				//We need to resize the mesh_list, so that each sub-mesh is listed in sequential order.
				//We temporarily set the first mesh (0) as the value of these, which should later be
				//overwritten with the correct meshes.
				mesh_list.resize(num_meshes, meshes[i]); 
				//We're not guaranteed that all siblings have been loaded, we're not even guaranteed they're
				//loaded in sequential order, so pack all that has been loaded, and then load any remainding
				//sub-meshes, if there is any...
				int mesh_index = 1; //already found 0, so start on 1
				CL_String sub_name = cl_format("%1%2", filename, mesh_index);

				//We need to register which meshes we find in this search process,
				//so that we can load the rest afterward.
				std::vector<bool> found(num_meshes, false);
				int num_found = 1;

				for(unsigned int j = 0; j < meshes.size(); j++)
				{
					if(meshes[j]->getName() == sub_name)
					{
						found[mesh_index] = true;
						num_found++;

						mesh_list[mesh_index] = copyMesh(meshes[j], shader, name); //Insert at correct location

						//If we have foudn all the meshes we were looking for, break.
						if(num_found == num_meshes)
							break;

						mesh_index++;
						sub_name = cl_format("%1%2", filename, mesh_index);
					}
				}

				//If we found all meshes, return the list of meshes.
				if(num_found == num_meshes)
					return mesh_list;
				//Else, we break out of the for-loop, so that we can
				//load the rest
				else
				{
					//Before we start loading sub-meshes, regiser which sub-meshes
					//we need to load
					for(unsigned int j = 0; j < found.size(); j++)
					{
						if(found[j] == false)
							mesh_indices_to_load.push_back(j);
					}
					break;
				}
			}
		}
	}

	CL_String abs_filename = cl_format("%1%2/%3", engine.getFileSystem().getRootPath(), relative_path, filename);
	
	const aiScene *scene = importer->ReadFile(abs_filename.c_str(), aiProcessPreset_TargetRealtime_Quality);
	if(scene == 0x0)
	{
		CL_Console::write_line(cl_format("Failed to load mesh from file: %1", abs_filename));
		mesh_list.clear();
		return mesh_list;
	}
	
	unsigned int num_meshes = scene->mNumMeshes;
	int num_siblings = num_meshes - 1;

	//If no meshes for his mesh file has been loaded previously,
	//We'll load everything!
	if(mesh_list.empty())
	{
		for(unsigned int mesh_index = 0; mesh_index < num_meshes; mesh_index++)
		{
			aiMesh *ai_mesh = scene->mMeshes[mesh_index];
			if(ai_mesh == 0x0)
			{
				CL_Console::write_line(cl_format("Failed to load mesh with index %1 from file: %2", mesh_index, abs_filename));
				mesh_list.clear();
				return mesh_list;
			}

			name = cl_format("%1%2", filename, mesh_index);

			Mesh *mesh = new Mesh(engine, shader, name, ai_mesh, num_siblings);
			meshes.push_back(mesh);
			mesh_list.push_back(mesh);
		}
	}
	else
	{
		for(unsigned int i = 0; i < mesh_indices_to_load.size(); i++)
		{
			unsigned int mesh_index = mesh_indices_to_load[i];
			aiMesh *ai_mesh = scene->mMeshes[mesh_index];
			if(ai_mesh == 0x0)
			{
				CL_Console::write_line(cl_format("Failed to load mesh with index %1 from file: %2", mesh_index, abs_filename));
				mesh_list.clear();
				return mesh_list;
			}

			name = cl_format("%1%2", filename, mesh_index);

			Mesh *mesh = new Mesh(engine, shader, name, ai_mesh, num_siblings);
			meshes.push_back(mesh);
			mesh_list[mesh_index] = mesh;
		}
	}
	return mesh_list;
}

Mesh *MeshSystem::copyMesh(Mesh *mesh, Renderer::Shader &shader, const CL_String &name)
{
	Renderer::IRenderParams &params = mesh->getRenderParams();
	return new Mesh(engine, shader, name, params, mesh->getNumSiblings());
}
*/
#include "Globals.h"
#include "ModuleMesh3D.h"
#include "BaseMesh.h"

#include "Assimp/Assimp/include/cimport.h"
#include "Assimp/Assimp/include/scene.h"
#include "Assimp/Assimp/include/postprocess.h"

#pragma comment (lib, "Assimp/Assimp/libx86/assimp.lib")

ModuleMesh3D::ModuleMesh3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleMesh3D::~ModuleMesh3D()
{
}

bool ModuleMesh3D::Start()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);


	return true;
}

update_status ModuleMesh3D::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleMesh3D::Update(float dt)
{
	for (uint i = 0; i < meshes.size(); i++) {
		meshes[i]->Draw();
	}

	return UPDATE_CONTINUE;
}

update_status ModuleMesh3D::PostUpdate(float dt)
{

	return UPDATE_CONTINUE; 
}

bool ModuleMesh3D::LoadFBX(const char* filepath)
{
	bool ret = false;

	aiMesh* new_mesh = nullptr;

	const aiScene* scene = aiImportFile(filepath, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {
		//Use scene.mNumMesh to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++) {

			ourMesh = new BaseMesh();
			new_mesh = scene->mMeshes[i];

			ourMesh->mesh.num_vertex = new_mesh->mNumVertices;
			ourMesh->mesh.vertex = new float[ourMesh->mesh.num_vertex * 3];

			memcpy(ourMesh->mesh.vertex, new_mesh->mVertices, sizeof(float) * ourMesh->mesh.num_vertex * 3);

			LOG("New mesh with %d vertices", ourMesh->mesh.num_vertex);

			if (new_mesh->HasFaces()) {
				ourMesh->mesh.num_index = new_mesh->mNumFaces * 3;
				ourMesh->mesh.index = new uint[ourMesh->mesh.num_index]; // assume each face is a triangle
				
				for (uint j = 0; j < new_mesh->mNumFaces; j++)
				{
					if (new_mesh->mFaces[j].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else {
						memcpy(&ourMesh->mesh.index[j * 3], new_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
				ourMesh->GenerateNewBuffer();
				meshes.push_back(ourMesh);
			}
		}

		aiReleaseImport(scene);

	}

	return ret;
}

bool ModuleMesh3D::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

void ModuleMesh3D::DestroyAllMeshes()
{
	for (uint i = 0; i < meshes.size(); i++) {
		meshes[i]->Clear();
	}
	meshes.clear();
}

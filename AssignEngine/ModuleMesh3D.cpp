#include "Application.h"
#include "Globals.h"
#include "ModuleMesh3D.h"
#include "BaseMesh.h"
#include "ModuleTexture3D.h"

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

bool ModuleMesh3D::LoadFBX(const char* filepath, char* texturepath)
{
	bool ret = false;

	aiMesh* new_mesh = nullptr;
	const aiScene* scene = aiImportFile(filepath, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {
		//Use scene.mNumMesh to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++) {

			ourMesh = new BaseMesh(false);
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
				if (new_mesh->HasTextureCoords(0)) {
					ourMesh->mesh.texCoords = new float[ourMesh->mesh.num_vertex * 2];
					for (uint k = 0; k < new_mesh->mNumVertices; k++) {
						ourMesh->mesh.texCoords[k * 2] = new_mesh->mTextureCoords[0][k].x;
						ourMesh->mesh.texCoords[k * 2+1] = new_mesh->mTextureCoords[0][k].y;
					}
					if (texturepath != nullptr) {
						ourMesh->mesh.texPath = texturepath;
						ourMesh->mesh.imageID = App->texture->LoadTexture(ourMesh->mesh.texPath);
					}
					else {
						ourMesh->AssignCheckersImage();
					}
				}
				if (new_mesh->HasNormals()) {
					ourMesh->mesh.normals = new float[ourMesh->mesh.num_vertex * 3];
					memcpy(ourMesh->mesh.normals, new_mesh->mNormals, sizeof(float) * ourMesh->mesh.num_vertex * 3);
				}

				ourMesh->GenerateNewBuffer();
				meshes.push_back(ourMesh);
			}
		}
		aiReleaseImport(scene);
	}
	return ret;
}

void ModuleMesh3D::ShowWire(bool wires)
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->SetWireframe(wires);
	}
}

void ModuleMesh3D::ShowNormals()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->SeeNormalsFace();
		meshes[i]->SeeNormalsVertex();
	}
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

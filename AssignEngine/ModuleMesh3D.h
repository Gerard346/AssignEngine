#pragma once

#include "Module.h"
#include "Globals.h"
#include "BaseMesh.h"

#include <vector>

class ModuleMesh3D : public Module{
public:
	ModuleMesh3D(Application* app, bool start_enabled = true);
	~ModuleMesh3D();

	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool LoadFBX(const char*);

	bool CleanUp();

	void DestroyAllMeshes();
private:
	std::vector<BaseMesh*> meshes;
	BaseMesh* ourMesh = nullptr;

};
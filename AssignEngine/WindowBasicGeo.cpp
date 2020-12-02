#include "Application.h"
#include "WindowBasicGeo.h"

WindowBasicGeo::WindowBasicGeo() :ModuleUIManager()
{
	isActive.push_back(Activate());
}

WindowBasicGeo::~WindowBasicGeo()
{
	isActive.clear();
}

bool WindowBasicGeo::Start()
{

	return true;
}

update_status WindowBasicGeo::Update(float dt)
{
	if (isActive[0].isActivate) {
		bool* p = &isActive[0].isActivate;
		Draw("Config Window", p);

	}

	return UPDATE_CONTINUE;
}

bool WindowBasicGeo::CleanUp()
{
	return true;
}

void WindowBasicGeo::Draw(const char* title, bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_FirstUseEver);

	ImGui::Begin("3D Models generator", p_open);

	if (ImGui::CollapsingHeader("Basic primitives")){
		if (ImGui::Button("Cube")) {
			LOG("Loading Cube");
			App->mesh->LoadFBX("Engine/Assets/Basic_Primitives/Cube.fbx");
		}
		if (ImGui::Button("Sphere")) {
			LOG("Loading Sphere");
			App->mesh->LoadFBX("Engine/Assets/Basic_Primitives/Sphere.fbx");
		}
		if (ImGui::Button("Pyramid")) {
			LOG("Loading Pyramid");
			App->mesh->LoadFBX("Engine/Assets/Basic_Primitives/Pyramid.fbx");
		}
		if (ImGui::Button("Cylinder")) {
			LOG("Loading Cylinder");
			App->mesh->LoadFBX("Engine/Assets/Basic_Primitives/Cylinder.fbx");
		}
	}

	if(ImGui::CollapsingHeader("Models")) {

		if (ImGui::Button("Suzanne")) {
			LOG("Loading Suzanne");
			//App->mesh->LoadFBX("Engine/Assets/Suzanne.fbx");
		}
		if (ImGui::Button("House")) {
			LOG("Loading House");
			//App->mesh->LoadFBX("Engine/Assets/BakerHouse.fbx");
		}
		if (ImGui::Button("Bolt")) {
			LOG("Loading Bolt");
			//App->mesh->LoadFBX("Engine/Assets/Bolt.fbx");
		}
	}
	if (ImGui::CollapsingHeader("Clear All Meshes")) {
		if (ImGui::Button("ClearMeshes")) {
			App->mesh->DestroyAllMeshes();
			LOG("Clearing all meshes from engine.");
		}
	}

	ImGui::End();


	

}


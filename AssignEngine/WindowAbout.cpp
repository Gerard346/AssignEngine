#include "Application.h"
#include "WindowAbout.h"
#include "SDL\include\SDL.h"

WindowAbout::WindowAbout() : ModuleUIManager()
{
	isActive.push_back(Activate());

}

WindowAbout::~WindowAbout()
{
	isActive.clear();
}

bool WindowAbout::Start()
{
	return true;
}

update_status WindowAbout::Update(float dt)
{
	if (isActive[0].isActivate == true) {
		if (ImGui::Begin("About"), true, ImGuiWindowFlags_AlwaysAutoResize) {
			ImGui::Text("Name: Assign Engine v0.1");
			ImGui::Separator();
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			ImGui::Text("3D engine for the University");
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			if (ImGui::Button("Github Page")) {
				ShellExecuteA(NULL, "open", "https://github.com/Gerard346/AssignEngine", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			ImGui::Text("Gerard Gil");

			ImGui::Separator();
			ImGui::Text("3rd Party Libraries used: ");
			ImGui::Text("SDL 2.0.12");
			ImGui::Text("ImGui: %s", ImGui::GetVersion());
			ImGui::Text("Gerard Gil");
			ImGui::Text("Gerard Gil");

			ImGui::End();
		}
	}
	
	return UPDATE_CONTINUE;
}

bool WindowAbout::CleanUp()
{
	return true;
}

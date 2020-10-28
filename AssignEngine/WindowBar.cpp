#include "Application.h"
#include "WindowBar.h"
#include "SDL\include\SDL.h"

WindowBar::WindowBar() : ModuleUIManager()
{
	isActive.push_back(Activate());
}

WindowBar::~WindowBar()
{
	isActive.clear();
}

bool WindowBar::Start()
{
	return true;
}

update_status WindowBar::Update(float dt)
{
	if (isActive[0].isActivate == true) {
		//File Menu
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New")) {

				}
				if (ImGui::MenuItem("Exit")) {
					SDL_Event quit;
					quit.type = SDL_QUIT;
					SDL_PushEvent(&quit);
				}
				ImGui::EndMenu();
			}
		}
		//Window Menu
		if (ImGui::BeginMenu("Window")) {
			if (ImGui::MenuItem("Configuration")) {

			}
			if (ImGui::MenuItem("Console")) {

			}
			ImGui::EndMenu();
		}
		//Help
		if (ImGui::BeginMenu("Info")) {
			if (ImGui::MenuItem("Github")) {

			}
			if (ImGui::MenuItem("About")) {

			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	else {

	}
	return UPDATE_CONTINUE;
}

bool WindowBar::CleanUp()
{
	return true;
}

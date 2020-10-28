#include "Application.h"
#include "WindowBar.h"
#include "SDL\include\SDL.h"
#include "WindowAbout.h"
#include "Glew/include/glew.h"

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
	UI_SubBar.push_back(new WindowAbout());

	std::vector<ModuleUIManager*>::iterator ui_windows_bar = UI_SubBar.begin();

	for (int i = 0; i < UI_SubBar.size(); i++) {
		ui_windows_bar[i]->Start();
	}

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
			ImGui::Text("Name: Assign Engine v0.1");

			ImGui::Separator();

			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			ImGui::Text("3D engine for the University");
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			if (ImGui::Button("Github Page")) {
				ShellExecuteA(NULL, "open", "https://github.com/Gerard346/AssignEngine", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			if (ImGui::Button("by Gerard Gil")) {
				ShellExecuteA(NULL, "open", "https://github.com/Gerard346", NULL, NULL, SW_SHOWNORMAL);
			}

			ImGui::Separator();

			ImGui::Text("3rd Party Libraries used: ");
			ImGui::Text("SDL Version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
			ImGui::Text("ImGui: %s", ImGui::GetVersion());
			GLint gl_major_version, gl_minor_version;
			glGetIntegerv(GL_MAJOR_VERSION, &gl_major_version); glGetIntegerv(GL_MINOR_VERSION, &gl_minor_version);
			ImGui::Text("OpenGL: %d. %d", gl_major_version, gl_minor_version);
			ImGui::Text("Glew: %d.%d", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
			ImGui::Text("MathGeoLib: 1.5");

			ImGui::Separator();

			ImGui::Text("License: ");
			ImGui::Text("MIT License: ");
			ImGui::Text("Copyright (c) 2020 Gerard346");
			ImGui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy"
				"of this software and associated documentation files(the Software), to deal"
				"in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell"
				"copies of the Software, and to permit persons to whom the Software is" 
				"furnished to do so, subject to the following conditions: ");
			ImGui::TextWrapped("The above copyright notice and this permission notice shall be included in all"
				"copies or substantial portions of the Software.");
			ImGui::TextWrapped("THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR"
				"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,"
				"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE"
				"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
				"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,"
				"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE"
				"SOFTWARE.");
			
			ImGui::EndMenu();

		}
		ImGui::EndMainMenuBar();

		UpdateChilds(dt);
	}
	else {

	}
	return UPDATE_CONTINUE;
}

bool WindowBar::CleanUp()
{
	return true;
}

void WindowBar::UpdateChilds(float dt)
{
	std::vector<ModuleUIManager*>::iterator ui_windows = UI_SubBar.begin();

	for (int i = 0; i < UI_SubBar.size(); i++) {
		ui_windows[i]->Update(dt);
	}
}

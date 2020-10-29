#include "Application.h"
#include "Globals.h"
#include "ModuleUI.h"
#include "imgui\imgui.h"
#include "SDL\include\SDL.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"
#include "Glew/include/glew.h"

#include "MathGeoLib/include/Algorithm/Random/LCG.h"

#include "WindowConsole.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	//Init Glew
	glewInit();
	//Setup Dear ImGui Context
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	/*
	std::vector<ModuleUIManager*>::iterator ui_windows = UIManager.begin();

	for (int i = 0; i < UIManager.size(); i++) {
		ui_windows[i]->Start();
	}
	*/
	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	

	ImGui::ShowDemoWindow();
	DrawUIBar();
	UpdateUI(dt);

	/*
	//	RNG Generator

	ImGui::Begin("RNG Generator");
	ImGui::Spacing();
	ImGui::PushItemWidth(0.67);

	static int rng_min;
	static int rng_max;

	ImGui::PushItemWidth(80);
	ImGui::Text("Put the range values of the random number you want:	");
	ImGui::InputInt("Min", &rng_min); ImGui::SameLine();
	ImGui::InputInt("Max", &rng_max);
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("Click if you want an RNG int or a float: ");

	if (ImGui::Button("Int")) {
		rng_intT = true;
		rng_int = rng_generator.Int(rng_min, rng_max);
	}
	ImGui::SameLine();
	if (ImGui::Button("Float")) {
		rng_intT = false;
		rng_float = rng_generator.Float(rng_min, rng_max);
	}

	if (rng_intT == true) {
		ImGui::Text("%i", rng_int);
	}
	else {
		ImGui::Text("%f", rng_float);
	}

	ImGui::End();
	*/
	//Render
	
	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading UI");

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(App->renderer3D->context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}

void ModuleUI::UpdateUI(float dt)
{
	std::vector<ModuleUIManager*>::iterator ui_windows = UIManager.begin();

	for (int i = 0; i < UIManager.size(); i++) {
		ui_windows[i]->Update(dt);
	}
}

void ModuleUI::DrawUIBar()
{
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
				App->console->OpenConsole();
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
}

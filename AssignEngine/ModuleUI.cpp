#include "Application.h"
#include "Globals.h"
#include "ModuleUI.h"
#include "imgui\imgui.h"
#include "SDL\include\SDL.h"
#include "ImGui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "WindowConfiguration.h"
#include "WindowConsole.h"
#include "WindowBasicGeo.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	//Setup Dear ImGui Context
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	
	UIManager.push_back(new WindowConfiguration());
	UIManager.push_back(new WindowBasicGeo());

	UIManager[Congifuration_Window]->isActive[0].isActivate = false;
	UIManager[BasicPrimitives_Window]->isActive[0].isActivate = false;

	std::vector<ModuleUIManager*>::iterator ui_windows = UIManager.begin();

	for (int i = 0; i < UIManager.size(); i++) {
		ui_windows[i]->Start();
	}
	
	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	
	Dockspace(p_open);

	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	
	
	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	
	
	return UPDATE_CONTINUE;
}

void ModuleUI::DrawUI(float dt)
{
	DrawUIBar();
	UpdateUI(dt);

	//	RNG Generator
	/*
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
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
	SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(backup_current_window, backup_current_context);

	//Render
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
				UIManager[Congifuration_Window]->isActive[0].OpenWindow();
			}
			if (ImGui::MenuItem("Console")) {
				App->console->OpenConsole();
			}
			if (ImGui::MenuItem("Basic Primitives")) {
				UIManager[BasicPrimitives_Window]->isActive[0].OpenWindow();
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

void ModuleUI::Dockspace(bool *p_open)
{
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	ImGui::End();

}

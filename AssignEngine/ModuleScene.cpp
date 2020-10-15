#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Primitive.h"
#include "Glew/include/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"
#include "MathGeoLib/include/Algorithm/Random/LCG.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	//Init Glew
	glewInit();
	//Setup Dear ImGui Context
	ImGui::CreateContext();
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);



	App->camera->Move(vec3(0, 30, -30));

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(App->renderer3D->context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}

// Update: draw background
update_status ModuleScene::Update(float dt)
{
	Plane_Obj(0, 1, 0, 0).Render();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

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
	
	//Show demo window
	ImGui::ShowDemoWindow();

	//Quit
	ImGui::Begin("Quit");
	if (ImGui::Button("Exit")) {
		return UPDATE_STOP;
	}
	ImGui::End();

	//Render
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Primitive.h"
#include "ModuleTexture3D.h"
#include "Glew/include/glew.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleScene::~ModuleScene()
{
}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(0, 30, -30));

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleScene::Update(float dt)
{
	Plane_Obj(0, 1, 0, 0).Render();

	float3 pos = { 1, 1, 1 };
	float3 size = { 1, 1, 1 };

	if (App->input->GetKey(SDL_SCANCODE_G) ==KEY_DOWN) {
		App->mesh->ShowWire(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_G)== KEY_DOWN) {
		App->renderer3D->EnableTextures();
	}
	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) {
		App->mesh->ShowNormals();
	}
	return UPDATE_CONTINUE;
}

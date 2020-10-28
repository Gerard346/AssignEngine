#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Primitive.h"


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
	
	return UPDATE_CONTINUE;
}

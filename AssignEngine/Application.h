#pragma once

#include "Globals.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleUI.h"
#include "WindowConsole.h"
#include "ModuleMesh3D.h"
#include "ModuleTexture3D.h"
#include <list>
#include "Parson/parson.h"
#include "Timer.h"
#include "ModuleFileSystem.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleScene* scene;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleUI* ui;
	WindowConsole* console;
	ModuleMesh3D* mesh;
	ModuleTexture3D* texture;
	ModuleFileSystem* file_system;
	
private:
	
	Timer ms_timer;
	float				dt;
	float fps;
	float fps_capped;
	bool is_fps_capped = true;

	std::list<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	float GetFPS();
	float GetLastDt();
	void SetFPS(int);
	int GetFPSCapped();

	JSON_Value* config_value;
	JSON_Object* config_object;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	void CreatingConfigJSON();
	void LoadingData();
};

extern Application* App;
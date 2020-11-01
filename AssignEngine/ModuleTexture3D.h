#pragma once

#include "Module.h"
#include "Globals.h"

class ModuleTexture3D : public Module {
public:
	ModuleTexture3D(Application* app, bool start_enabled = true);
	~ModuleTexture3D();

	bool CleanUp();
};
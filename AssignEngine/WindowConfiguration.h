#pragma once
#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"
#include "ModuleUIManager.h"

class WindowConfiguration : public ModuleUIManager {

public:
	WindowConfiguration();
	virtual ~WindowConfiguration();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:
};
#pragma once
#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"
#include "ModuleUIManager.h"

class WindowBasicGeo : public ModuleUIManager {

public:
	WindowBasicGeo();
	virtual ~WindowBasicGeo();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:
	void Draw(const char*, bool*);

private:
};
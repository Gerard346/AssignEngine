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
	void Draw(const char*, bool*);

private:
	const char* name_engine;
	const char* name_organization;

	std::vector<float> fps_log;
	std::vector<float> ms_log;
};
#pragma once
#include "Globals.h"
#include "ImGui/imgui.h"
#include <list>
#include <vector>
struct Activate {

	bool isActivate = false;

	bool isActive() {
		return isActivate;
	}
	void OpenWindow() {
		isActivate = true;
	}
	void CloseWindow() {
		isActivate = false;
	}
};

class ModuleUIManager {

public:
	ModuleUIManager() {}
	~ModuleUIManager(){}

	virtual bool Start() {
		return true;
	}

	virtual update_status Update(float dt) {
		return update_status();
	}

	virtual bool CleanUp() {
		return true;
	}

public:

	std::vector<Activate> isActive;

};
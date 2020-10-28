#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleUIManager.h"

enum WindowsType_SubBar {
	About_Window,
	Console_Window,
	Configuration_Window
};

class WindowBar : public ModuleUIManager {

public:
	WindowBar();
	virtual ~WindowBar();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	std::vector<ModuleUIManager*> UI_SubBar;

private:
	void UpdateChilds(float dt);

};
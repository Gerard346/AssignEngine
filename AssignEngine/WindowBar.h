#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleUIManager.h"

class WindowBar : public ModuleUIManager {

public:
	WindowBar();
	virtual ~WindowBar();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:

};
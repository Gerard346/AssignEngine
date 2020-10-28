#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleUIManager.h"



class WindowAbout : public ModuleUIManager {

public:
	WindowAbout();
	virtual ~WindowAbout();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

private:

};
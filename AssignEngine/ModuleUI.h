#ifndef _MODULE_UI
#define _MODULE_UI

#include "Module.h"
#include "Globals.h"
#include "ModuleUIManager.h"

enum WindowsType {
	Console
};

class ModuleUI : public Module {

public:

	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool CleanUp();

public:

	std::vector<ModuleUIManager*> UIManager;

private:
	void UpdateUI(float dt);
	void DrawUIBar();
	/*bool rng_intT = true;
	int rng_int = 0;
	float rng_float = 0.0f;

	LCG rng_generator;*/
};

#endif // !_MODULE_UI


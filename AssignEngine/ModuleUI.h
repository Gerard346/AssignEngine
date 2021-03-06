#ifndef _MODULE_UI
#define _MODULE_UI

#include "Module.h"
#include "Globals.h"
#include "ModuleUIManager.h"
#include "MathGeoLib/include/Algorithm/Random/LCG.h"

enum WindowsType {
	Congifuration_Window,
	BasicPrimitives_Window
};

class ModuleUI : public Module {

public:

	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	void DrawUI(float dt);
	bool CleanUp();

public:

	std::vector<ModuleUIManager*> UIManager;

private:
	void UpdateUI(float dt);
	void DrawUIBar();
	void Dockspace(bool*);

private:
	bool* p_open;
	bool* open_rng;
	bool rng_intT = true;

	int rng_int = 0;
	float rng_float = 0.0f;

	LCG rng_generator;
};

#endif // !_MODULE_UI


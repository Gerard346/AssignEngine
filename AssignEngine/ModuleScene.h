#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib/include/MathGeoLib.h"
#define BOUNCER_TIME 200

struct PhysBody3D;
class Cube;

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();


public:

	SDL_Texture* graphics;
	PhysBody3D* ground;

private:
	bool rng_intT = true;
	int rng_int = 0;
	float rng_float = 0.0f;

	LCG rng_generator;
};

#pragma once
#include "Module.h"
#include "Globals.h"
#include "Glew/include/glew.h"

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

private:
	GLubyte checkImage[64][64][4];
	GLuint textureID;


};

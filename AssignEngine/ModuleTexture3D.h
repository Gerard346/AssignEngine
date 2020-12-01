#pragma once
#include "Module.h"
#include "Globals.h"
#include "BaseMesh.h"
#include "Glew/include/glew.h"

class ModuleTexture3D : public Module {
public:
	ModuleTexture3D(Application* app, bool start_enabled = true);
	~ModuleTexture3D();

	bool Init();
	bool Start();

	GLuint LoadTexture(const char*);

	bool CleanUp();

public: 

};
#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Primitive.h"

#include "Glew/include/glew.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(0, 30, -30));

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleScene::Update(float dt)
{
	Plane_Obj(0, 1, 0, 0).Render();
	
	static const GLfloat vertex[] = {
		0,0,0,
		10,0,0,
		10,0,10,
		0,0,10,
		0,10,0,
		10,10,0,
		10,10,10,
		0,10,10
	};

	static const GLuint index[] = {
		//Front
		3,2,6,6,7,3,
		//Right
		6,2,1,1,5,6,
		//Top
		4,7,6,6,5,4,
		//Back
		1,0,5,0,4,5,
		//Left
		4,0,7,7,0,3,
		//Bottom
		0,1,2,2,3,0
	};

	GLuint vertex_buffer;
	//Create new buffer, gives uint
	glGenBuffers(1, &vertex_buffer);
	//Start using that buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	//send array to VRAM
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 3, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	GLuint index_buffer;

	glGenBuffers(1, &index_buffer);
	//Start using that buffer
	glBindBuffer(GL_ARRAY_BUFFER, index_buffer);
	//send array to VRAM
	glBufferData(GL_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	glDrawElements(GL_TRIANGLES, (sizeof(index) / sizeof(GLuint)), GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	return UPDATE_CONTINUE;
}

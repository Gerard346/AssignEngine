#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	update_status PreUpdate(float);

	void SetTitle(const char* title);
	void SetFullScreen();
	void SetResizable();
	void SetBorderless();
	void setFullDesktop();

	void SetBrightness(float);
	float GetBrightness();
	void ResizeWindow();

	void wantToresize();
public:
	//The window we'll be rendering to
	SDL_Window* window;
	SDL_GLContext context;
	//The surface contained by the window
	SDL_Surface* screen_surface;
	bool fullscreen = false;
	bool resizable = false;
	bool borderless = false;
	bool fulldesktop = false;
	bool want_to_resize = false;
	int width;
	int height;

private:
	SDL_bool res_sdl;
	SDL_bool bor_sdl;
	
};

#endif // __ModuleWindow_H__
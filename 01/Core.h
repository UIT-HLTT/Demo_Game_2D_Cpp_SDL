#ifndef CORE_H_
#define CORE_H_

#include "Header.h"
#include "MenuManager.h"
#include "ImpTimer.h"

class Core
{
public:
	Core(void);
	~Core(void);

	void mainLoop();
	void FPS();
	void Close();
	void Free();

private: 
	SDL_Window* window = NULL;
	SDL_Renderer* screen = NULL;
	SDL_Event events;

	static MenuManager* oMenuManager;
	static ImpTimer* fps_timer;

	static bool QuitGame;
};

#endif
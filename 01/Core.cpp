#include "Core.h"

bool is_quit = false;
bool Core::QuitGame = false;

MenuManager* Core::oMenuManager = new MenuManager();
ImpTimer* Core::fps_timer = new ImpTimer();

Core::Core(void)
{
	bool is_quit = false;

	/*--------Init Screen------- */
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("Demo Game 2D",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH, SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		is_quit = true;
	}

	screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/*--------Icon------- */
	std::string file_name = "file//image//icon.png";
	SDL_Surface* load_surface = IMG_Load(file_name.c_str());
	SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

	SDL_SetWindowIcon(window, load_surface);
	SDL_FreeSurface(load_surface);
	/*--------Icon------- */

	oMenuManager = new MenuManager(screen);
	fps_timer = new ImpTimer();
}

Core::~Core(void)
{
	Close();
}

void Core::mainLoop()
{
	while (!QuitGame)
	{
		fps_timer->Start();

		while (SDL_PollEvent(&events) != 0)
		{
			if (events.type == SDL_QUIT)
			{
				oMenuManager->SetCGS(5);
			}

			oMenuManager->Input(events, screen);
		}

		SDL_SetRenderDrawColor(screen,
			RENDER_DRAW_COLOR,
			RENDER_DRAW_COLOR,
			RENDER_DRAW_COLOR,
			RENDER_DRAW_COLOR);
		SDL_RenderClear(screen);

		oMenuManager->ActiveGame(screen);
		QuitGame = oMenuManager->GetQuit();

		SDL_RenderPresent(screen);

		FPS();
	}

	Close();
}

void Core::FPS()
{
	int real_imp_time = fps_timer->GetTicks();
	int time_one_frame = 1000 / FRAME_PER_SECOND; //ms

	if (real_imp_time < time_one_frame)
	{
		int delay_time = time_one_frame - real_imp_time;
		if (delay_time >= 0)
			SDL_Delay(delay_time);
	}
}

void Core::Close()
{
	SDL_DestroyRenderer(screen);
	screen = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();

	Free();
}

void Core::Free()
{
	oMenuManager = NULL;
	fps_timer = NULL;
}

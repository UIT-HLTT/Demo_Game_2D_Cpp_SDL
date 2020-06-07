#ifndef PAUSE_GAME_H_
#define PAUSE_GAME_H_

#include "Header.h"
#include "IMG.h"
#include "Text.h"

class PauseGame
{
public:
	PauseGame(void);
	PauseGame(SDL_Renderer* screen);
	~PauseGame(void);

	enum GameStateAfterPause
	{
		eNone = 0,
		eMainMenu = 1,
		eResumeGame = 2,
		eQuit = 5,
	};

	void LoadMenuPause(SDL_Renderer* screen);
	void Draw(SDL_Renderer* screen);
	void Input(SDL_Event events, SDL_Renderer* screen);
	void ActiveAfterPause();
	void UpdateText(SDL_Renderer* screen);
	void Free();

	/* ------- set & get ------- */
	void SetCGAP(const int& x) { iCurrenGameAfterPause = x; }
	
	int GetCGAP() const { return iCurrenGameAfterPause; }
	bool GetPause() const { return *bPause; }

private:
	std::vector<Text*> vSelection;
	IMG* BG_menu_pause;
	TTF_Font* font_menu_pause;

	bool* bPause;
	int input_key_pause; //0 1 2
	int input_key_menu; //1 2 3
	int iCurrenGameAfterPause;
};

#endif
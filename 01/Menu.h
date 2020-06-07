#ifndef MENU_H_
#define MENU_H_

#include "Header.h"
#include "Text.h"
#include "IMG.h"

class Menu
{
public:
	Menu(void);
	Menu(SDL_Renderer* screen);
	~Menu(void);

	enum MainMenu
	{
		none = 0,
		new_game = 2,
		quit_game = 5,
	};

	void LoadMainMenu(SDL_Renderer* screen);
	void Draw(SDL_Renderer* screen);
	void Input(SDL_Event events, SDL_Renderer* screen);
	void ActiveMenu();
	void UpdateText(SDL_Renderer* screen);
	void Free();

	/* ------- set & get ------- */
	void SetCG(const int& x) { CG = x; }

	int GetCG() const { return CG; }
	bool GetMenu() { return *bMenu; }

private:
	std::vector<Text*> vSelection;
	IMG* bg_menu;
	TTF_Font* font_menu;

	unsigned int CG;
	int input_key; //1->NUM_SELECTION_MENU
	bool* bMenu;
};

#endif
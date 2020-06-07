#include "Menu.h"

Menu::Menu(void)
{

}

Menu::Menu(SDL_Renderer* screen)
{
	font_menu = NULL;
	bg_menu = new IMG;
	bMenu = new bool(true);

	input_key = 1;
	CG = none;

 	LoadMainMenu(screen);
}

Menu::~Menu(void)
{
	Free();
}

void Menu::LoadMainMenu(SDL_Renderer* screen)
{
	TTF_Init();
	font_menu = TTF_OpenFont("file//font//msjh.ttf", 40);

	std::vector<std::string> vTemp(NUM_SELECTION_MENU);
	Text* oTemp;

	vTemp[0] = "New Game";
	vTemp[1] = "Quit";

	for (int i = 0; i < NUM_SELECTION_MENU; i++)
	{
		oTemp = new Text();
		oTemp->SetColor(Text::WHITE_TEXT);
		oTemp->SetText(vTemp[i]);
		oTemp->LoadFromRenderText(font_menu, screen);
		vSelection.push_back(oTemp);
	}

	bg_menu->LoadIMG("bg_menu", screen);
}

void Menu::Input(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
		{
			input_key--;

			if (input_key < 0)
				input_key = NUM_SELECTION_MENU;
		}
		break;
		case SDLK_DOWN:
		{
			input_key++;

			if (input_key > NUM_SELECTION_MENU)
				input_key = 1;
		}
		break;
		case SDLK_RETURN:
		{
			ActiveMenu();
		}
		}
	}
}

void Menu::ActiveMenu()
{
	if (input_key == 1)
	{
		CG = new_game;
		*bMenu = false;
	}
	else if (input_key == 2)
	{
		CG = quit_game;
		*bMenu = false;
	}
}

void Menu::Draw(SDL_Renderer* screen)
{
	UpdateText(screen);

	bg_menu->Draw(screen);

	for (unsigned int i = 0; i < vSelection.size(); i++)
	{
		vSelection[i]->Draw(screen, 700, 380 + 70 * i);
	}
}

void Menu::UpdateText(SDL_Renderer* screen)
{
	for (int i = 0; i < NUM_SELECTION_MENU; i++)
	{
		if (input_key == i + 1)
		{
			vSelection[i]->SetColor(Text::GRAY_TEXT_1);
		}
		else vSelection[i]->SetColor(Text::WHITE_TEXT);

		vSelection[i]->LoadFromRenderText(font_menu, screen);
	}
}

void Menu::Free()
{
	for (std::vector<Text*>::iterator i = vSelection.begin(); i != vSelection.end(); i++)
	{
		delete (*i);
	}

	font_menu = NULL;
	bg_menu = NULL;
	bMenu = NULL;
	input_key = 0;
	CG = none;
}
#include "PauseGame.h"

PauseGame::PauseGame(void)
{

}

PauseGame::PauseGame(SDL_Renderer* screen)
{
	BG_menu_pause = new IMG();

	font_menu_pause = NULL;
	bPause = new bool(false);
	input_key_pause = 0;
	input_key_menu = 0;
	iCurrenGameAfterPause = eNone;

	LoadMenuPause(screen);
}

PauseGame::~PauseGame(void)
{
	Free();
}

void PauseGame::LoadMenuPause(SDL_Renderer* screen)
{
	TTF_Init();
	font_menu_pause = TTF_OpenFont("file//font//msjh.ttf", 30);

	std::vector<std::string> vTemp(NUM_SELECTION_PAUSE);
	Text* oTemp;

	vTemp[0] = "Resume Game";
	vTemp[1] = "Main Menu";
	vTemp[2] = "Quit";

	for (int i = 0; i < NUM_SELECTION_PAUSE; i++)
	{
		oTemp = new Text();
		oTemp->SetColor(Text::GRAY_TEXT_2);
		oTemp->SetText(vTemp[i]);
		oTemp->LoadFromRenderText(font_menu_pause, screen);
		vSelection.push_back(oTemp);
	}

	BG_menu_pause->LoadIMG("bg_menu_pause", screen);
}

void PauseGame::Draw(SDL_Renderer* screen)
{
	UpdateText(screen);

	BG_menu_pause->Draw(screen);

	for (unsigned int i = 0; i < vSelection.size(); i++)
	{
		vSelection[i]->Draw(screen, 305, 169 + 64 * i);
	}
}

void PauseGame::Input(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_ESCAPE:
		{
			input_key_pause++;

			if (input_key_pause > 2)
			{
				input_key_pause = 1;
			}
		}
		break;
		}
	}

	if (input_key_pause == 0)
		*bPause = false;
	else if (input_key_pause == 1)
	{
		*bPause = true;
	}

	if (*bPause == true)
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_DOWN:
			{
				input_key_menu++;
				if (input_key_menu > NUM_SELECTION_PAUSE)
					input_key_menu = 1;
			}
			break;

			case SDLK_UP:
			{
				input_key_menu--;
				if (input_key_menu < 0)
					input_key_menu = NUM_SELECTION_PAUSE;
			}
			break;

			case SDLK_RETURN:
			{
				ActiveAfterPause();
			}
			break;
			}
		}

		if (input_key_pause == 2)
		{
			iCurrenGameAfterPause = eResumeGame;
			*bPause = false;
			input_key_pause = 0;
		}
	}
}

void PauseGame::ActiveAfterPause()
{
	if (input_key_menu != 0)
	{
		if (input_key_menu == 1)
		{
			iCurrenGameAfterPause = eResumeGame;
			*bPause = false;
		}

		else if (input_key_menu == 2)
		{
			iCurrenGameAfterPause = eMainMenu;
			*bPause = false;
		}
		else if (input_key_menu == 3)
		{
			iCurrenGameAfterPause = eQuit;
			*bPause = false;
		}
	}
	input_key_pause = 0;
}

void PauseGame::UpdateText(SDL_Renderer* screen)
{
	for (int i = 0; i < NUM_SELECTION_PAUSE; i++)
	{
		if (input_key_menu == i+1)
		{
			vSelection[i]->SetColor(Text::WHITE_TEXT);
		}
		else vSelection[i]->SetColor(Text::GRAY_TEXT_2);

		vSelection[i]->LoadFromRenderText(font_menu_pause, screen);
	}
}

void PauseGame::Free()
{
	for (std::vector<Text*>::iterator i = vSelection.begin(); i != vSelection.end(); i++)
	{
		delete (*i);
	}

	BG_menu_pause = NULL;

	font_menu_pause = NULL;
	bPause = new bool(false);
	input_key_pause = 0;
	input_key_menu = 0;
	iCurrenGameAfterPause = eNone;
}
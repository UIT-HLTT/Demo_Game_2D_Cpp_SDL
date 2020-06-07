#include "MenuManager.h"

MenuManager::MenuManager(void)
{

}

MenuManager::MenuManager(SDL_Renderer* screen)
{
	oMenu = new Menu(screen);
	oPause = new PauseGame(screen);
	oMap = new Map();
	oPlayer = new Player(screen);

	bInputMenu = true;
	bInputPause = false;
	bInputPlayer = false;
	bQuit = false;
	iCurrentGameState = eMainMenu;
	iNextLV = 0;
	idLV = 1;
}

MenuManager::~MenuManager(void)
{
	Free();
}

void MenuManager::UpdateCurrentGameState(SDL_Renderer* screen)
{
	//------- Menu
		switch (MenuManager::oMenu->GetCG())
		{
		case eGame:
		{
			iCurrentGameState = eGameLoading;
			oPause->SetCGAP(eNone);
		}
		break;

		case eQuit:
		{
			iCurrentGameState = eQuit;
			oPause->SetCGAP(eNone);
		}
		break;
		}

	//------- Pause
	if (MenuManager::oPause->GetPause() == true && iCurrentGameState != eQuit)
	{
		iCurrentGameState = ePause;
	}

	switch (oPause->GetCGAP())
	{
	case eGame:
	{
		iCurrentGameState = eGame;
		oPause->SetCGAP(eNone);
	}
	break;

	case eMainMenu:
	{
		iCurrentGameState = eMainMenu;
	}
	break;

	case eQuit:
	{
		iCurrentGameState = eQuit;
	}
	break;
	}
}

void MenuManager::ActiveGame(SDL_Renderer* screen)
{
	UpdateCurrentGameState(screen);

	switch (iCurrentGameState)
	{
	case eMainMenu:
	{
		oMenu->Draw(screen);
		bInputPlayer = false;
		bInputMenu = true;
		bInputPause = false;
	}
	break;

	case eGameLoading:
	{
		LoadLVMap(screen);
		iCurrentGameState = eGame;
		oMenu->SetCG(eNone);
	}
	break;

	case eGame:
	{
		oMap->DrawMap(screen);
		*oPlayer->GetMap() = *oMap;
		oPlayer->DoPlayer();
		oPlayer->Draw(screen);
		bInputPlayer = true;
		bInputPause = true;
		bInputMenu = false;
	}
	break;

	case ePause:
	{
		oPause->Draw(screen);
		bInputPlayer = false;
		bInputPause = true;
		bInputMenu = false;
	}
	break;

	case eQuit:
	{
		bQuit = true;
	}
	break;
	}
}

void MenuManager::LoadLVMap(SDL_Renderer* screen)
{
	UpdateIDLV();

	switch (idLV)
	{
	case 1:
	{
		oMap = new Map();
		oPlayer = new Player(screen);
		oPlayer->SetPlayerStart(96, 784);
		oMap->SetMaxMap(40, 30);
		oMap->SetArrData();
		oMap->SetIDMap("01");
		oMap->LoadBackground(screen);
		oMap->LoadTileData(screen);
		oMap->LoadDataMap();
	}
	break;

	case 2:
	{
		oMap->SetMaxMap(50, 30);
		oMap->SetArrData();
		oMap->SetIDMap("02");
		oMap->LoadBackground(screen);
		oMap->LoadTileData(screen);
		oMap->LoadDataMap();
		iCurrentGameState = eGame;
		oMenu->SetCG(eNone);
	}
	break;

	case 3:
	{
		oMap->SetMaxMap(50, 30);
		oMap->SetArrData();
		oMap->SetIDMap("03");
		oMap->LoadBackground(screen);
		oMap->LoadTileData(screen);
		oMap->LoadDataMap();
		iCurrentGameState = eGame;
		oMenu->SetCG(eNone);
	}
	break;
	}
}

void MenuManager::Input(SDL_Event events, SDL_Renderer* screen)
{
	if (bInputMenu == true)
		oMenu->Input(events, screen);
	if (bInputPause == true)
		oPause->Input(events, screen);
	if (bInputPlayer == true)
		oPlayer->Input(events);
}

void MenuManager::UpdateIDLV()
{
	if (iNextLV == 1)
	{
		idLV++;
	}

	else if (iNextLV == -1)
	{
		idLV--;
	}
}

void MenuManager::Free()
{
	oMenu = NULL;
	oPause = NULL;
	oMap = NULL;
	oPlayer = NULL;

	bQuit = false;
	bInputMenu = false;
	bInputPause = false;
	bInputPlayer = false;
	iCurrentGameState = 0;
	iNextLV = 0;
	idLV = 0;
}
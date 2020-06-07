#ifndef MENU_MANAGER_H_
#define MENU_MANAGER_H_

#include "Header.h"
#include "Map.h"
#include "Menu.h"
#include "PauseGame.h"
#include "Player.h"

class MenuManager
{
public:
	MenuManager(void);
	MenuManager(SDL_Renderer* screen);
	~MenuManager(void);

	enum GameState
	{
		eNone,
		eMainMenu,
		eGame,
		eGameLoading,
		ePause,
		eQuit,
	};

	void UpdateCurrentGameState(SDL_Renderer* screen);
	void ActiveGame(SDL_Renderer* screen);
	void LoadLVMap(SDL_Renderer* screen);
	void UpdateIDLV();
	void Input(SDL_Event events, SDL_Renderer* screen);
	void Free();

	/* ------- set & get ------- */
	void SetCGS(const int& CGS) { iCurrentGameState = CGS; }
	void SetidLV(const int& idlv) { this->idLV = idlv; }

	int GetCGS() const { return iCurrentGameState; }
	bool GetQuit() const { return bQuit; }

private:
	Menu* oMenu;
	PauseGame* oPause;
	Map* oMap;
	Player* oPlayer;

	bool bQuit;
	bool bInputMenu;
	bool bInputPause;
	bool bInputPlayer;
	int iCurrentGameState;
	int iNextLV; //1 -1
	int idLV;
};

#endif
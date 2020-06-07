#ifndef PLAYER_H_
#define PLAYER_H_

#include "Header.h"
#include "IMG.h"
#include "Sprite.h"
#include "Map.h"
#include "PauseGame.h"

class Player
{
public:
	Player(void);
	Player(SDL_Renderer* screen);
	~Player(void);

	enum StatePlayer
	{
		eRight,
		eLeft,
	};

	enum StatusDoPlayer
	{
		eNone,
		eMove,
		eJump,
	};

	struct InputType
	{
		int none;
		int right;
		int left;
		int jump;
	};

	void LoadSprite(SDL_Renderer* screen);
	void Draw(SDL_Renderer* screen);
	void Input(SDL_Event events);
	void CenterEntityOnMap();
	void CheckToMap();
	void DoPlayer();
	void UpdateStatusPlayer();
	void UpdateRotate();
	void UpdateSizeFrame();
	void Free();

	/* ------- set & get ------- */
	void SetMap(Map* oMap) { this->oMap = oMap; }
	void SetPlayerStart(const int& x, const int& y) { x_pos = x; y_pos = y; }

	Map* GetMap() const { return oMap; }

private:
	std::vector<Sprite*> vPlayer;
	Map* oMap;
	SDL_Rect rect;

	InputType input_key;
	int status_player; // eNone, eMove, eJump
	int direction_player; // eRight, eLeft
	bool on_ground;
	int width_frame;
	int height_frame;

	int x_val;
	int y_val;
	int x_pos;
	int y_pos;
};

#endif

#include "Player.h"

Player::Player(void)
{

}

Player::Player(SDL_Renderer* screen)
{
	oMap = new Map();

	status_player = eNone;
	direction_player = eRight;
	on_ground = false;
	width_frame = 0;
	height_frame = 0;
	rect.x = 0;
	rect.y = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;

	LoadSprite(screen);
}

Player::~Player(void)
{
	Free();
}

void Player::LoadSprite(SDL_Renderer* screen)
{
	std::vector<std::string> tempS;
	std::vector<unsigned int> tempI;

	//-------idle (0)
	for (int i = 0; i < NUM_FRAME_IDLE; i++)
	{
		tempS.push_back("player//idle" + std::to_string(i + 1));
		tempI.push_back(50);
	}
	vPlayer.push_back(new Sprite(screen, tempS, tempI, false));
	tempS.clear();
	tempI.clear();

	//-------move (1)
	for (int i = 0; i < NUM_FRAME_MOVE; i++)
	{
		tempS.push_back("player//move" + std::to_string(i + 1));
		tempI.push_back(40);
	}
	vPlayer.push_back(new Sprite(screen, tempS, tempI, false));
	tempS.clear();
	tempI.clear();

	//-------jump (2)
	for (int i = 0; i < NUM_FRAME_JUMP; i++)
	{
		tempS.push_back("player//jump" + std::to_string(i + 1));
		tempI.push_back(0);
	}
	vPlayer.push_back(new Sprite(screen, tempS, tempI, false));
	tempS.clear();
	tempI.clear();
}

void Player::Draw(SDL_Renderer* screen)
{
	rect.x = x_pos - oMap->GetMapData()->start_x;
	rect.y = y_pos - oMap->GetMapData()->start_y;

	vPlayer[status_player]->Update();
	vPlayer[status_player]->GetTexture()->Draw(screen, rect.x, rect.y, vPlayer[status_player]->GetRotate());
}


void Player::Input(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			direction_player = eRight;
			input_key.right = 1;
			input_key.left = 0;
		}
		break;

		case SDLK_a:
		{
			direction_player = eLeft;
			input_key.right = 0;
			input_key.left = 1;
		}
		break;

		case SDLK_SPACE:
		{
			input_key.jump = 1;
		}
		break;
		}
	}

	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			input_key.right = 0;
		}
		break;

		case SDLK_a:
		{
			input_key.left = 0;
		}
		break;

		case SDLK_SPACE:
		{
			input_key.jump = 0;
		}
		break;
		}
	}
}

void Player::DoPlayer()
{
	x_val = 0;
	y_val += GRAVITY_SPEED;

	if (y_val >= MAX_FALL_SPEED)
		y_val = MAX_FALL_SPEED;

	if (input_key.right == 1)
	{
		x_val += PLAYER_SPEED;
	}

	if (input_key.left == 1)
	{
		x_val -= PLAYER_SPEED;
	}

	if (input_key.jump == 1)
	{
		if (on_ground == true)
		{
			y_val -= JUMP_PLAYER_VAR;
		}

		on_ground = false;
	}

	CheckToMap();
	UpdateRotate();
	UpdateSizeFrame();
	UpdateStatusPlayer();
	CenterEntityOnMap();
}

void Player::CenterEntityOnMap()
{
	oMap->SetStartMapX(x_pos - (SCREEN_WIDTH / 2));
	if (oMap->GetMapData()->start_x < 0)
	{
		oMap->SetStartMapX(0);
	}
	else if (oMap->GetMapData()->start_x + SCREEN_WIDTH >= oMap->GetMapData()->max_x)
	{
		oMap->SetStartMapX(oMap->GetMapData()->max_x - SCREEN_WIDTH);
	}

	oMap->SetStartMapY(y_pos - (SCREEN_HEIGHT / 2));
	if (oMap->GetMapData()->start_y < 0)
	{
		oMap->SetStartMapY(0);
	}
	else if (oMap->GetMapData()->start_y + SCREEN_HEIGHT >= oMap->GetMapData()->max_y)
	{
		oMap->SetStartMapY(oMap->GetMapData()->max_y - SCREEN_HEIGHT);
	}
}

void Player::CheckToMap()
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	x_pos += x_val;
	y_pos += y_val;

	//------- Check horiontal
	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + width_frame - 1) / TILE_SIZE;

	y1 = (y_pos - x_val) / TILE_SIZE;
	y2 = (y_pos - x_val + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < oMap->GetMapData()->max_map_x && y1 >= 0 && y2 < oMap->GetMapData()->max_map_y)
	{
		if (x_val > 0) //player is moving to right
		{
			int val1 = oMap->GetMapData()->data[y1][x2];
			int val2 = oMap->GetMapData()->data[y2][x2];

			if ((oMap->GetBlock()[val1]->GetCollisionR() || oMap->GetBlock()[val2]->GetCollisionR()) == true)
			{
					x_pos = x2 * TILE_SIZE;
					x_pos -= width_frame + 1;
					x_val = 0;
			}
		}
		else if (x_val < 0) //player is moving to left
		{
			int val1 = oMap->GetMapData()->data[y1][x1];
			int val2 = oMap->GetMapData()->data[y2][x1];

			if ((oMap->GetBlock()[val1]->GetCollisionL() || oMap->GetBlock()[val2]->GetCollisionL()) == true)
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
	}

	//------- Check vertical
	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;

	x1 = (x_pos - x_val) / TILE_SIZE;
	x2 = (x_pos - x_val + width_min) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_frame - MAX_FALL_SPEED) / TILE_SIZE + 1;

	if (x1 >= 0 && x2 < oMap->GetMapData()->max_map_x && y1 >= 0 && y2 < oMap->GetMapData()->max_map_y)
	{
		if (y_val > 0) //player is moving to down
		{
			int val1 = oMap->GetMapData()->data[y2][x1];
			int val2 = oMap->GetMapData()->data[y2][x2];

			if ((oMap->GetBlock()[val1]->GetCollisionB() || oMap->GetBlock()[val2]->GetCollisionB()) == true)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= height_frame;
				y_val = 0;

				on_ground = true;
			}

			else on_ground = false;
		}

		else if (y_val < 0) //player is moving to up
		{
			int val1 = oMap->GetMapData()->data[y1][x1];
			int val2 = oMap->GetMapData()->data[y1][x2];

			if ((oMap->GetBlock()[val1]->GetCollisionA() || oMap->GetBlock()[val2]->GetCollisionA()) == true)
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
	}

	x_val = 0;

	if (x_pos < 0)
	{
		x_pos = 0;
	}
	else if (x_pos + width_frame > oMap->GetMapData()->max_x)
	{
		x_pos = oMap->GetMapData()->max_x - width_frame - 1;
	}
}

void Player::UpdateStatusPlayer()
{
	if (on_ground == true)
	{
		if (input_key.right == 1 || input_key.left == 1)
		{
			status_player = eMove;
		}

		else if (input_key.right == 0 || input_key.left == 0)
		{
			status_player = eNone;
		}
	}

	if (on_ground == false)
	{
		status_player = eJump;
	}
}

void Player::UpdateRotate()
{
	if (direction_player == eRight)
	{
		vPlayer[0]->SetRotate(false);
		vPlayer[1]->SetRotate(false);
		vPlayer[2]->SetRotate(false);
	}
	else
	{
		vPlayer[0]->SetRotate(true);
		vPlayer[1]->SetRotate(true);
		vPlayer[2]->SetRotate(true);
	}
}

void Player::UpdateSizeFrame()
{
	switch (status_player)
	{
	case eNone:
	{
		width_frame = 38;
		height_frame = 48;
	}
	break;

	case eMove:
	{
		width_frame = 38;
		height_frame = 53;
	}
	break;

	case eJump:
	{
		width_frame = 43;
		height_frame = 53;
	}
	break;
	}
}

void Player::Free()
{
	for (std::vector<Sprite*>::iterator i = vPlayer.begin(); i != vPlayer.end(); i++)
	{
		delete (*i);
	}

	oMap = NULL;
	status_player = 0;
	direction_player = 0;
	on_ground = false;
	width_frame = 0;
	height_frame = 0;
	rect.x = 0;
	rect.y = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
}
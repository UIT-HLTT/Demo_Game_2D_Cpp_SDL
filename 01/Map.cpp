#include "Map.h"

Map::Map(void)
{
	sIDMap = "";

	GM = new MapData;
	background = new IMG;
}

Map::~Map(void)
{
	Free();
}

void Map::SetArrData()
{
	GM->data = (int**)malloc(GM->max_map_y * sizeof(int*));
	for (int i = 0; i < GM->max_map_y; i++)
	{
		GM->data[i] = (int*)malloc(GM->max_map_x * sizeof(int));
	}
}

void Map::LoadBackground(SDL_Renderer* screen)
{
	background->LoadIMG("background//" + sIDMap + "//" + sIDMap, screen);
}

void Map::LoadTileData(SDL_Renderer* screen)
{
	std::vector<std::string> tSprite;
	std::vector<unsigned int> iDelay;

	//------- 0
	tSprite.push_back("tile//" + sIDMap + "//transp");
	iDelay.push_back(0);
	vBlock.push_back(new Block(0, new Sprite(screen, tSprite, iDelay, false), false, false, false, false, false, false));
	tSprite.clear();
	iDelay.clear();

	// ------- 1->4
	for (int i = 0; i < 4; i++)
	{
		tSprite.push_back("tile//" + sIDMap + "//" + std::to_string(i + 1));
		iDelay.push_back(0);
		vBlock.push_back(new Block(i + 1, new Sprite(screen, tSprite, iDelay, false), true, true, true, true, false, false));
		tSprite.clear();
		iDelay.clear();
	}

	// ------- 5
	tSprite.push_back("tile//" + sIDMap + "//5");
	iDelay.push_back(0);
	vBlock.push_back(new Block(5, new Sprite(screen, tSprite, iDelay, false), false, true, false, false, false, false));
	tSprite.clear();
	iDelay.clear();
}

void Map::LoadDataMap()
{
	sIDMap = "file//map//" + sIDMap + ".dat";
	{
		FILE* fp = NULL;
		fopen_s(&fp, sIDMap.c_str(), "rb");
		if (fp == NULL)
		{
			return;
		}
		GM->max_x = 0;
		GM->max_y = 0;

		for (int i = 0; i < GM->max_map_y; i++)
		{
			for (int j = 0; j < GM->max_map_x; j++)
			{
				fscanf_s(fp, "%d", &GM->data[i][j]);
				int val = GM->data[i][j];
				if (val > 0)
				{
					if (j > GM->max_x)
					{
						GM->max_x = j;
					}
					if (i > GM->max_y)
					{
						GM->max_y = i;
					}
				}
			}
		}

		GM->max_x = (GM->max_x + 1) * TILE_SIZE;
		GM->max_y = (GM->max_y + 1) * TILE_SIZE;

		GM->start_x = 0;
		GM->start_y = 0;

		fclose(fp);
	}
}

void Map::DrawBackground(SDL_Renderer* screen)
{
	background->Draw(screen);
}

void Map::DrawTileStatic(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = GM->start_x / TILE_SIZE;
	x1 = (GM->start_x % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = GM->start_y / TILE_SIZE;
	y1 = (GM->start_y % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = GM->start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = GM->data[map_y][map_x];

			if (val >= 0)
			{
				vBlock[val]->Draw(screen, j, i);
			}
			map_x++;
		}
		map_y++;
	}
}

void Map::DrawMap(SDL_Renderer* screen)
{
	DrawBackground(screen);
	DrawTileStatic(screen);
}

void Map::Free()
{
	sIDMap = "";

	delete GM;
	delete background;

	for (std::vector<Block*>::iterator i = vBlock.begin(); i != vBlock.end(); i++)
	{
		delete (*i);
	}
}
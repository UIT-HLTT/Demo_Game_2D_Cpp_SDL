#ifndef MAP_H_
#define MAP_H_

#include "Header.h"
#include "Block.h"

struct MapData
{
	int max_map_x;
	int max_map_y;

	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int** data;
};

class Map
{
public:
	Map(void);
	Map(SDL_Renderer* screen);
	~Map(void);

	void LoadBackground(SDL_Renderer* screen);
	void LoadTileData(SDL_Renderer* screen);
	void LoadDataMap();
	
	void DrawBackground(SDL_Renderer* screen);
	void DrawTileStatic(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);

	void Free();

	/* ------- set & get ------- */
	void SetArrData();
	void SetMapData(MapData& map_data) { *GM = map_data; }
	void SetMaxMap(const int& x, const int& y) { GM->max_map_x = x, GM->max_map_y = y; }
	void SetStartMapX(const int& x) { GM->start_x = x; }
	void SetStartMapY(const int& y) { GM->start_y = y; }
	void SetIDMap(std::string ID) { sIDMap = ID; }

	MapData* GetMapData() const { return GM; }
	std::vector<Block*> GetBlock() const { return vBlock; }

private:
	std::string sIDMap;
	std::vector<Block*> vBlock;

	MapData* GM;
	IMG* background;
};

#endif

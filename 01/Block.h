#ifndef BLOCK_H_
#define BLOCK_H_

#include "Header.h"
#include "Sprite.h"

class Block
{
public:
	Block(void);
	Block(int iBlockID, Sprite* sSprite, bool bCollisionA, bool bCollisionB, bool bCollisionR, bool bCollisionL, bool bUse, bool bVisible);
	~Block(void);

	void Draw(SDL_Renderer* screen, int x, int y);
	void Free();

	/* ----- set & get ----- */
	void SetBlockID(const int& id) { iBlockID = id; }

	Sprite* GetSprite() const { return sSprite; }
	int GetBlockID() const { return iBlockID; }
	bool GetCollisionA() const { return bCollisionA; }
	bool GetCollisionB() const { return bCollisionB; }
	bool GetCollisionR() const { return bCollisionR; }
	bool GetCollisionL() const { return bCollisionL; }
	bool GetUse() const { return bUse; }
	bool GetVisible() const { return bVisible; }

private:
	Sprite* sSprite;
	int iBlockID;
	bool bCollisionA; // above
	bool bCollisionB; // below
	bool bCollisionR; // right
	bool bCollisionL; // left
	bool bUse;
	bool bVisible;
};

#endif
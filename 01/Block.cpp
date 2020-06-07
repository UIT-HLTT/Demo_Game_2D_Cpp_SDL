#include "Block.h"

Block::Block(void)
{
	Free();
}

Block::Block(int iBlockID, Sprite* sSprite, bool bCollisionA, bool bCollisionB, bool bCollisionR, bool bCollisionL, bool bUse, bool bVisible)
{
	this->iBlockID = iBlockID;
	this->sSprite = sSprite;
	this->bCollisionA = bCollisionA;
	this->bCollisionB = bCollisionB;
	this->bCollisionR = bCollisionR;
	this->bCollisionL = bCollisionL;
	this->bUse = bUse;
	this->bVisible = bVisible;
}

Block::~Block(void)
{

}

void Block::Draw(SDL_Renderer* screen, int x, int y) 
{
	sSprite->GetTexture()->Draw(screen, x, y);
}

void Block::Free()
{
	delete sSprite;
	iBlockID = 0;
	bCollisionA = false;
	bCollisionB = false;
	bCollisionR = false;
	bCollisionL = false;
	bUse = false;
	bVisible = false;
}
#ifndef SPRITE_H_
#define SPRITE_H_

#include "Header.h"
#include "IMG.h"

class Sprite
{
public:
	Sprite(void);
	Sprite(SDL_Renderer* screen, std::vector<std::string> tSprite, std::vector<unsigned int> iDelay, bool bRotate);
	~Sprite(void);

	void Update();
	void Free();

	/* ------- set & get ------- */
	void SetRotate(const bool& b) { bRotate = b; }

	IMG* GetTexture() const { return tSprite[iCurrentFrame]; }
	IMG* GetTexture(int iID) const { return tSprite[iID]; }
	bool GetRotate() const { return bRotate; }

private:
	std::vector<IMG*> tSprite;
	std::vector<unsigned int> iDelay;

	bool bRotate;
	int iCurrentFrame;
	int iStartFrame;
	int iEndFrame;
	unsigned long lTimePassed;
};

#endif
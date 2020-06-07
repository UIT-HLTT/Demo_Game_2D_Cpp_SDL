#ifndef IMG_H_
#define IMG_H_

#include "Header.h"

class IMG
{
public:
	IMG(void);
	IMG(std::string file_name, SDL_Renderer* screen);
	~IMG(void);

	void LoadIMG(std::string file_name, SDL_Renderer* screen);
	void Draw(SDL_Renderer* screen, const SDL_Rect* clip = NULL);
	void Draw(SDL_Renderer* screen, int x, int y);
	void Draw(SDL_Renderer* screen, int x, int y, bool bRotate);
	void Free();

	/* ------- set & get ------- */
	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y; }

	SDL_Rect GetRect() const { return rect; }
	SDL_Texture* GetIMG() const { return tIMG; }

protected:
	SDL_Rect rect;
	SDL_Texture* tIMG;
};

#endif
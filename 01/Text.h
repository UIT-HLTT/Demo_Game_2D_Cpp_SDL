#ifndef TEXT_H_
#define TEXT_H_

#include "Header.h"

class Text
{
public:
	Text(void);
	~Text(void);

	enum
	{
		RED_TEXT,
		WHITE_TEXT,
		BLACK_TEXT,
		GRAY_TEXT_1,
		GRAY_TEXT_2,
		ANTIQUEWHITE_TEXT,
	};

	void Free();
	virtual void LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Draw(SDL_Renderer* screen,
		int xp, int yp,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point * center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	/* ------- set & get ------- */
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);
	void SetText(const std::string& sText) { this->sText = sText; }
	void SetWidth(const int& width_) { iWidth = width_; }
	void SetHeight(const int& height_) { iHeight = height_; }

	int GetWidth() const { return iWidth; }
	int GetHeight() const { return iHeight; }
	std::string GetText() const { return sText; }
	SDL_Texture* GetTexure() const { return texture; }

private:
	std::string sText;
	SDL_Color text_color;
	SDL_Texture* texture;

	int iWidth;
	int iHeight;
};

#endif
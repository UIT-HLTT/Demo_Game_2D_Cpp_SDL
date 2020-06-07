#include "Text.h"

Text::Text(void)
{
	sText = "";
	iWidth = 0;
	iHeight = 0;
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	texture = NULL;
}

Text::~Text(void)
{
	Free();
}

void Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	Free();

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, sText.c_str(), text_color);

	if (text_surface != NULL)
	{
		texture = SDL_CreateTextureFromSurface(screen, text_surface);
		iWidth = text_surface->w;
		iHeight = text_surface->h;

		SDL_FreeSurface(text_surface);
	}
}

void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void Text::SetColor(int type)
{
	switch (type)
	{
	case RED_TEXT:
	{
		SDL_Color color = { 255, 0, 0 };
		text_color = color;
	}
	break;

	case WHITE_TEXT:
	{
		SDL_Color color = { 255, 255, 255 };
		text_color = color;
	}
	break;

	case BLACK_TEXT:
	{
		SDL_Color color = { 0, 0, 0 };
		text_color = color;
	}
	break;

	case GRAY_TEXT_1:
	{
		SDL_Color color = { 128, 128, 128 };
		text_color = color;
	}
	break;

	case GRAY_TEXT_2:
	{
		SDL_Color color = { 167, 175, 180 };
		text_color = color;
	}
	break;

	case ANTIQUEWHITE_TEXT:
	{
		SDL_Color color = { 205, 192, 176 };
		text_color = color;
	}
	break;
	}
}

void Text::Draw(SDL_Renderer* screen,
	int xp, int yp,
	SDL_Rect* clip/*= NULL*/,
	double angle/*= 0.0*/,
	SDL_Point* center/*= NULL*/,
	SDL_RendererFlip flip/*= SDL_FLIP_NONE*/)
{
	SDL_Rect renderQuad = { xp, yp, iWidth, iHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
}

void Text::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}
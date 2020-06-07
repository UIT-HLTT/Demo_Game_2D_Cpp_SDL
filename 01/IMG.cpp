#include "IMG.h"

IMG::IMG(void)
{

}
IMG::IMG(std::string file_name, SDL_Renderer* screen)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;

	LoadIMG(file_name, screen);
}

IMG::~IMG(void)
{
	Free();
}

void IMG::LoadIMG(std::string file_name, SDL_Renderer* screen)
{
	Free();

	file_name = "file//image//" + file_name + ".png";
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(file_name.c_str());

	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}

	tIMG = new_texture;
}

void IMG::Draw(SDL_Renderer* screen, const SDL_Rect* clip/*= NULL*/)
{
		SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
		SDL_RenderCopy(screen, tIMG, clip, &renderquad);
}

void IMG::Draw(SDL_Renderer* screen, int x, int y)
{
	rect.x = x;
	rect.y = y;

	SDL_RenderCopy(screen, tIMG, NULL, &rect);
}

void IMG::Draw(SDL_Renderer* screen, int x, int y, bool bRotate) 
{
	rect.x = x;
	rect.y = y;

	if (!bRotate) {
		SDL_RenderCopy(screen, tIMG, NULL, &rect);
	}
	else {
		SDL_RenderCopyEx(screen, tIMG, NULL, &rect, 180.0, NULL, SDL_FLIP_VERTICAL);
	}
}

void IMG::Free()
{
	if (tIMG != NULL)
	{
		SDL_DestroyTexture(tIMG);
		tIMG = NULL;
		rect.w = 0;
		rect.h = 0;
		rect.x = 0;
		rect.y = 0;
	}
}
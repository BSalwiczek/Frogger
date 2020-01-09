#pragma once
#include <stdio.h>

#define SCREEN_WIDTH	720
#define SCREEN_HEIGHT	920

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
#include"../SDL2-2.0.10/include/SDL_image.h"
}

#ifdef __cplusplus
extern "C"
#endif


class Draw
{
public:
	SDL_Texture* charset;
	SDL_Texture* charset2;
	SDL_Texture* background;
	SDL_Surface* screen;
	SDL_Renderer* renderer;
	SDL_Texture* scrtex;


	int black, green, red;
	bool error;

	Draw(SDL_Renderer* renderer);
	~Draw();
	void DrawString(int x, int y, const char* text, SDL_Texture* charset, int size);
	void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	void DrawFullScreenTexture();
	bool drawPartOfTexture(SDL_Renderer* renderer, SDL_Texture* texture, int X, int Y, SDL_Rect SrcR, double angle, SDL_RendererFlip flip);
};
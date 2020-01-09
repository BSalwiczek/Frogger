#include "Base.h"

Base::Base(SDL_Texture* texture, int posX, int posY) : Entity(texture, posX, posY, 0)
{
	width = BASE_SIZE;
	height = BASE_SIZE;
	visible = false;
}

void Base::show(Draw* draw)
{
	SDL_Rect rect = { BASE_SIZE,0,width,height };
	if(visible)
		draw->drawPartOfTexture(draw->renderer, texture, (int)posX, (int)posY, rect, 0, SDL_FLIP_NONE);
}
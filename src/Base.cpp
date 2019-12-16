#include "Base.h"

Base::Base(SDL_Texture* texture, int posX, int posY)
{
	this->texture = texture;
	this->posX = posX;
	this->posY = posY;
	this->width = 48;
	this->height = 48;
	this->visible = false;
}

void Base::show(Draw* draw)
{
	SDL_Rect rect;
	rect.h = this->height;
	rect.w = this->width;
	rect.x = 48;
	rect.y = 0;
	if(visible)
		draw->drawPartOfTexture(draw->renderer, this->texture, this->posX, this->posY, rect, 0, SDL_FLIP_NONE);
}
#include "Wood.h"


Wood::Wood(SDL_Texture* texture, int posX, int posY, int size, int velocity)
{
	this->texture = texture;
	this->posX = posX;
	this->posY = posY;

	this->size = size;
	this->height = 34;
	this->velocity = velocity;
	this->step = 0;
	this->direction = right;
}

void Wood::show(Draw* draw)
{
	SDL_Rect beginningRect;
	beginningRect.x = 0;
	beginningRect.y = 0;
	beginningRect.w = BEGIN_WIDTH;
	beginningRect.h = this->height;

	draw->drawPartOfTexture(draw->renderer, this->texture, this->posX, this->posY, beginningRect, 0, SDL_FLIP_NONE);


	for (int i = 0; i < size; i++)
	{
		SDL_Rect middleRect;
		middleRect.x = BEGIN_WIDTH + 1;
		middleRect.y = 0;
		middleRect.w = MIDDLE_WIDTH;
		middleRect.h = this->height;
		draw->drawPartOfTexture(draw->renderer, this->texture, this->posX + BEGIN_WIDTH + MIDDLE_WIDTH*i, this->posY, middleRect, 0, SDL_FLIP_NONE);
	}


	SDL_Rect endRect;
	endRect.x = BEGIN_WIDTH + MIDDLE_WIDTH + 2;
	endRect.y = 0;
	endRect.w = END_WIDTH;
	endRect.h = this->height;
	draw->drawPartOfTexture(draw->renderer, this->texture, this->posX + BEGIN_WIDTH + MIDDLE_WIDTH*size, this->posY, endRect, 0, SDL_FLIP_NONE);

	this->width = BEGIN_WIDTH + MIDDLE_WIDTH * size + END_WIDTH;

}

void Wood::move(int fps)
{
	if (fps > 0)
		this->step = velocity * (1 / (double)fps) + this->step;
	if (this->step >= 1)
	{
			this->posX += 1;
		if (this->posX > SCREEN_WIDTH * 2 - this->width)
			this->posX = -this->width;
		if (this->posX < -SCREEN_WIDTH + this->width)
			this->posX = SCREEN_WIDTH + this->width;

		this->step = 0;
	}
}
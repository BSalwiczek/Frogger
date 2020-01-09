#include "Wood.h"

Wood::Wood(SDL_Texture* texture, int posX, int posY, int size, int velocity) : Entity(texture, posX, posY, velocity)
{
	this->size = size;
	height = WOOD_HEIGHT;
	direction = right;
}

void Wood::show(Draw* draw)
{
	SDL_Rect beginningRect = {0,0,WOOD_BEGIN_WIDTH,height};
	draw->drawPartOfTexture(draw->renderer, texture, (int)posX, (int)posY, beginningRect, 0, SDL_FLIP_NONE);

	SDL_Rect middleRect = { WOOD_BEGIN_WIDTH + 1,0,WOOD_MIDDLE_WIDTH,height };
	for (int i = 0; i < size; i++)
	{
		draw->drawPartOfTexture(draw->renderer, texture, (int)(posX + WOOD_BEGIN_WIDTH + WOOD_MIDDLE_WIDTH*i), (int)posY, middleRect, 0, SDL_FLIP_NONE);
	}

	SDL_Rect endRect = { WOOD_BEGIN_WIDTH + WOOD_MIDDLE_WIDTH + 2, 0, WOOD_END_WIDTH, height};
	draw->drawPartOfTexture(draw->renderer, texture, (int)(posX + WOOD_BEGIN_WIDTH + WOOD_MIDDLE_WIDTH*size), (int)posY, endRect, 0, SDL_FLIP_NONE);

	width = WOOD_BEGIN_WIDTH + WOOD_MIDDLE_WIDTH * size + WOOD_END_WIDTH;
}
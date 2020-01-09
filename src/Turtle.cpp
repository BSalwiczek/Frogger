#include "Turtle.h"

Turtle::Turtle(SDL_Texture* texture, int posX, int posY, int size, int velocity) : Entity(texture, posX, posY, velocity)
{
	this->size = size;
	diving = false;
	width = TURTLE_WIDTH*size;
	height = TURTLE_HEIGHT;
	direction = left;
	animation_state = swim_start;

}

void Turtle::show(Draw* draw)
{
	for (int i = 0; i < size; i++)
	{
		SDL_Rect Rect = {0,0,TURTLE_WIDTH, TURTLE_HEIGHT};

		switch (animation_state)
		{
		case swim_start:
			Rect.x = 0;
			break;
		case swim_middle:
			Rect.x = TURTLE_WIDTH + 1;
			break;
		case swim_end:
			Rect.x = 2*(TURTLE_WIDTH + 1);
			break;
		case diving_start:
			Rect.x = 3 * (TURTLE_WIDTH + 1);
			break;
		case diving_end:
			Rect.x = 3 * (TURTLE_WIDTH + 1);
			break;
		case diving_middle:
			Rect.x = 4 * (TURTLE_WIDTH + 1);
			break;
		}
		draw->drawPartOfTexture(draw->renderer, texture, (int)(posX + TURTLE_WIDTH * i), (int)posY, Rect, 0, SDL_FLIP_NONE);
	}
}

void Turtle::animate()
{
	if (SDL_GetTicks() - last_animation_time > 20000 / velocity)
	{
		if(!diving) 
		{
			switch (animation_state)
			{
			case swim_start:
				animation_state = swim_middle;
				break;
			case swim_middle:
				animation_state = swim_end;
				break;
			case swim_end:
				animation_state = swim_start;
				break;
			}
			last_animation_time = SDL_GetTicks();
		}
	}

	if (SDL_GetTicks() - last_animation_time > 50000 / velocity)
	{
		if (diving)
		{
			switch (animation_state)
			{
			case diving_start:
				animation_state = diving_middle;
				break;
			case diving_middle:
				animation_state = diving_end;
				break;
			case diving_end:
				animation_state = swim_start;
				diving = false;
				break;
			default:
				animation_state = diving_start;
				break;
			}
			last_animation_time = SDL_GetTicks();
		}
	}
	
}

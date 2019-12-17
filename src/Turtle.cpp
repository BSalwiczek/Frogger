#include "Turtle.h"

Turtle::Turtle(SDL_Texture* texture, int posX, int posY, int size, int velocity)
{
	this->texture = texture;
	this->posX = posX;
	this->posY = posY;
	this->size = size;
	this->velocity = velocity;
	step = 0;
	width = TURTLE_WIDTH*size;
	height = TURTLE_HEIGHT;
	direction = left;
	last_animation_time = SDL_GetTicks();
	animation_state = swim_start;

}

void Turtle::show(Draw* draw)
{
	for (int i = 0; i < size; i++)
	{
		SDL_Rect Rect;
		Rect.x = 0;
		Rect.y = 0;
		Rect.w = TURTLE_WIDTH;
		Rect.h = TURTLE_HEIGHT;

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

		}

		draw->drawPartOfTexture(draw->renderer, texture, posX + TURTLE_WIDTH * i, posY, Rect, 0, SDL_FLIP_NONE);
	}
}

void Turtle::move(int fps)
{
	setAnimation();

	if (fps > 0)
		this->step = velocity * (1 / (double)fps) + this->step;
	if (this->step >= 1)
	{
		this->posX -= 1;
		if (this->posX > SCREEN_WIDTH * 2 - this->width)
			this->posX = -this->width;
		if (this->posX < -SCREEN_WIDTH + this->width)
			this->posX = SCREEN_WIDTH + this->width;

		this->step = 0;
	}
}

void Turtle::setAnimation()
{
	if (SDL_GetTicks() - last_animation_time > 20000/velocity)
	{
		switch(animation_state)
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

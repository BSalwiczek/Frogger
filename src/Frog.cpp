#include "Frog.h"

Frog::Frog(SDL_Renderer* renderer)
{
	error = false;
	jump_distance = 53;
	jump_velocity = 130;
	direction = none;

	SDL_Surface* frogSprite = SDL_LoadBMP("src/bmp/frog.bmp");
	if (frogSprite == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		error = true;
	}
	goToStart();

	frogTexture = SDL_CreateTextureFromSurface(renderer, frogSprite);

	last_animation_time = SDL_GetTicks();
	animation_state = a_stand; 
	last_time_jumped = 0;
	jumping = false;
	moveable = true;
	first_move = true;
	lives = 3;
	this->external_velocity = 0;
	this->external_velocity_direction = right;
	current_steps = 0;
	step = 0;
}

void Frog::showFrog(Draw* draw)
{
	setAnimation();
	SDL_Rect SrcR = {0,0,41,42};

	this->width = 41;
	this->height = 42;

	switch (animation_state)
	{
	case a_jump:
		SrcR.x = 42;
		this->width = 41;
		this->height = 46;
		break;
	case a_stand:
		SrcR.x = 83;
		this->width = 40;
		this->height = 33;
		break;
	}

	SrcR.w = this->width;
	SrcR.h = this->height;


	if(direction == left)
		draw->drawPartOfTexture(draw->renderer, frogTexture, posX, posY, SrcR, 90, SDL_FLIP_VERTICAL);
	if (direction == right)
		draw->drawPartOfTexture(draw->renderer, frogTexture, posX, posY, SrcR, 90, SDL_FLIP_NONE);
	else if (direction == down)
		draw->drawPartOfTexture(draw->renderer, frogTexture, posX, posY, SrcR, 180, SDL_FLIP_NONE);
	else if (direction == up || direction == none)
		draw->drawPartOfTexture(draw->renderer, frogTexture, posX, posY, SrcR, 0, SDL_FLIP_NONE);
}

void Frog::setAnimation()
{
	if (SDL_GetTicks() - last_animation_time > 150)
	{
		if (animation_state == a_land)
			animation_state = a_stand;

		if (animation_state == a_jump)
			animation_state = a_land;

		last_animation_time = SDL_GetTicks();
	}

}

void Frog::jump(SDL_Keycode key)
{
	if (!jumping && SDL_GetTicks() - last_time_jumped > 200 && moveable)
	{
		if (direction != none)
		{
			if (first_move)
				first_move = false;

			jumping = true;
			animation_state = a_jump; 
		}

		
		if (key == SDLK_UP)
			direction = up;
		else if (key == SDLK_DOWN)
			direction = down;
		else if (key == SDLK_LEFT)
			direction = left;
		else if (key == SDLK_RIGHT)
			direction = right;
		else
			direction = none;
	}

}

void Frog::move(int fps)
{
	if (jumping)
	{
		//if (fps > 0)
		//	this->step = this->jump_velocity * (1 / (double)fps) + this->step;

		step = 1;
		if (step >= 1)
		{
			switch (direction)
			{
			case left:
				posX -= step;
				break;
			case right:
				posX += step;
				break;
			case up:
				posY -= step;
				break;
			case down:
				posY += step;
				break;
			default:
				break;
			}

			current_steps += step;
			if (current_steps >= jump_distance)
			{
				jumping = false;
				last_time_jumped = SDL_GetTicks();
				current_steps = 0;
			}

			step = 0;
		}
	}
	else if (external_velocity > 0)
	{
		if (fps > 0)
			this->step = this->external_velocity * (1 / (double)fps) + this->step;

		if (step >= 1)
		{
			switch (external_velocity_direction)
			{
			case left:
				posX -= 1;
				break;
			case right:
				posX += 1;
				break;
			case up:
				posY -= 1;
				break;
			case down:
				posY += 1;
				break;
			default:
				break;
			}
			step = 0;
		}
	}
}

void Frog::die()
{
	if (this->lives > 0)
	{
		lives--;
		external_velocity = 0;
		goToStart();
	}
}

void Frog::goToStart()
{
	first_move = true;
	posX = START_X;
	posY = START_Y;
	lowestY = posY;
	jumping = false;
	current_steps = 0;
	last_time_jumped = SDL_GetTicks();
}

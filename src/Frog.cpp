#include "Frog.h"

Frog::Frog(SDL_Texture* texture) : Entity(texture, posX, posY, 500)
{
	error = false;
	jumping = false;
	moveable = true;
	first_move = true;

	jump_distance = 53;
	direction = none;

	animation_state = a_stand; 
	last_time_jumped = 0;
	lives = MAX_LIVES;
	external_velocity = 0;
	external_velocity_direction = right;
	current_steps = 0;

	goToStart();
}

void Frog::showFrog(Draw* draw)
{
	setAnimation();
	SDL_Rect SrcR = {0,0,FROG_WIDTH,FROG_HEIGHT};

	width = FROG_WIDTH;
	height = FROG_HEIGHT;

	switch (animation_state)
	{
	case a_jump:
		SrcR.x = FROG_WIDTH + 1;
		height = FROG_HEIGHT + 4;
		break;
	case a_stand:
		SrcR.x = FROG_WIDTH*2 + 1;
		width = FROG_WIDTH - 1;
		height = FROG_HEIGHT - 9;
		break;
	}

	SrcR.w = width;
	SrcR.h = height;

	if(direction == left)
		draw->drawPartOfTexture(draw->renderer, texture, (int)posX, (int)posY, SrcR, 90, SDL_FLIP_VERTICAL);
	if (direction == right)
		draw->drawPartOfTexture(draw->renderer, texture, (int)posX, (int)posY, SrcR, 90, SDL_FLIP_NONE);
	else if (direction == down)
		draw->drawPartOfTexture(draw->renderer, texture, (int)posX, (int)posY, SrcR, 180, SDL_FLIP_NONE);
	else if (direction == up || direction == none)
		draw->drawPartOfTexture(draw->renderer, texture, (int)posX, (int)posY, SrcR, 0, SDL_FLIP_NONE);
}

void Frog::setAnimation()
{
	if (SDL_GetTicks() - last_animation_time > 100)
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
	if (!jumping && SDL_GetTicks() - last_time_jumped > 100 && moveable)
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

void Frog::move(double delta)
{
	if (jumping)
	{
		int step = delta * velocity;
		if (jump_distance - current_steps <= 1)
			step = jump_distance - current_steps;
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
	} else if (external_velocity > 0)
	{
		switch (external_velocity_direction)
		{
		case left:
			posX -= external_velocity * delta;
			break;
		case right:
			posX += external_velocity * delta;
			break;
		}
	}
}

void Frog::die()
{
	if (lives > 0)
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

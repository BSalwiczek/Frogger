#include "LittleFrog.h"


LittleFrog::LittleFrog(SDL_Texture* texture, int posX, int woodWidth, int posY) : Frog(texture)
{
	this->posX = posX;
	this->posY = posY;
	this->woodWidth = woodWidth;
	follow = false;
	jumping = true;
	direction = right;
	animation_state = a_jump;
	moveable = true;
	woodX = posX;
}

void LittleFrog::checkIfTooFar()
{
	if (posX > SCREEN_WIDTH * 2 - width)
		posX = -width;
	if (posX < -SCREEN_WIDTH + width)
		posX = SCREEN_WIDTH + width;

	if (woodX > SCREEN_WIDTH * 2 - woodWidth)
		woodX = -woodWidth;
}

void LittleFrog::moveAround(double fps)
{
	if (!follow)
	{
		switch (external_velocity_direction)
		{
		case left:
			woodX -= fps * external_velocity;
			break;
		case right:
			woodX += fps * external_velocity;
			break;
		}

		if (posX - woodWidth > SCREEN_WIDTH)
			posX = woodX;

		if (!jumping && SDL_GetTicks() - last_time_jumped > 2000 && moveable && posX < SCREEN_WIDTH)
		{
			if (first_move)
				first_move = false;

			if (posX + jump_distance < woodX + woodWidth && rand() % 100 > 50)
			{
				jumping = true;
				animation_state = a_jump;
				direction = right;
			}
			else if(rand() % 100 > 50 && woodX < posX - jump_distance) {
				jumping = true;
				animation_state = a_jump;
				direction = left;
			}
		}
	}
}

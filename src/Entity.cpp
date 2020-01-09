#include "Entity.h"

Entity::Entity(SDL_Texture* texture, double posX, double posY, int velocity = 0)
{
	this->texture = texture;
	this->posX = posX;
	this->posY = posY;
	this->velocity = velocity;
	direction = up;
	last_animation_time = SDL_GetTicks();
}

bool Entity::collision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	if (beetwen(posY + height, frogY + frogHeight, frogY) || beetwen(posY, frogY + frogHeight, frogY))
	{
		if (beetwen(posX + width, frogX + frogWidth, frogY))
			return true;
		if (beetwen(posX, frogX + frogWidth, frogX))
			return true;
	}

	if (fabsf(posX + width / 2 - frogX - frogWidth / 2) <= width / 2 + frogWidth / 2 && fabsf(posY + height / 2 - frogY - frogHeight / 2) <= height / 2 + frogHeight / 2)
		return true;
	return false;
}

bool Entity::centerCollision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	int frogCenterX = frogX + frogWidth / 2;
	int frogCenterY = frogY + frogHeight / 2;

	if (posY <= frogCenterY && posY + height >= frogCenterY)
	{
		if (posX <= frogCenterX && posX + width >= frogCenterX)
		{
			return true;
		}
	}
	return false;
}


bool Entity::beetwen(int x, int up, int down)
{
	if (x<up && x>down)
		return true;
	return false;
}

void Entity::move(double delta)
{
	if (direction == left)
		posX -= velocity * delta;
	if (direction == right)
		posX += velocity * delta;
	if (posX > SCREEN_WIDTH * 2 - width)
		posX = -this->width;
	if (posX < -SCREEN_WIDTH + width)
		posX = SCREEN_WIDTH + width;
}
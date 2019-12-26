#include "Entity.h"


Entity::Entity()
{
	direction = up;
	velocity = 1;
}

bool Entity::collision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	int centerX = this->posX + this->width / 2;
	int centerY = this->posY + this->height / 2;
	int frogCenterX = frogX + frogWidth / 2;
	int frogCenterY = frogY + frogHeight / 2;

	if (beetwen(centerY + this->height / 2, frogCenterY + frogHeight / 2, frogCenterY - frogHeight / 2))
	{
		if (beetwen(centerX  + this->width / 2, frogCenterX + frogWidth / 2, frogCenterX - frogWidth / 2))
			return true;
		if (beetwen(centerX - this->width / 2, frogCenterX + frogWidth / 2, frogCenterX - frogWidth / 2))
			return true;
	}

	if (beetwen(centerY - this->height / 2, frogCenterY + frogHeight / 2, frogCenterY - frogHeight / 2))
	{
		if (beetwen(centerX + this->width / 2, frogCenterX + frogWidth / 2, frogCenterX - frogWidth / 2))
			return true;
		if (beetwen(centerX - this->width / 2, frogCenterX + frogWidth / 2, frogCenterX - frogWidth / 2))
			return true;
	}

	if (abs(centerX - frogCenterX) <= this->width / 2 + frogWidth /2 && abs(centerY - frogCenterY) <= this->height / 2 + frogHeight /2 )
		return true;

	return false;
}

bool Entity::centerCollision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	int frogCenterX = frogX + frogWidth / 2;
	int frogCenterY = frogY + frogHeight / 2;

	if (this->posY <= frogCenterY && this->posY + this->height >= frogCenterY)
	{
		if (this->posX <= frogCenterX && this->posX + this->width >= frogCenterX)
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
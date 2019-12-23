#include "LittleFrog.h"


LittleFrog::LittleFrog(SDL_Texture* texture, int posX, int posY) : Frog(texture)
{
	this->posX = posX;
	this->posY = posY;
	follow = false;
	//frogTexture = texture;
}

void LittleFrog::checkIfTooFar()
{
	if (this->posX > SCREEN_WIDTH * 2 - this->width)
		this->posX = -this->width;
	if (this->posX < -SCREEN_WIDTH + this->width)
		this->posX = SCREEN_WIDTH + this->width;
}

bool LittleFrog::collision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	int centerX = this->posX + this->width / 2;
	int centerY = this->posY + this->height / 2;
	int frogCenterX = frogX + frogWidth / 2;
	int frogCenterY = frogY + frogHeight / 2;

	//if (beetwen(this->posY + this->height / 2, frogY + frogHeight / 2, frogY - frogHeight / 2))
	//{

	//	if (beetwen(this->posX + this->width / 2, frogX + frogWidth / 2, frogX - frogWidth / 2))
	//		return true;
	//	if (beetwen(this->posX - this->width / 2, frogX + frogWidth / 2, frogX - frogWidth / 2))
	//		return true;
	//}

	//if (beetwen(this->posY - this->height / 2, frogY + frogHeight / 2, frogY - frogHeight / 2))
	//{
	//	if (beetwen(this->posX + this->width / 2, frogX + frogWidth / 2, frogX - frogWidth / 2))
	//		return true;
	//	if (beetwen(this->posX - this->width / 2, frogX + frogWidth / 2, frogX - frogWidth / 2))
	//		return true;
	//}

	if (beetwen(centerY + this->height / 2, frogCenterY + frogHeight / 2, frogCenterY - frogHeight / 2))
	{
		if (beetwen(centerX + this->width / 2, frogCenterX + frogWidth / 2, frogCenterX - frogWidth / 2))
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

	if (abs(centerX - frogCenterX) <= this->width / 2 + frogWidth / 2 && abs(centerY - frogCenterY) <= this->height / 2 + frogHeight / 2)
		return true;

	return false;
}

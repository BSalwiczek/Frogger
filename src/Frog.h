#pragma once
#include "draw.h"
#include "Entity.h"


#define START_X SCREEN_WIDTH / 2 - 20
#define START_Y SCREEN_HEIGHT - 139

typedef enum {
	a_stand,
	a_jump,
	a_land
} frog_animation;

class Frog: public Entity
{
	frog_animation animation_state;

	int last_animation_time;

	int last_time_jumped;
	bool moveable;

	double step, current_steps;

	int last_posX, last_posY;
public:
	SDL_Texture* frogTexture;
	bool jumping;
	bool error;
	int jump_distance;
	
	int jump_velocity;
	int external_velocity;

	direction_t velocity_direction, external_velocity_direction;

	int posX, posY, width, height;
	short lives;

	Frog(SDL_Renderer* renderer);
	void showFrog(Draw* draw);
	void setAnimation();
	void move(int fps);
	void jump(SDL_Keycode key);
	void die();
	void goToStart();
};

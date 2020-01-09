#pragma once
#include "draw.h"
#include "Entity.h"


#define START_X SCREEN_WIDTH / 2 - 20
#define START_Y SCREEN_HEIGHT - 139
#define MAX_LIVES 5
#define FROG_WIDTH 41
#define FROG_HEIGHT 42

typedef enum {
	a_stand,
	a_jump,
	a_land
} frog_animation;

class Frog: public Entity
{
public:
	frog_animation animation_state;

	bool jumping, error, moveable, first_move;

	double current_steps;
	int jump_distance, external_velocity, last_time_jumped;

	direction_t velocity_direction, external_velocity_direction;

	int lowestY;
	short lives;

	Frog(SDL_Texture* texture);
	void showFrog(Draw* draw);
	void setAnimation();
	void move(double delta);
	void jump(SDL_Keycode key);
	void die();
	void goToStart();
};

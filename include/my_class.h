#ifndef __MY_CLASS_H__
#define __MY_CLASS_H__

#include "my_attack.h"

typedef struct ClassType_S
{
	Moveset *attacks;
	float movespeed;
	float attack;
	float defense;
	float stamina;
	float throwspeed;
}ClassType;

/*
	@brief sets up the 3 available class presets
*/
void class_init();

/*
	@brief returns the Rectcol preset based on the current frame of the attack
*/
Rectcol *class_get_hit(Uint8 attack_frame, Uint8 attack, Uint8 type);

/*
	@brief returns the amount of frames in the specified attack
*/
Uint8 class_get_frames(Uint8 attack);

float class_get_throw(Uint8 type);

Uint8 class_get_damage(Uint8 attack, Uint8 type);

#endif
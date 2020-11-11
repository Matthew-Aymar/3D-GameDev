#ifndef __MY_ATTACK_H__
#define __MY_ATTACK_H__

#include "my_collider.h"

typedef struct Attack_S
{
	float speed;
	Rectcol *hits; //collection of hitboxes to follow the motion of the attack
	Uint8 frames; //how many frames the hitboxes should be active for
} Attack;

typedef struct Moveset_S
{
	Attack *light1;
	Attack *light2;
	Attack *heavy;
} Moveset;

void attack_init();

Moveset *attack_get_moveset();

#endif
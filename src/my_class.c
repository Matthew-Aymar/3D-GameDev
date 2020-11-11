#include "my_class.h"
#include "simple_logger.h"

ClassType Stinger;
ClassType Exe;
ClassType Shin;

void class_init()
{
	Stinger.attacks = attack_get_moveset(0);
	Exe.attacks = attack_get_moveset(1);
	Shin.attacks = attack_get_moveset(2);

	Stinger.throwspeed = 2;
	Exe.throwspeed = 1;
	Shin.throwspeed = 3;
}

Rectcol* class_get_hit(Uint8 attack_frame, Uint8 attack, Uint8 type)
{
	if (type == 0)
	{
		if (attack == 0)
			return &Stinger.attacks->light1->hits[attack_frame];
		else if (attack == 1)
			return &Stinger.attacks->light2->hits[attack_frame];
		else if (attack == 2)
			return &Stinger.attacks->heavy->hits[attack_frame];
	}
	else if (type == 1)
	{
		if (attack == 0)
			return &Exe.attacks->light1->hits[attack_frame];
		else if (attack == 1)
			return &Exe.attacks->light2->hits[attack_frame];
		else if (attack == 2)
			return &Exe.attacks->heavy->hits[attack_frame];
	}
	else if (type == 2)
	{
		if (attack == 0)
			return &Shin.attacks->light1->hits[attack_frame];
		else if (attack == 1)
			return &Shin.attacks->light2->hits[attack_frame];
		else if (attack == 2)
			return &Shin.attacks->heavy->hits[attack_frame];
	}
}

Uint8 class_get_frames(Uint8 attack)
{
	if (attack == 0)
		return Stinger.attacks->light1->frames;
	else if (attack == 1)
		return Exe.attacks->light2->frames;
	else if (attack == 2)
		return Shin.attacks->heavy->frames;
}

float class_get_throw(Uint8 type)
{
	if (type == 0)
		return Stinger.throwspeed;
	else if (type == 1)
		return Exe.throwspeed;
	else if (type == 2)
		return Shin.throwspeed;
}
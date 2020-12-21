#ifndef __MY_BOT_H__
#define __MY_BOT_H__

#include "my_entity.h"
#include "my_player.h"
#include "my_class.h"

typedef struct Bot_S
{
	Uint8 _dead;
	Entity *ent;
	Player *target;
	Uint8 state;
	Uint8 iframes;
	int health;
	Uint8 respawn;
} Bot;

void bot_new(Bot *b, Player *target);

void bot_update(Bot *b);

void bot_respawn(Bot *b);

#endif
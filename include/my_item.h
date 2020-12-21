#ifndef __MY_ITEM_H__
#define __MY_ITME_H__

#include "my_player.h"

typedef struct Item_S
{
	Entity *ent;
	Uint8 type;
	Uint8 respawn;
} Item;

void item_new(Item *i, Uint8 type);

void item_draw(Item *i, Uint32 bufferFrame, VkCommandBuffer commandBuffer);

void item_update(Item *i, Player *p);

void item_heal(Player *p);

void item_stim(Player *p);

void item_sped(Player *p);

void item_atks(Player *p);

void item_fire(Player *p);

#endif
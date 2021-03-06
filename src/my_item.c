#include "my_item.h"
#include "simple_logger.h"

void item_new(Item *i, Uint8 type)
{
	i->ent = entity_new();
	i->ent->model = gf3d_model_load_animated("item", 1, 39);
	if (type == 0)
		i->ent->position = vector3d(0, 0, 4);
	else if (type == 1)
		i->ent->position = vector3d(-25, 25, 4);
	else if (type == 2)
		i->ent->position = vector3d(-25, -25, 4);
	else if (type == 3)
		i->ent->position = vector3d(25, -25, 4);
	else if (type == 4)
		i->ent->position = vector3d(25, 25, 4);
	gfc_matrix_make_translation(i->ent->modelmat, i->ent->position);
	collider_new(&i->ent->col, i->ent->position, vector3d(1, 1, 1), Kinematic);
	i->ent->_dead = true;
	i->type = type;
}

void item_update(Item *i, Player *p)
{
	if (i->respawn <= 0)
	{
		if (collider_rect_rect(&i->ent->col, &p->ent->col))
		{
			i->respawn = 255;
			if (i->type == 0)
				item_heal(p);
			else if (i->type == 1)
				item_stim(p);
			else if (i->type == 2)
				item_sped(p);
			else if (i->type == 3)
				item_atks(p);
			else if (i->type == 4)
				item_fire(p);
		}
	}
	else
	{
		i->respawn--;
	}
}

void item_draw(Item *i, Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
	if (i->respawn > 0)
		return;
	gf3d_model_draw(i->ent->model, bufferFrame, commandBuffer, i->ent->modelmat, (Uint32)i->ent->frame);
	i->ent->frame += 0.1;
	if (i->ent->frame >= i->ent->model->frameCount)
		i->ent->frame = 0;
}

void item_heal(Player *p)
{
	p->health = p->max_health;
}

void item_stim(Player *p)
{
	p->stim = 255;
}

void item_sped(Player *p)
{
	p->sped = 255;
}

void item_atks(Player *p)
{
	p->atks = 255;
}

void item_fire(Player *p)
{
	p->fire = 255;
}
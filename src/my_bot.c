#include "my_bot.h"
#include "simple_logger.h"

void bot_new(Bot *b, Player *target)
{
	b->ent = entity_new();
	collider_new(&b->ent->col, vector3d(0, 0, 0), vector3d(5, 5, 10), Kinematic);
	b->target = target;
	b->state = 0;
	b->health = 100;
}

void bot_update(Bot *b)
{
	Vector3D bot_position;
	Vector3D target_position;
	Vector3D direction;
	float speed = 0.1;
	float up = 0;
	Uint8 x;
	Rectcol fire;
	if (b->_dead)
		bot_respawn(b);

	bot_position.x = b->ent->position.x;
	bot_position.y = b->ent->position.y;
	bot_position.z = b->ent->position.z;

	target_position.x = b->target->ent->position.x;
	target_position.y = b->target->ent->position.y;
	target_position.z = b->target->ent->position.z;

	direction.x = bot_position.x - target_position.x;
	direction.y = bot_position.y - target_position.y;
	direction.z = bot_position.z - target_position.z;
	vector3d_normalize(&direction);

	if (b->state == 0)
	{
		//attempting to move towards player
		b->ent->col.position.x -= direction.x * speed;

		entity_check_col(b->ent);

		if (entity_get_col_by_type(b->ent, Wall))
		{
			//revert
			b->ent->col.position.x += direction.x * (speed + 1);
		}
		else
		{
			b->ent->position.x -= direction.x * speed;
		}

		b->ent->col.position.y -= direction.y * speed;

		entity_check_col(b->ent);

		if (entity_get_col_by_type(b->ent, Wall))
		{
			//revert
			b->ent->col.position.y += direction.y * (speed + 1);
		}
		else
		{
			b->ent->position.y -= direction.y * speed;
		}

		//jump if player is above
		if (direction.z < 0 && b->ent->grounded)
		{
			b->ent->vel = 1;
			b->ent->accel = 0.035;
			b->ent->grounded = false;
		}

		up = b->ent->vel;
		b->ent->col.position.z += up;

		entity_check_col(b->ent);

		if (entity_get_col_by_type(b->ent, Ground) && up < 0)
		{
			b->ent->col.position.z -= up;
			b->ent->vel = 0;
			b->ent->accel = 0;
			b->ent->grounded = true;
		}
		else if (!entity_get_col_by_type(b->ent, Ground))
		{
			b->ent->position.z += up;
			b->ent->accel = 0.035;
			b->ent->grounded = false;
		}
	}
	else if (b->state == 1)
	{

	}

	if (b->target->fire)
	{
		collider_new(&fire, b->target->ent->position, vector3d(6, 6, 6), Kinematic);
		if (collider_rect_rect(&b->ent->col, &fire))
		{
			b->health--;
			if (b->health <= 0)
			{
				b->_dead = true;
				b->ent->_dead = true;
				b->respawn = 200;
			}
		}
	}

	if (b->iframes <= 0)
	{
		for (x = 0; x < 3; x++)
		{
			if (collider_rect_rect(&b->ent->col, &b->target->attack_hits[x]) || (collider_rect_rect(&b->ent->col, &b->target->ent->col) && b->target->attacking))
			{
				b->health -= class_get_damage(b->target->attack, b->target->class_type);
				if (b->health <= 0)
				{
					b->_dead = true;
					b->ent->_dead = true;
					b->respawn = 200;
				}
				b->iframes = 15;
				break;
			}
		}
	}
	else
	{
		b->iframes--;
	}
}

void bot_respawn(Bot *b)
{
	if (b->respawn > 0)
	{
		b->respawn--;
	}
	else
	{
		b->health = 100;
		b->ent->_dead = false;
		b->_dead = false;
		b->ent->position = vector3d(0, 0, 5);
	}
}
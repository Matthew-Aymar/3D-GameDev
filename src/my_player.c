#include "my_player.h"

#include "simple_logger.h"

typedef struct PlayerManager_s
{
	Player *players;
	Uint8 *myplayer;
	Uint8 player_max;
}PlayerManager;

static PlayerManager player_manager = { 0 };

void player_manager_close()
{
	if (player_manager.players != NULL)
	{
		free(player_manager.players);
	}
	memset(&player_manager, 0, sizeof(Player));
}

void player_manager_init(Uint8 Max)
{
	player_manager.player_max = Max;
	player_manager.players = (Player*)gfc_allocate_array(sizeof(Player), player_manager.player_max);
	if (!player_manager.players)
	{
		slog("Failed to allocate player list");
		return;
	}
	atexit(player_manager_close);
}

Player *player_new(Uint8 id)
{
	int i = 0;
	for (i = 0; i < player_manager.player_max; i++)
	{
		if (player_manager.players[i]._playernum != NULL)
		{
			continue;
		}
		else
		{
			memset(&player_manager.players[i], 0, sizeof(Player));
			player_manager.players[i]._playernum = id;
			player_manager.players[i].ent = entity_new();
			player_manager.players[i].armed = true;
			return &player_manager.players[i];
		}
	}
	slog("No empty space in player array");
	return NULL;
}

void player_free(Player *p)
{
	if (!p)
	{
		slog("Null pointer in player_free!");
		return;
	}
	p->_playernum = 0;
	entity_free(p->ent);
}

Player *player_get_by_num(Uint8 id)
{
	return &player_manager.players[id-1];
}

void player_move(Uint8 *input, Uint8 num, int mousex, int mousey)
{
	Vector3D move = vector3d(input[3] - input[1], input[0] - input[2], 0);
	Vector2D forward;
	float up;
	Player *p = player_get_by_num(num);
	Uint8 xcol = false, ycol = false;

	if (!p->attacking)
	{
		//take mouse x input and use it to rotate the model
		vector3d_normalize(&move);
		p->ent->rottarget += -mousex * 0.01;
		p->ent->rotcurrent += p->ent->rottarget;
		p->ent->rotcurrent = SDL_fmodf(p->ent->rotcurrent, 6.28319);
		//mouse smoothing
		if (p->ent->rottarget != 0)
			p->ent->rottarget *= 0.8;

		p->ent->rotheight += -mousey * 0.025;

		//rotate the forward direction based on current rotation
		forward.x = (move.x * SDL_cosf(p->ent->rotcurrent)) - (move.y * SDL_sinf(p->ent->rotcurrent));
		forward.y = (move.x * SDL_sinf(p->ent->rotcurrent)) + (move.y * SDL_cosf(p->ent->rotcurrent));

		//check if player can jump and adjust their velocity if they can
		if (input[4] && p->ent->grounded)
		{
			p->ent->vel = 1;
			p->ent->accel = 0.035;
			p->ent->grounded = false;
		}

		up = p->ent->vel;
		p->ent->col.position.z += up;

		//check for collisions before height check
		entity_check_col(p->ent);

		//check for ground collisions (landing)
		if (entity_get_col_by_type(p->ent, 2) && up < 0)
		{
			p->ent->col.position.z -= up;
			p->ent->vel = 0;
			p->ent->accel = 0;
			p->ent->grounded = true;
		}
		else if (!entity_get_col_by_type(p->ent, 2))
		{
			p->ent->accel = 0.035;
			p->ent->grounded = false;
		}

		//move collider to new x position
		p->ent->col.position.x -= forward.x * 0.2;

		//Check for a collision
		entity_check_col(p->ent);

		if (entity_get_col_by_type(p->ent, 1))
		{
			xcol = true;
			//revert
			p->ent->col.position.x += forward.x * 0.2;
		}

		//move collider to new y position
		p->ent->col.position.y -= forward.y * 0.2;

		//Check for collision
		entity_check_col(p->ent);

		if (entity_get_col_by_type(p->ent, 1))
		{
			//revert
			ycol = true;
			p->ent->col.position.y += forward.y * 0.2;
		}

		//Commit movements to the player entity if no collision
		if (!xcol)
		{
			p->ent->position.x -= forward.x * 0.2;
		}
		if (!ycol)
		{
			p->ent->position.y -= forward.y * 0.2;
		}

		p->ent->position.z += up;

		player_update_camera(vector3d(p->ent->position.x, p->ent->position.y, p->ent->position.z), vector3d(0, p->ent->rotheight, p->ent->rotcurrent));

		//mouse smoothing
		if (p->ent->rotheight != 0)
			p->ent->rotheight *= 0.8;
	}
	else
	{
		p->ent->accel = 0;
	}

	if (input[7] && p->armed && !p->attacking)
	{
		Vector2D temp;
		temp.x = 0;
		temp.y = 1;
		temp = vector2d_rotate(temp, p->ent->rotcurrent);
		p->forward.x = temp.x;
		p->forward.y = temp.y;
		p->forward.z = gf3d_camera_get_height();

		player_throw_weapon(num);
		p->throwcd = 5;
	}

	if (p->armed)
	{
		player_update_attack(input[6], num);
	}
	else if (p->throwcd <= 0)
	{
		if (collider_rect_rect(&p->ent->col, &p->weapon.ent->col))
		{
			p->weapon.ent->_inuse = false;
			p->armed = true;
		}
	}
	else { p->throwcd--; }
}

void player_update_camera(Vector3D move, Vector3D rotate)
{
	gf3d_camera_update(move, rotate);
}

void player_update_attack(Uint8 input, Uint8 num)
{
	Player *p = player_get_by_num(num);
	Rectcol *temp;
	Vector3D pos, dim;
	Uint8 last_attack;

	/*pos = vector3d(-10, -15, 0);
	vector3d_rotate_about_z(&pos, p->ent->rotcurrent * GFC_RADTODEG);

	pos.x += p->ent->position.x;
	pos.y += p->ent->position.y;
	pos.z += p->ent->position.z;

	collider_new(&p->attack_hits[0], pos, vector3d(p->attack_frame * 0.01, p->attack_frame * 0.01, p->attack_frame * 0.01), Kinematic);

	p->attack_frame++;*/

	if (p->attack == 0)
		last_attack = 1;
	else { last_attack = 0; }

	if (input)
	{
		if (input == 1)
		{
			if (p->attack_frame >= class_get_frames(last_attack) || (p->attack == 0 && p->attack_frame == 0))
			{
				p->attack_frame = 0;
				p->attacking = true;
			}
		}
		else
		{
			if (p->attack_frame >= class_get_frames(last_attack) || (p->attack == 0 && p->attack_frame == 0))
			{
				p->attack = 2;
				p->attack_frame = 0;
				p->attacking = true;
			}
		}
	}

	if (p->attacking)
	{
		if (p->attack_frame < class_get_frames(p->attack))
		{
			temp = class_get_hit(p->attack_frame, p->attack, p->class_type);
			vector3d_copy(pos, temp->position);
			vector3d_copy(dim, temp->dimension);
			if (p->attack_frame <= 2)
			{
				pos.x += dim.x * 0.5;
				pos.y += dim.y * 0.5;
				pos.z += dim.z * 0.5;
				vector3d_rotate_about_z(&pos, p->ent->rotcurrent*GFC_RADTODEG);

				pos.x += p->ent->position.x;
				pos.y += p->ent->position.y;
				pos.z += p->ent->position.z;
				
				collider_new(&p->attack_hits[p->attack_frame], pos, dim, Kinematic);
			}
			else
			{
				p->attack_hits[0] = p->attack_hits[1];
				p->attack_hits[1] = p->attack_hits[2];
				pos.x += dim.x * 0.5;
				pos.y += dim.y * 0.5;
				pos.z += dim.z * 0.5;
				vector3d_rotate_about_z(&pos, p->ent->rotcurrent*GFC_RADTODEG);

				pos.x += p->ent->position.x;
				pos.y += p->ent->position.y;
				pos.z += p->ent->position.z;
				collider_new(&p->attack_hits[2], pos, dim, Kinematic);
			}
			p->attack_frame++;
		}
		else
		{
			p->attack_hits[0]._active = false;
			p->attack_hits[1]._active = false;
			p->attack_hits[2]._active = false;

			if(p->attack == 0)
				p->attack++;
			else { p->attack--; }

			p->attacking = false;
		}
	}
}

void player_draw_attack(Uint32 buffer, VkCommandBuffer command, Uint8 num)
{
	int x = 0;
	Player *p = player_get_by_num(num);

	for (x = 0; x < 3; x++)
	{
		collider_draw(&p->attack_hits[x], buffer, command);
	}
}

void player_throw_weapon(Uint8 num)
{
	Player *p = player_get_by_num(num);

	if (p->attacking)
		return;

	p->armed = false;
	projectile_new(&p->weapon, p->ent->position, p->forward, class_get_throw(p->class_type));
}
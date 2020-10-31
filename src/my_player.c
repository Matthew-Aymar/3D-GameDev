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

	vector3d_normalize(&move);
	p->ent->rottarget = mousex;
	p->ent->rotcurrent += p->ent->rottarget * 0.01;
	p->ent->rotcurrent = SDL_fmodf(p->ent->rotcurrent, 6.28319);

	forward.x = (move.x * SDL_cosf(p->ent->rotcurrent)) - (move.y * SDL_sinf(p->ent->rotcurrent));
	forward.y = (move.x * SDL_sinf(p->ent->rotcurrent)) + (move.y * SDL_cosf(p->ent->rotcurrent));

	if (input[4] && p->ent->grounded)
	{
		p->ent->vel = 10;
		p->ent->accel = 0.05;
		p->ent->grounded = false;
	}

	up = p->ent->vel;
	p->ent->col.position.z += up * 0.01;
	
	entity_check_col(p->ent);
	
	slog("%d|%d|%d|%d|%d|%d", p->ent->collisions[0],
							p->ent->collisions[1],
							p->ent->collisions[2], 
							p->ent->collisions[3], 
							p->ent->collisions[4], 
							p->ent->collisions[5]);

	if (entity_get_col_by_type(p->ent, 2) && up < 0)
	{
		slog("1");
		p->ent->col.position.z -= up * 0.01;
		p->ent->vel = 0;
		p->ent->accel = 0;
		p->ent->grounded = true;
	}

	p->ent->col.position.x -= forward.x * 0.02;
	
	entity_check_col(p->ent);

	if (entity_get_col_by_type(p->ent, 1))
	{
		xcol = true;
		p->ent->col.position.x += forward.x * 0.02;
	}
	
	p->ent->col.position.y -= forward.y * 0.02;
	
	entity_check_col(p->ent);
	
	if (entity_get_col_by_type(p->ent, 1))
	{
		ycol = true;
		p->ent->col.position.y += forward.y * 0.02;
	}

	if (!xcol)
	{
		p->ent->position.x -= forward.x * 0.02;
	}
	if (!ycol)
	{
		p->ent->position.y -= forward.y * 0.02;
	}

	p->ent->position.z += up * 0.01;

	player_update_camera(vector3d(p->ent->position.x, p->ent->position.y, p->ent->position.z), vector3d(0, mousey, p->ent->rotcurrent));

	if (p->ent->vel > -1 * p->ent->velmax)
	{
		p->ent->vel -= p->ent->accel;
	}
	else
	{
		p->ent->vel = -p->ent->velmax;
	}
}

void player_update_camera(Vector3D move, Vector3D rotate)
{
	gf3d_camera_update(move, rotate);
}
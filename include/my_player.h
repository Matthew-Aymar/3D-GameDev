#ifndef __MY_PLAYER_H__
#define __MY_PLAYER_H__

#include "my_entity.h"
#include "gf3d_camera.h"

typedef struct Player_s
{
	Uint8 _playernum;	//0 for uninitialized, count starts at 1 - given to by server
	Entity *ent;
	char *name;			//name of the user
}Player;

void player_manager_init(Uint8 Max);

void player_manager_close();

Player *player_new(Uint8 id);

void player_free(Player *p);

/*
Parameters: Uint8 array holding input values, number id of the player to move
*/
void player_move(Uint8 *input, Uint8 num, int mousex, int mousey);

/*
Parameters: any amount of Uint8 arrays representing player input
Notes: should update all players based on input
*/
void player_move_all(Uint8*, ...);

void player_set_num();

void player_update_camera(Vector3D move, Vector3D rotate);

#endif
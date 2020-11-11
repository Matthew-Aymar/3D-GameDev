#ifndef __MY_PLAYER_H__
#define __MY_PLAYER_H__

#include "my_entity.h"
#include "gf3d_camera.h"
#include "my_class.h"
#include "my_projectile.h"

typedef struct Player_s
{
	Uint8 _playernum;	//0 for uninitialized, count starts at 1 - given to by server
	Entity *ent;
	char *name;			//name of the user
	Uint8 attack;		//Which attack
	Uint8 attack_frame; //Frame of the attack
	Rectcol attack_hits[3];
	Uint8 attacking;	//boolean to check if a attack needs to finish
	Uint8 class_type;   //0 = stinger; 1 = exe; 2 = shin

	Uint8 armed;		//false if the player has thrown their weapon and not picked it up
	Projectile weapon;
	Vector3D forward;
	Uint8 throwcd;		//frames to wait before checking for collision
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

/*
	update the player's attacking state based on the attack and attack frame values
*/
void player_update_attack(Uint8 input, Uint8 num);

/*
	place in game.c to draw colliders for the attack
*/
void player_draw_attack(Uint32 buffer, VkCommandBuffer command, Uint8 num);

void player_throw_weapon(Uint8 num);

#endif
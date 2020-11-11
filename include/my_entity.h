#ifndef __MY_ENTITY_H__
#define __MY_ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf3d_model.h"
#include "my_collider.h"

typedef struct Entity_S
{
	Uint8 _inuse;
	Uint8 _id;

	Vector3D position;
	float rottarget;
	float rotcurrent;
	float rotheight;
	Model *model;
	Matrix4 modelmat;

	Uint8 grounded;
	float vel;		//==========================
	float accel;	//Physics for height changes 
	float velmax;	//==========================

	Uint8 collisions[6]; //collection of current relevant collisions
	
	Rectcol col;

	Uint8 hasthink;
	void (*think)(void *self);
	void *thinktarget;
} Entity;

void entity_manager_init(Uint32 maxEnt);

void entity_manager_close();

Entity *entity_new();

void entity_free(Entity *self);

void entity_draw(Entity *self, Uint32 buffer, VkCommandBuffer command);

void entity_draw_all(Uint32 buffer, VkCommandBuffer command);

void entity_update(Entity *self);

void entity_update_all();

/*
	@brief checks param entity collider with all other entitites
*/
Uint8 entity_check_col(Entity *self);

/*
	@brief returns true if specified collision type is in the collisions
*/
Uint8 entity_get_col_by_type(Entity *self, Uint8 type);

#endif
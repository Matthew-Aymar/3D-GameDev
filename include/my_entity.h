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
	float lasttarget;
	float rotcurrent;
	float rotdist;
	Uint8 distset;
	Model *model;
	Matrix4 modelmat;

	Rectcol col;
} Entity;

void entity_manager_init(Uint32 maxEnt);

void entity_manager_close();

Entity *entity_new();

void entity_free(Entity *self);

void entity_draw(Entity *self, Uint32 buffer, VkCommandBuffer command);

void entity_draw_all(Uint32 buffer, VkCommandBuffer command);

/*
	@brief checks param entity collider with all other entitites
*/
Uint8 entity_check_col(Entity *self);

#endif
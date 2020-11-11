#ifndef __MY_COLLIDER_H__
#define __MY_COLLIDER_H__

#include "gfc_vector.h"
#include "gf3d_model.h"

enum col_types { Ground = 1, Wall = 2, Kinematic = 3, Conv = 4, Jump = 5, Spin = 6, Spik = 7, Tele1 = 8, Tele2= 9};

typedef struct Rectcol_S
{
	Uint8 _active; //false to not be used in collision checks
	Uint8 _drawskip;
	Uint8 type; //Ground, Wall, Kinematic
	Vector3D position;
	Vector3D dimension;
	Model* colmodel;
}Rectcol;

/*
	@breif checks 2 rectangle colliders to check for overlap
	@return 0 on no collision 1 on collision
*/
Uint8 collider_rect_rect(Rectcol *col1, Rectcol *col2);

/*
	@brief initializes a new collider
	@param collider address, position vector, dimension vector
*/
void collider_new(Rectcol *col, Vector3D pos, Vector3D dim, Uint8 type);

void collider_free(Rectcol *col);

void collider_set_draw(Uint8 drawmode);

void collider_draw(Rectcol *rc, Uint32 buffer, VkCommandBuffer command);
#endif
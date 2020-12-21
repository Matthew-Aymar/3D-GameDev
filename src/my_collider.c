#include "my_collider.h"
#include "simple_logger.h"

Uint8 draw;
Model *colmodel;
void collider_set_draw(Uint8 drawmode)
{
	draw = drawmode;
	colmodel = gf3d_model_load("cube");
}

Uint8 collider_rect_rect(Rectcol *col1, Rectcol *col2)
{
	Uint8 xcol = 0, ycol = 0, zcol = 0;
	if (!col1->_active || !col2->_active)
		return 0;

	if ((col1->type != Kinematic && col2->type != Kinematic)) 
	{
		//Nothing will come out of the collision so ignore
		return 0;
	}

	//x check
	if (col2->position.x + col2->dimension.x < col1->position.x ||
		col2->position.x > col1->position.x + col1->dimension.x)
	{
		xcol = 0;
		//no x collision
	}
	else { xcol = 1; }

	//y check
	if (col2->position.y + col2->dimension.y < col1->position.y ||
		col2->position.y > col1->position.y + col1->dimension.y)
	{
		ycol = 0;
		//no y collision
	}
	else { ycol = 1; }

	//z check
	if (col2->position.z + col2->dimension.z < col1->position.z ||
		col2->position.z > col1->position.z + col1->dimension.z)
	{
		zcol = 0;
		//no z collision
	}
	else { zcol = 1; }

	//slog("%d,%d,%d", xcol, ycol, zcol);

	if (xcol && ycol && zcol)
	{
		if (col1->type == Wall || col2->type == Wall)
			return Wall;
		else if (col1->type == Ground || col2->type == Ground)
			return Ground;
		else if (col1->type == Conv || col2->type == Conv)
			return Conv;
		else if (col1->type == Jump || col2->type == Jump)
			return Jump;
		else if (col1->type == Spik || col2->type == Spik)
			return Spik;
		else if (col1->type == Spin || col2->type == Spin)
			return Spin;
		else if (col1->type == Tele1 || col2->type == Tele1)
			return Tele1;
		else if (col1->type == Tele2 || col2->type == Tele2)
			return Tele2;
	}
	else { return 0; }
}

void collider_new(Rectcol *col, Vector3D pos, Vector3D dim, Uint8 type)
{
	col->position = vector3d(pos.x - (dim.x * 0.5),
							 pos.y - (dim.y * 0.5),
							 pos.z - (dim.z * 0.5));
	col->dimension = vector3d(dim.x, dim.y, dim.z);
	col->_active = true;
	col->type = type;

	if (draw)
		col->colmodel = colmodel;
}

void collider_free(Rectcol *col)
{
	if (!col)
	{
		slog("Null pointer in entity_free!");
		return;
	}
	col->_active = 0;
	gf3d_model_free(col->colmodel);
}

void collider_draw(Rectcol *rc, Uint32 buffer, VkCommandBuffer command)
{
	Matrix4 modelmat;
	Vector3D colpos;
	if (!draw)
		return;

	if (rc->_drawskip == true)
		return;
	if (rc->_active == false)
		return;

	if (rc->colmodel == NULL)
		return;

	gfc_matrix_identity(modelmat);

	//the model draw and colliders have different anchor points so they need to be offset
	//to be accurate
	colpos = rc->position;
	colpos.x += rc->dimension.x * 0.5;
	colpos.y += rc->dimension.y * 0.5;
	colpos.z += rc->dimension.z * 0.5;

	gfc_matrix_make_translation(modelmat, colpos);

	modelmat[0][0] *= rc->dimension.x * 0.5;
	modelmat[1][1] *= rc->dimension.y * 0.5;
	modelmat[2][2] *= rc->dimension.z * 0.5;
	modelmat[3][3] *= 1;

	gf3d_model_draw(rc->colmodel, buffer, command, modelmat, rc->colmodel->frameCount);
}
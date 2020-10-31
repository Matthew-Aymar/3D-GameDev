#include "my_collider.h"
#include "simple_logger.h"

Uint8 collider_rect_rect(Rectcol *col1, Rectcol *col2)
{
	Uint8 xcol = 0, ycol = 0, zcol = 0;
	if (!col1->_active || !col2->_active)
		return;
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
		return 1;
	}
	else { return 0; }
}

void collider_new(Rectcol *col, Vector3D pos, Vector3D dim)
{
	col->position = vector3d(pos.x - (dim.x * 0.5),
							 pos.y - (dim.y * 0.5),
							 pos.z - (dim.z * 0.5));
	col->dimension = dim;
	col->_active = true;
}
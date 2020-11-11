#include <stdlib.h>
#include <string.h>

#include "simple_logger.h"

#include "my_entity.h"


typedef struct EntityManager_S
{
	Entity *entity_list;
	Uint32  entity_max;
} EntityManager;

static EntityManager entity_manager = { 0 };

void entity_manager_close()
{
	if (entity_manager.entity_list != NULL)
	{
		free(entity_manager.entity_list);
	}
	memset(&entity_manager, 0, sizeof(EntityManager));
}

void entity_manager_init(Uint32 maxEnt)
{
	entity_manager.entity_max = maxEnt;
	entity_manager.entity_list = (Entity*)gfc_allocate_array(sizeof(Entity), entity_manager.entity_max);
	if (!entity_manager.entity_list)
	{
		slog("Failed to allocate entity list");
		return;
	}
	atexit(entity_manager_close);
}

Entity *entity_new()
{
	int i = 0;
	for (i = 0; i < entity_manager.entity_max; i++)
	{
		if (entity_manager.entity_list[i]._inuse != NULL)
		{
			continue;
		}
		else
		{
			memset(&entity_manager.entity_list[i], 0, sizeof(Entity));
			entity_manager.entity_list[i]._inuse = 1;
			gfc_matrix_identity(entity_manager.entity_list[i].modelmat);
			entity_manager.entity_list[i]._id = i;
			entity_manager.entity_list[i].velmax = 10;
			entity_manager.entity_list[i].grounded = true;
			return &entity_manager.entity_list[i];
		}
	}
	slog("No empty space in entity array");
	return NULL;
}

void entity_free(Entity *self)
{
	if (!self)
	{
		slog("Null pointer in entity_free!");
		return;
	}
	self->_inuse = 0;
	gf3d_model_free(self->model);
}

void entity_draw(Entity *self, Uint32 buffer, VkCommandBuffer command)
{
	if (self->model != NULL)
	{
		gf3d_model_draw(self->model, buffer, command, self->modelmat);
	}
	if (self->col.colmodel != NULL)
	{
		collider_draw(&self->col, buffer, command);
	}
}

void entity_draw_all(Uint32 buffer, VkCommandBuffer command)
{
	int i = 0;
	for (i = 0; i < entity_manager.entity_max; i++)
	{
		if (entity_manager.entity_list[i]._inuse == true)
		{
			entity_draw(&entity_manager.entity_list[i], buffer, command);
		}
	}
}

void entity_update(Entity *self)
{
	if (self->hasthink)
	{
		if (self->thinktarget != NULL)
			self->think(self->thinktarget);
		else { self->think(self); }
	}

	if (self->vel > -1 * self->velmax)
	{
		self->vel -= self->accel;
	}
	else
	{
		self->vel = self->velmax;
	}

	gfc_matrix_make_translation(self->modelmat, self->position);

	self->col.position.x = self->position.x - (self->col.dimension.x * 0.5);
	self->col.position.y = self->position.y - (self->col.dimension.y * 0.5);
	self->col.position.z = self->position.z - (self->col.dimension.z * 0.5);

	gfc_matrix_rotate(
		self->modelmat,
		self->modelmat,
		self->rotcurrent,
		vector3d(0, 0, 1));
}

void entity_update_all()
{
	int i = 0;
	for (i = 0; i < entity_manager.entity_max; i++)
	{
		if (entity_manager.entity_list[i]._inuse == true)
		{
			entity_update(&entity_manager.entity_list[i]);
		}
	}
}

Uint8 entity_check_col(Entity *self)
{
	int i = 0;
	int x = 0;
	Uint8 col;
	for (x = 0; x < 6; x++)
	{
		self->collisions[x] = 0;
	}

	for (i = 0; i < entity_manager.entity_max; i++)
	{
		if (entity_manager.entity_list[i]._inuse == true)
		{
			if (entity_manager.entity_list[i]._id != self->_id)
			{
				col = collider_rect_rect(&self->col, &entity_manager.entity_list[i].col);
				if (col != 0)
				{
					for (x = 0; x < 6; x++)
					{
						if (self->collisions[x] == 0)
						{
							self->collisions[x] = col;
							break;
						}
					}
				}
			}
		}
	}
	return 0;
}

Uint8 entity_get_col_by_type(Entity *self, Uint8 type)
{
	int x = 0;
	for (x = 0; x < 6; x++)
	{
		if (self->collisions[x] == type)
		{
			return true;
		}
	}
	return false;
}
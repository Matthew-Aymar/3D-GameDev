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
	gfc_matrix_make_translation(self->modelmat, self->position);

	self->col.position.x = self->position.x;
	self->col.position.y = self->position.y;
	self->col.position.z = self->position.z;

	gfc_matrix_rotate(
		self->modelmat,
		self->modelmat,
		self->rotcurrent,
		vector3d(0, 0, 1));

	gf3d_model_draw(self->model, buffer, command, self->modelmat);
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

void entity_check_col(Entity *self)
{
	int i = 0;
	for (i = 0; i < entity_manager.entity_max; i++)
	{
		if (entity_manager.entity_list[i]._inuse == true)
		{
		}
	}
}
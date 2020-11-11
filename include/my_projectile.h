#ifndef __MY_PROJECTILE_H__
#define __MY_PROJECTILE_H__

#include "my_entity.h"

typedef struct Projectile_S
{
	Entity *ent;
	Vector3D launch_dir;
	float speed;
}Projectile;

void projectile_new(Projectile *p, Vector3D pos, Vector3D dir, float speed);

void projectile_update(Entity *self);

#endif
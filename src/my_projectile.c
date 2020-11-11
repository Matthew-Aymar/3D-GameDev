#include "my_projectile.h"
#include "simple_logger.h"

void projectile_new(Projectile *p, Vector3D pos, Vector3D dir, float speed)
{
	p->ent = entity_new();
	p->ent->think = *projectile_update;
	p->ent->hasthink = true;
	p->ent->thinktarget = p;
	p->ent->accel = 0.035;
	p->ent->vel = -(((dir.z - 10) * 0.05)) + speed / 5;
	p->ent->position = pos;
	p->launch_dir = dir;
	p->speed = speed;
	collider_new(&p->ent->col, p->ent->position, vector3d(2, 2, 2), Kinematic);
}

void projectile_update(void *self)
{
	Projectile *p = (Projectile*)self;

	p->ent->col.position.x -= p->launch_dir.x * p->speed;
	p->ent->col.position.y -= p->launch_dir.y * p->speed;
	p->ent->col.position.z -= p->ent->vel;

	entity_check_col(p->ent);

	if (entity_get_col_by_type(p->ent, 2) || entity_get_col_by_type(p->ent, 1))
	{
		p->ent->col.position.x += p->launch_dir.x * p->speed;
		p->ent->col.position.y += p->launch_dir.y * p->speed;
		p->ent->accel = 0;
		p->ent->hasthink = false;
	}
	else
	{
		p->ent->position.x -= p->launch_dir.x * p->speed;
		p->ent->position.y -= p->launch_dir.y * p->speed;
		p->ent->position.z += p->ent->vel;
	}
}
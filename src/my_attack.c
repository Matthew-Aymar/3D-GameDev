#include "my_attack.h"
#include "simple_logger.h"

Attack stinger_l1;
Attack stinger_l2;
Attack stinger_h;
Moveset stinger;

Attack exe_l1;
Attack exe_l2;
Attack exe_h;
Moveset exe;

Attack shin_l1;
Attack shin_l2;
Attack shin_h;
Moveset shin;

void attack_init()
{
	int x = 0;
	stinger_l1.damage = 15;
	stinger_l1.speed = 1;
	stinger_l1.frames = 15;
	stinger_l1.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), stinger_l1.frames);

	collider_new(&stinger_l1.hits[0], vector3d(1.2, -5, -7), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[1], vector3d(1, -5.5, -6), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[2], vector3d(0.8, -6, -5), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[3], vector3d(0.6, -6.5, -4), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[4], vector3d(0.4, -7, -3), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[5], vector3d(0.2, -7.5, -2), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[6], vector3d(0, -8, -1), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[7], vector3d(-0.2, -8.5, 0), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[8], vector3d(-0.4, -8, 1), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[9], vector3d(-0.6, -7.5, 2), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[10], vector3d(-0.8, -7, 3), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[11], vector3d(-1, -6.5, 4), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[12], vector3d(-1.2, -6, 5), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[13], vector3d(-1.3, -5.5, 6), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l1.hits[14], vector3d(-1.5, -5, 7), vector3d(2, 2, 2), Kinematic);

	stinger_l2.damage = 15;
	stinger_l2.speed = 1;
	stinger_l2.frames = 15;
	stinger_l2.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), stinger_l2.frames);

	collider_new(&stinger_l2.hits[0], vector3d(1.2, -5, 7), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[1], vector3d(1, -5.5, 6), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[2], vector3d(0.8, -6, 5), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[3], vector3d(0.6, -6.5, 4), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[4], vector3d(0.4, -7, 3), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[5], vector3d(0.2, -7.5, 2), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[6], vector3d(0, -8, 1), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[7], vector3d(-0.2, -8.5, 0), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[8], vector3d(-0.4, -8, -1), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[9], vector3d(-0.6, -7.5, -2), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[10], vector3d(-0.8, -7, -3), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[11], vector3d(-1, -6.5, -4), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[12], vector3d(-1.2, -6, -5), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[13], vector3d(-1.3, -5.5, -6), vector3d(2, 2, 2), Kinematic);
	collider_new(&stinger_l2.hits[14], vector3d(-1.5, -5, -7), vector3d(2, 2, 2), Kinematic);

	stinger_h.speed = 0.5;
	stinger_h.frames = 5;
	stinger_h.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), stinger_h.frames);

	stinger.light1 = &stinger_l1;
	stinger.light2 = &stinger_l2;
	stinger.heavy = &stinger_h;

	exe_l1.damage = 10;
	exe_l1.speed = 1;
	exe_l1.frames = 15;
	exe_l1.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), exe_l1.frames);

	collider_new(&exe_l1.hits[0], vector3d(10, -5, -0.5), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[1], vector3d(8, -6, -0.4), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[2], vector3d(6, -7, -0.3), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[3], vector3d(4, -8, -0.2), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[4], vector3d(2, -9, -0.1), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[5], vector3d(0, -10, 0), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[6], vector3d(-1, -10.25, 0.1), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[7], vector3d(-2, -10.5, 0.2), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[8], vector3d(-3, -10.25, 0.3), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[9], vector3d(-4, -10, 0.4), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[10], vector3d(-5, -9, 0.5), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[11], vector3d(-6, -8, 0.6), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[12], vector3d(-7, -7, 0.55), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[13], vector3d(-8, -7, 0.5), vector3d(3, 3, 2), Kinematic);
	collider_new(&exe_l1.hits[14], vector3d(-9, -5, 0.45), vector3d(3, 3, 2), Kinematic);

	exe_l2.damage = 40;
	exe_l2.speed = 1;
	exe_l2.frames = 15;
	exe_l2.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), exe_l2.frames);

	collider_new(&exe_l2.hits[0], vector3d(1, -5, 9), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[1], vector3d(0.9, -6, 9.5), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[2], vector3d(0.8, -7, 9.75), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[3], vector3d(0.7, -8, 10), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[4], vector3d(0.6, -8.25, 9), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[5], vector3d(0.5, -8.5, 8), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[6], vector3d(0.4, -8.75, 6.5), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[7], vector3d(0.3, -9, 5), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[8], vector3d(0.2, -10, 3), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[9], vector3d(0.1, -10, 1), vector3d(2, 2, 3), Kinematic);
	collider_new(&exe_l2.hits[10], vector3d(0, -10, -1), vector3d(2, 2, 2), Kinematic);
	collider_new(&exe_l2.hits[11], vector3d(-0.1, -10, -4), vector3d(5, 5, 5), Kinematic);
	collider_new(&exe_l2.hits[12], vector3d(-0.2, -10, -4), vector3d(6, 6, 6), Kinematic);
	collider_new(&exe_l2.hits[13], vector3d(-0.3, -10, -4), vector3d(10, 10, 4), Kinematic);
	collider_new(&exe_l2.hits[14], vector3d(-0.4, -10, -4), vector3d(2, 2, 2), Kinematic);

	exe_h.speed = 0.5;
	exe_h.frames = 5;
	exe_h.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), exe_h.frames);

	exe.light1 = &exe_l1;
	exe.light2 = &exe_l2;
	exe.heavy = &exe_h;

	shin_l1.damage = 30;
	shin_l1.speed = 1;
	shin_l1.frames = 15;
	shin_l1.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), shin_l1.frames);

	collider_new(&shin_l1.hits[0], vector3d(0, 0, 0), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[1], vector3d(0, -2, 0), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[2], vector3d(0, -4, 0), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[3], vector3d(0, -6, 0), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[4], vector3d(0, -8, 0), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[5], vector3d(-2, 0, 2), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[6], vector3d(-2, -2, 2), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[7], vector3d(-2, -4, 2), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[8], vector3d(-2, -6, 2), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[9], vector3d(-2, -8, 2), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[10], vector3d(-3.5, 0, -1), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[11], vector3d(-3.5, -2, -1), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[12], vector3d(-3.5, -4, -1), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[13], vector3d(-3.5, -6, -1), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l1.hits[14], vector3d(-3.5, -8, -1), vector3d(1.5, 1.5, 1.5), Kinematic);

	shin_l2.damage = 10;
	shin_l2.speed = 1;
	shin_l2.frames = 15;
	shin_l2.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), shin_l2.frames);

	collider_new(&shin_l2.hits[0], vector3d(0, 0, 0), vector3d(3, 3, 3), Kinematic);
	collider_new(&shin_l2.hits[1], vector3d(0, -2, 0), vector3d(3, 3, 3), Kinematic);
	collider_new(&shin_l2.hits[2], vector3d(0, -4, 0), vector3d(3, 3, 3), Kinematic);
	collider_new(&shin_l2.hits[3], vector3d(0, -6, 0), vector3d(2.5, 2.5, 2.5), Kinematic);
	collider_new(&shin_l2.hits[4], vector3d(0, -8, 0), vector3d(2.5, 2.5, 2.5), Kinematic);
	collider_new(&shin_l2.hits[5], vector3d(0, -10, 0), vector3d(2.5, 2.5, 2.5), Kinematic);
	collider_new(&shin_l2.hits[6], vector3d(0, -11, 0), vector3d(2, 2, 2), Kinematic);
	collider_new(&shin_l2.hits[7], vector3d(0, -12, 0), vector3d(2, 2, 2), Kinematic);
	collider_new(&shin_l2.hits[8], vector3d(0, -13, 0), vector3d(2, 2, 2), Kinematic);
	collider_new(&shin_l2.hits[9], vector3d(0, -14, 0), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l2.hits[10], vector3d(0, -15, 0), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l2.hits[11], vector3d(0, -16, 0), vector3d(1.5, 1.5, 1.5), Kinematic);
	collider_new(&shin_l2.hits[12], vector3d(0, -17, 0), vector3d(1, 1, 1), Kinematic);
	collider_new(&shin_l2.hits[13], vector3d(0, -18, 0), vector3d(1, 1, 1), Kinematic);
	collider_new(&shin_l2.hits[14], vector3d(0, -19, 0), vector3d(1, 1, 1), Kinematic);

	shin_h.speed = 0.5;
	shin_h.frames = 5;
	shin_h.hits = (Rectcol*)gfc_allocate_array(sizeof(Rectcol), shin_h.frames);

	shin.light1 = &shin_l1;
	shin.light2 = &shin_l2;
	shin.heavy = &shin_h;
}

Moveset *attack_get_moveset(Uint8 type)
{
	if (type == 0)
		return &stinger;
	else if (type == 1)
		return &exe;
	else if (type == 2)
		return &shin;
}
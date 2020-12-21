#ifndef __MY_BUTTON_H__
#define __MY_BUTTON_H__

#include "gf3d_texture.h"
#include "gf3d_sprite.h"

typedef struct Button_S
{
	Vector2D position;
	Vector2D size;
	Sprite *sprite;
} Button;

/*
Creates a button using a sprite and position
position is edited so the button is centered at position
*/
void button_new(Button *b, Sprite *s, Vector2D position);

/*
Checks if the mouse is within bounds of the button
*/
Uint8 button_check(Button *b, Vector2D mouse);

#endif
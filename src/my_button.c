#include "my_button.h"
#include "simple_logger.h"
void button_new(Button *b, Sprite *s, Vector2D position)
{
	b->sprite = s;
	
	b->position.x = position.x - (s->texture->width * 0.25);
	b->position.y = position.y - (s->texture->height * 0.25);

	b->size.x = s->texture->width;
	b->size.y = s->texture->height;
}

Uint8 button_check(Button *b, Vector2D mouse)
{
	if (mouse.x < b->position.x ||
		mouse.x > b->position.x + b->size.x * 0.5||
		mouse.y < b->position.y ||
		mouse.y > b->position.y + b->size.y * 0.5)
	{
		return false;
	}
	else
	{
		return true;
	}
}
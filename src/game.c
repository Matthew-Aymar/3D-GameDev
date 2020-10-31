#include <SDL.h>            

#include "my_entity.h"
#include "my_player.h"

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"

int main(int argc, char *argv[])
{
	int done = 0;
	int a;
	Uint8 validate = 0;
	const Uint8 * keys;
	Uint32 bufferFrame = 0;
	VkCommandBuffer commandBuffer;

	enum input_names { up = 0, left = 1, down = 2, right = 3, jump = 4, ability = 5, attack = 6, toss = 7 };

	Uint8 input_max = 8;
	Uint8 *inputs = (Uint8*)malloc(sizeof(Uint8) * input_max);
	
	int mousex, mousey;

	Entity *ent1, *ent2;

	Player *p;

	SDL_Window *w;

	for (a = 1; a < argc; a++)
	{
		if (strcmp(argv[a], "-disable_validate") == 0)
		{
			validate = 0;
		}
	}

	init_logger("gf3d.log");
	slog("gf3d begin");
	gf3d_vgraphics_init(
		"gf3d",                 //program name
		1200,                   //screen width
		700,                    //screen height
		vector4d(0.51, 0.75, 1, 1),//background color
		0,                      //fullscreen
		validate                //validation
		);
	entity_manager_init(256);
	player_manager_init(16);
	slog_sync();
	
	ent1 = entity_new();
	ent2 = entity_new();

	p = player_new(1);
	p->ent->model = gf3d_model_load("dino");

	ent1->model = gf3d_model_load("cube");
	ent2->model = gf3d_model_load("cube");

	ent1->position = vector3d(10, 10, 0);
	ent2->position = vector3d(0, 0, 0);
	// main game loop
	slog("gf3d main loop begin");
	slog_sync();

	SDL_SetRelativeMouseMode(1);
	w = SDL_GetWindowFromID(1);
	SDL_SetWindowGrab(w, 1);

	gf3d_camera_set(gf3d_vgraphics_get_uniform_buffer_object().view);

	collider_new(&ent1->col, vector3d(10, 10, 0), vector3d(1, 1, 1));
	collider_new(&p->ent->col, vector3d(0, 0, 0), vector3d(5, 5, 5));

	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		SDL_GetRelativeMouseState(&mousex, &mousey);
		
		//update game things here

		if (keys[SDL_SCANCODE_W] == true)
		{
			inputs[up] = true;
		}
		else { inputs[up] = false; }

		if (keys[SDL_SCANCODE_A] == true)
		{
			inputs[left] = true;
		}
		else { inputs[left] = false; }

		if (keys[SDL_SCANCODE_S] == true)
		{
			inputs[down] = true;
		}
		else { inputs[down] = false; }

		if (keys[SDL_SCANCODE_D] == true)
		{
			inputs[right] = true;
		}
		else { inputs[right] = false; }

		if (keys[SDL_SCANCODE_SPACE] == true)
		{
			inputs[jump] = true;
		}
		else { inputs[jump] = false; }

		if (keys[SDL_SCANCODE_E] == true)
		{
			inputs[ability] = true;
		}
		else { inputs[ability] = false; }

		player_move(inputs, p->_playernum, mousex, mousey);

		// configure render command for graphics command pool
		// for each mesh, get a command and configure it from the pool
		bufferFrame = gf3d_vgraphics_render_begin();
		gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(), bufferFrame);
		commandBuffer = gf3d_command_rendering_begin(bufferFrame);

		entity_draw_all(bufferFrame, commandBuffer);

		gf3d_command_rendering_end(commandBuffer);

		gf3d_vgraphics_render_end(bufferFrame);

		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
	}

	vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());
	//cleanup
	slog("gf3d program end");
	slog_sync();
	return 0;
}

/*eol@eof*/
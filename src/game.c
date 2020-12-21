#include <SDL.h>            
#include <enet.h>

#include "my_entity.h"
#include "my_player.h"
#include "my_multiplayer.h"
#include "my_button.h"
#include "my_attack.h"
#include "my_bot.h"
#include "my_item.h"
#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"

#include "gfc_audio.h"

void ground_set(Entity *ground_cols[22])
{
	//Base
	ground_cols[0] = entity_new();
	ground_cols[0]->position = vector3d(0, 0, -7.5);
	collider_new(&ground_cols[0]->col, vector3d(0, 0, 0), vector3d(100, 100, 0), Ground);

	//Raised floors
	ground_cols[1] = entity_new();
	ground_cols[1]->position = vector3d(68.75, 25, -1.25);
	collider_new(&ground_cols[1]->col, vector3d(0, 0, 0), vector3d(37.5, 75, 0), Ground);

	ground_cols[2] = entity_new();
	ground_cols[2]->position = vector3d(25, 68.75, -1.25);
	collider_new(&ground_cols[2]->col, vector3d(0, 0, 0), vector3d(75, 37.5, 0), Ground);

	ground_cols[3] = entity_new();
	ground_cols[3]->position = vector3d(-68.75, -25, -1.25);
	collider_new(&ground_cols[3]->col, vector3d(0, 0, 0), vector3d(37.5, 75, 0), Ground);

	ground_cols[4] = entity_new();
	ground_cols[4]->position = vector3d(-25, -68.75, -1.25);
	collider_new(&ground_cols[4]->col, vector3d(0, 0, 0), vector3d(75, 37.5, 0), Ground);

	//Center Blocks
	ground_cols[5] = entity_new();
	ground_cols[5]->position = vector3d(25, 50, 7.5);
	collider_new(&ground_cols[5]->col, vector3d(0, 0, 0), vector3d(25, 25, 30), Wall);

	ground_cols[6] = entity_new();
	ground_cols[6]->position = vector3d(50, 25, 7.5);
	collider_new(&ground_cols[6]->col, vector3d(0, 0, 0), vector3d(25, 25, 30), Wall);

	ground_cols[7] = entity_new();
	ground_cols[7]->position = vector3d(-25, -50, 7.5);
	collider_new(&ground_cols[7]->col, vector3d(0, 0, 0), vector3d(25, 25, 30), Wall);

	ground_cols[8] = entity_new();
	ground_cols[8]->position = vector3d(-50, -25, 7.5);
	collider_new(&ground_cols[8]->col, vector3d(0, 0, 0), vector3d(25, 25, 30), Wall);

	//Empty Corners
	ground_cols[9] = entity_new();
	ground_cols[9]->position = vector3d(-25, 62.5, 20.5);
	collider_new(&ground_cols[9]->col, vector3d(0, 0, 0), vector3d(25, 50, 56), Wall);

	ground_cols[10] = entity_new();
	ground_cols[10]->position = vector3d(-62.5, 25, 20.5);
	collider_new(&ground_cols[10]->col, vector3d(0, 0, 0), vector3d(50, 25, 56), Wall);

	ground_cols[11] = entity_new();
	ground_cols[11]->position = vector3d(25, -62.5, 20.5);
	collider_new(&ground_cols[11]->col, vector3d(0, 0, 0), vector3d(25, 50, 56), Wall);

	ground_cols[12] = entity_new();
	ground_cols[12]->position = vector3d(62.5, -25, 20.5);
	collider_new(&ground_cols[12]->col, vector3d(0, 0, 0), vector3d(50, 25, 56), Wall);

	//Raised Floor Walls
	ground_cols[13] = entity_new();
	ground_cols[13]->position = vector3d(68.75, 25, -8);
	collider_new(&ground_cols[13]->col, vector3d(0, 0, 0), vector3d(37.5, 75, 10), Wall);

	ground_cols[14] = entity_new();
	ground_cols[14]->position = vector3d(25, 68.75, -8);
	collider_new(&ground_cols[14]->col, vector3d(0, 0, 0), vector3d(75, 37.5, 10), Wall);

	ground_cols[15] = entity_new();
	ground_cols[15]->position = vector3d(-68.75, -25, -8);
	collider_new(&ground_cols[15]->col, vector3d(0, 0, 0), vector3d(37.5, 75, 10), Wall);

	ground_cols[16] = entity_new();
	ground_cols[16]->position = vector3d(-25, -68.75, -8);
	collider_new(&ground_cols[16]->col, vector3d(0, 0, 0), vector3d(75, 37.5, 10), Wall);

	//Far Walls
	ground_cols[13] = entity_new();
	ground_cols[13]->position = vector3d(106.25, 25, 20.5);
	collider_new(&ground_cols[13]->col, vector3d(0, 0, 0), vector3d(37.5, 75, 56), Wall);

	ground_cols[14] = entity_new();
	ground_cols[14]->position = vector3d(25, 106.25, 20.5);
	collider_new(&ground_cols[14]->col, vector3d(0, 0, 0), vector3d(75, 37.5, 56), Wall);

	ground_cols[15] = entity_new();
	ground_cols[15]->position = vector3d(-106.25, -25, 20.5);
	collider_new(&ground_cols[15]->col, vector3d(0, 0, 0), vector3d(37.5, 75, 56), Wall);

	ground_cols[16] = entity_new();
	ground_cols[16]->position = vector3d(-25, -106.25, 20.5);
	collider_new(&ground_cols[16]->col, vector3d(0, 0, 0), vector3d(75, 37.5, 56), Wall);

	//Far Corners
	ground_cols[17] = entity_new();
	ground_cols[17]->position = vector3d(-75, -75, 20.5);
	collider_new(&ground_cols[17]->col, vector3d(0, 0, 0), vector3d(25, 25, 56), Wall);

	ground_cols[18] = entity_new();
	ground_cols[18]->position = vector3d(75, 75, 20.5);
	collider_new(&ground_cols[18]->col, vector3d(0, 0, 0), vector3d(25, 25, 56), Wall);
	
	//Platforms
}

void interactable_set(Entity *i_conv, Entity *i_jump, Entity *i_spik, Entity *i_spin, Entity *i_tele1, Entity *i_tele2)
{
	Vector3D scale;
	Player *p = player_get_by_num(1);

	i_conv = entity_new();
	i_jump = entity_new();
	i_spik = entity_new();
	i_spin = entity_new();
	i_tele1 = entity_new();
	i_tele2 = entity_new();

	i_conv->model = gf3d_model_load("Conv");
	i_jump->model = gf3d_model_load("Jump");
	i_spik->model = gf3d_model_load("Spik");
	i_spin->model = gf3d_model_load("Spin");
	i_tele1->model = gf3d_model_load("Tele");
	i_tele2->model = gf3d_model_load("Tele");

	scale = vector3d(0.5, 0.5, 0.5);

	i_conv->position = vector3d(0, 15, -8);
	i_jump->position = vector3d(0, -15, -8);
	i_spik->position = vector3d(15, 0, -8);
	i_spin->position = vector3d(-15, 0, -8);
	i_tele1->position = vector3d(30, 0, -8);
	i_tele2->position = vector3d(-30, 0, -8);

	gfc_matrix_make_translation(i_conv->modelmat, i_conv->position);
	gfc_matrix_make_translation(i_jump->modelmat, i_jump->position);
	gfc_matrix_make_translation(i_spik->modelmat, i_spik->position);
	gfc_matrix_make_translation(i_spin->modelmat, i_spin->position);
	gfc_matrix_make_translation(i_tele1->modelmat, i_tele1->position);
	gfc_matrix_make_translation(i_tele2->modelmat, i_tele2->position);

	entity_scale_modelmat(i_conv, scale);
	entity_scale_modelmat(i_jump, scale);
	entity_scale_modelmat(i_spik, scale);
	entity_scale_modelmat(i_spin, scale);
	entity_scale_modelmat(i_tele1, scale);
	entity_scale_modelmat(i_tele2, scale);

	i_conv->_noupdate = true;
	i_jump->_noupdate = true;
	i_spik->_noupdate = true;
	i_spin->_noupdate = true;
	i_tele1->_noupdate = true;
	i_tele2->_noupdate = true;

	collider_new(&i_conv->col, i_conv->position, vector3d(10, 10, 4), Conv);
	collider_new(&i_jump->col, i_jump->position, vector3d(10, 10, 4), Jump);
	collider_new(&i_spik->col, i_spik->position, vector3d(10, 10, 4), Spik);
	collider_new(&i_spin->col, i_spin->position, vector3d(10, 10, 4), Spin);
	collider_new(&i_tele1->col, i_tele1->position, vector3d(10, 10, 4), Tele1);
	collider_new(&i_tele2->col, i_tele2->position, vector3d(10, 10, 4), Tele2);

	i_conv->col._drawskip = true;
	i_jump->col._drawskip = true;
	i_spik->col._drawskip = true;
	i_spin->col._drawskip = true;
	i_tele1->col._drawskip = true;
	i_tele2->col._drawskip = true;

	p->t1 = i_tele1->position;
	p->t1.z += 5;
	p->t2 = i_tele2->position;
	p->t2.z += 5;
}

int main(int argc, char *argv[])
{
	int done = 0;
	int a;
	Uint8 validate = 0;
	const Uint8 * keys;
	Uint32 bufferFrame = 0;
	VkCommandBuffer commandBuffer;

	Uint32 ms_per_tick = 7;
	Uint32 current_ms = 7;   //time(0) - last_tick
	Uint32 last_tick = 0;

	float frames;
	Uint32 last_second;

	enum input_names { up = 0, left = 1, down = 2, right = 3, jump = 4, ability = 5, attack = 6, toss = 7 };

	Uint8 input_max = 8;
	Uint8 *inputs = (Uint8*)malloc(sizeof(Uint8) * input_max);
	
	int mousex, mousey;

	Entity *ground;

	Entity *i_conv, *i_jump, *i_spik, *i_spin, *i_tele1, *i_tele2;

	Entity *temp_player;

	Player *p;

	SDL_Window *w;

	Entity *ground_cols[22];

	Uint8 enetinit = true;
	Uint8 isserver = true;
	Uint8 connected = false;

	ENetHost* hostptr = NULL;
	ENetHost** host = &hostptr;
	ENetAddress addr;
	ENetAddress* address = &addr;
	ENetEvent eventval;
	ENetEvent* event = &eventval;
	ENetPeer* peerptr = NULL;
	ENetPeer** peer = &peerptr;
	ENetPacket* pack = NULL;
	ENetPacket* recieved = NULL;

	Vector3D sendpos = vector3d(0, 0, 0);
	const Vector3D* send = &sendpos;
	Vector3D recievepos = vector3d(0, 0, 0);
	const Vector3D* recieve = &recievepos;

	Sprite *hud, *stam, *start, *edit, *exit, *menubg, *cursor;
	Button start_button, edit_button, exit_button;
	float bgframe = 0;

	Uint8 menu = false;
	Uint8 mainmenu = true;
	//editor stuff
	Uint8 editor = false;

	Entity *cube;

	Sprite *arrow_inc_1, *arrow_inc_2, *arrow_inc_3, *arrow_inc_4, *arrow_inc_5, *arrow_inc_6;
	Sprite *arrow_dec_1, *arrow_dec_2, *arrow_dec_3, *arrow_dec_4, *arrow_dec_5, *arrow_dec_6;
	Button pos_x_button_inc, pos_y_button_inc, pos_z_button_inc;
	Button pos_x_button_dec, pos_y_button_dec, pos_z_button_dec;
	Button size_x_button_inc, size_y_button_inc, size_z_button_inc;
	Button size_x_button_dec, size_y_button_dec, size_z_button_dec;

	Bot bot;

	Item item;

	Sound *bgtrack;

	FILE *cfg;
	const char cfgcontents[60];
	const char ipaddr[12];
	const char portstr[6];
	const char serverbool[1];
	int portint;
	int x = 0;
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
	attack_init();
	class_init();
	enetinit = multiplayer_init();
	gfc_audio_init(16, 4, 0, 8, 0, 0);

	slog_sync();
	
	collider_set_draw(true);

	ground = entity_new();

	ground_set(ground_cols);

	interactable_set(i_conv, i_jump, i_spik, i_spin, i_tele1, i_tele2);

	ground->model = gf3d_model_load("Map");

	ground->position = vector3d(0, 0, -10);

	cube = entity_new();
	cube->model = gf3d_model_load("cube2");

	item_new(&item, 0);

	start = gf3d_sprite_load("images/start.png", -1, -1, 0);
	edit = gf3d_sprite_load("images/edit.png", -1, -1, 0);
	exit = gf3d_sprite_load("images/exit.png", -1, -1, 0);
	menubg = gf3d_sprite_load("images/bg.png", 2400, 1400, 14);
	cursor = gf3d_sprite_load("images/cursor.png", -1, -1, 0);

	button_new(&start_button, start, vector2d(600, 400));
	button_new(&edit_button, edit, vector2d(600, 500));
	button_new(&exit_button, exit, vector2d(600, 600));

	cfg = fopen("config.txt", "r");
	if (cfg)
	{
		fgets(&cfgcontents, 60, cfg);
		strcpy(&ipaddr, &cfgcontents);
		fgets(&cfgcontents, 60, cfg);
		strcpy(&portstr, &cfgcontents);
		portint = atoi(&portstr);
		fgets(&cfgcontents, 60, cfg);
		strcpy(&serverbool, &cfgcontents);
		isserver = atoi(&serverbool);
		fclose(cfg);
	}
	else
	{
		connected = false;
		enetinit = false;
		slog("no enet config file!");
	}

	// main game loop
	slog("gf3d main loop begin");
	
	slog_sync();

	SDL_SetRelativeMouseMode(1);
	w = SDL_GetWindowFromID(1);
	SDL_SetWindowGrab(w, 1);

	gf3d_camera_set(gf3d_vgraphics_get_uniform_buffer_object().view);

	bgtrack = gfc_sound_load("sounds/Zone.wav", 0.02, -1);
	//gfc_sound_play(bgtrack, 100, 0.02, -1, -1);

	while (!done)
	{
		if (mainmenu)
		{
			SDL_PumpEvents();
			SDL_GetMouseState(&mousex, &mousey);
			keys = SDL_GetKeyboardState(NULL);

			bufferFrame = gf3d_vgraphics_render_begin();
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_overlay_pipeline(), bufferFrame);

			commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_overlay_pipeline());
			
			gf3d_sprite_draw(menubg, vector2d(0, 0), vector2d(1, 1), bgframe, bufferFrame, commandBuffer);
			gf3d_sprite_draw(start_button.sprite, vector2d(start_button.position.x, start_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
			gf3d_sprite_draw(edit_button.sprite, vector2d(edit_button.position.x, edit_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
			gf3d_sprite_draw(exit_button.sprite, vector2d(exit_button.position.x, exit_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
			gf3d_sprite_draw(cursor, vector2d(mousex - (cursor->texture->width * 0.25), mousey - (cursor->texture->height * 0.25)), vector2d(1, 1), 0, bufferFrame, commandBuffer);

			if (button_check(&start_button, vector2d(mousex, mousey)))
			{
				if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
				{
					//ENET
					if (enetinit)
					{
						if (!isserver)
						{
							//CLIENT SETUP
							connected = multiplayer_client_create(address, host, peer, event, portint, &ipaddr);
						}
						else
						{
							//SERVER SETUP
							connected = multiplayer_server_create(address, host, portint);
						}
					}
					//ENET
					hud = gf3d_sprite_load("images/hud.png", 960, 120, 10);
					stam = gf3d_sprite_load("images/hud_stam.png", 480, 60, 10);

					p = player_new(1);
					p->ent->model = gf3d_model_load("dino");

					collider_new(&p->ent->col, vector3d(0, 0, 0), vector3d(5, 5, 10), Kinematic);

					bot_new(&bot, p);
					bot.ent->model = gf3d_model_load("dino");

					mainmenu = false;
				}
			}
			else if (button_check(&edit_button, vector2d(mousex, mousey)))
			{
				if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
				{
					editor = true;
					mainmenu = false;

					arrow_inc_1 = gf3d_sprite_load("images/arrow.png", -1, -1, 0);
					arrow_inc_2 = gf3d_sprite_load("images/arrow.png", -1, -1, 0);
					arrow_inc_3 = gf3d_sprite_load("images/arrow.png", -1, -1, 0);
				
					arrow_dec_1 = gf3d_sprite_load("images/arrow2.png", -1, -1, 0);
					arrow_dec_2 = gf3d_sprite_load("images/arrow2.png", -1, -1, 0);
					arrow_dec_3 = gf3d_sprite_load("images/arrow2.png", -1, -1, 0);

					button_new(&pos_x_button_inc, arrow_inc_1, vector2d(1100, 500));
					button_new(&pos_y_button_inc, arrow_inc_2, vector2d(1100, 550));
					button_new(&pos_z_button_inc, arrow_inc_3, vector2d(1100, 600));

					button_new(&pos_x_button_dec, arrow_dec_1, vector2d(1000, 500));
					button_new(&pos_y_button_dec, arrow_dec_2, vector2d(1000, 550));
					button_new(&pos_z_button_dec, arrow_dec_3, vector2d(1000, 600));
				}
			}
			else if (button_check(&exit_button, vector2d(mousex, mousey)))
			{
				if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
				{
					done = 1;
				}
			}

			gf3d_command_rendering_end(commandBuffer);
			gf3d_vgraphics_render_end(bufferFrame);

			bgframe += 0.01;
			if (bgframe >= 13)
				bgframe = 0;

			if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
			continue;
		}
		else if (editor)
		{
			SDL_PumpEvents();
			SDL_GetMouseState(&mousex, &mousey);
			keys = SDL_GetKeyboardState(NULL);

			if (current_ms >= ms_per_tick)
			{
				if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
				{
					if (button_check(&pos_x_button_inc, vector2d(mousex, mousey)))
					{
						cube->position.x++;
					}
					else if (button_check(&pos_y_button_inc, vector2d(mousex, mousey)))
					{
						cube->position.y++;
					}
					else if (button_check(&pos_z_button_inc, vector2d(mousex, mousey)))
					{
						cube->position.z++;
					}
					else if (button_check(&pos_x_button_dec, vector2d(mousex, mousey)))
					{
						cube->position.x--;
					}
					else if (button_check(&pos_y_button_dec, vector2d(mousex, mousey)))
					{
						cube->position.y--;
					}
					else if (button_check(&pos_z_button_dec, vector2d(mousex, mousey)))
					{
						cube->position.z--;
					}
				}

				if (menu)
				{
					if (button_check(&start_button, vector2d(mousex, mousey)))
					{
						if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
						{
							editor = false;
							menu = false;
						}
					}
					else if (button_check(&edit_button, vector2d(mousex, mousey)))
					{
						if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
						{
							editor = true;
						}
					}
					else if (button_check(&exit_button, vector2d(mousex, mousey)))
					{
						if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
						{
							done = 1;
						}
					}
				}

				entity_update(cube);
				current_ms = 0;
				last_tick = SDL_GetTicks();
			}
			else
			{
				current_ms = SDL_GetTicks() - last_tick;
			}

			bufferFrame = gf3d_vgraphics_render_begin();
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_model_pipeline(), bufferFrame);
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_overlay_pipeline(), bufferFrame);

			commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_model_pipeline());

			entity_draw(cube, bufferFrame, commandBuffer);

			gf3d_command_rendering_end(commandBuffer);

			commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_overlay_pipeline());

				gf3d_sprite_draw(pos_x_button_inc.sprite, vector2d(pos_x_button_inc.position.x, pos_x_button_inc.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
				gf3d_sprite_draw(pos_y_button_inc.sprite, vector2d(pos_y_button_inc.position.x, pos_y_button_inc.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
				gf3d_sprite_draw(pos_z_button_inc.sprite, vector2d(pos_z_button_inc.position.x, pos_z_button_inc.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);

				gf3d_sprite_draw(pos_x_button_dec.sprite, vector2d(pos_x_button_dec.position.x, pos_x_button_dec.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
				gf3d_sprite_draw(pos_y_button_dec.sprite, vector2d(pos_y_button_dec.position.x, pos_y_button_dec.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
				gf3d_sprite_draw(pos_z_button_dec.sprite, vector2d(pos_z_button_dec.position.x, pos_z_button_dec.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);

				gf3d_sprite_draw(cursor, vector2d(mousex - (cursor->texture->width * 0.25), mousey - (cursor->texture->height * 0.25)), vector2d(1, 1), 0, bufferFrame, commandBuffer);

				if (menu)
				{
					gf3d_sprite_draw(start_button.sprite, vector2d(start_button.position.x, start_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
					gf3d_sprite_draw(edit_button.sprite, vector2d(edit_button.position.x, edit_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
					gf3d_sprite_draw(exit_button.sprite, vector2d(exit_button.position.x, exit_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
					gf3d_sprite_draw(cursor, vector2d(mousex - (cursor->texture->width * 0.25), mousey - (cursor->texture->height * 0.25)), vector2d(1, 1), 0, bufferFrame, commandBuffer);
				}

			gf3d_command_rendering_end(commandBuffer);
			gf3d_vgraphics_render_end(bufferFrame);

			if (keys[SDL_SCANCODE_ESCAPE])menu = 1; // exit condition
			continue;
		}
		else
		{
			//ENET
			if (connected)
			{
				multiplayer_host_service(isserver, host, event);
			}
			//ENET

			SDL_PumpEvents();   // update SDL's internal event structures
			keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
			if (!menu)
				SDL_GetRelativeMouseState(&mousex, &mousey);
			else
			{
				SDL_GetMouseState(&mousex, &mousey);
			}
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

			if (keys[SDL_SCANCODE_R] == true)
			{
				inputs[toss] = true;
			}
			else { inputs[toss] = false; }

			if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
			{
				inputs[attack] = 1;
			}
			else if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_RMASK))
			{
				inputs[attack] = 2;
			}
			else { inputs[attack] = 0; }


			if (!p->attacking)
			{
				if (keys[SDL_SCANCODE_1] == true)
				{
					p->class_type = 0;
					p->attack = 0;
				}
				else if (keys[SDL_SCANCODE_2] == true)
				{
					p->class_type = 1;
					p->attack = 0;
				}
				else if (keys[SDL_SCANCODE_3] == true)
				{
					p->class_type = 2;
					p->attack = 0;
				}
			}

			if (current_ms >= ms_per_tick)
			{
				if (!p->ent->_dead)
				{
					if (!menu)
						player_move(inputs, p->_playernum, mousex, mousey);
				}
				else if (p->respawn <= 0)
				{
					player_respawn(p);
				}
				else { p->respawn--; }

				bot_update(&bot);
				entity_update_all();
				item_update(&item, p);

				gfc_matrix_rotate(
					ground->modelmat,
					ground->modelmat,
					1.5708,
					vector3d(1, 0, 0));

				current_ms = 0;
				last_tick = SDL_GetTicks();
			}
			else
			{
				current_ms = SDL_GetTicks() - last_tick;
			}

			if (menu)
			{
				if (button_check(&start_button, vector2d(mousex, mousey)))
				{
					if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
					{
						menu = false;
					}
				}
				else if (button_check(&edit_button, vector2d(mousex, mousey)))
				{
					if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
					{
						menu = false;
						editor = true;
					}
				}
				else if (button_check(&exit_button, vector2d(mousex, mousey)))
				{
					if (SDL_GetMouseState(NULL, NULL, SDL_BUTTON_LMASK))
					{
						done = 1;
					}
				}
			}

			// configure render command for graphics command pool
			// for each mesh, get a command and configure it from the pool
			bufferFrame = gf3d_vgraphics_render_begin();
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_model_pipeline(), bufferFrame);
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_overlay_pipeline(), bufferFrame);
			commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_model_pipeline());

			entity_draw_all(bufferFrame, commandBuffer);
			item_draw(&item, bufferFrame, commandBuffer);

			if (!p->ent->_dead)
				player_draw_attack(bufferFrame, commandBuffer, p->_playernum);

			gf3d_command_rendering_end(commandBuffer);

			//2D OVERLAY
			commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_overlay_pipeline());
			if (menu)
			{
				gf3d_sprite_draw(start_button.sprite, vector2d(start_button.position.x, start_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
				gf3d_sprite_draw(edit_button.sprite, vector2d(edit_button.position.x, edit_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
				gf3d_sprite_draw(exit_button.sprite, vector2d(exit_button.position.x, exit_button.position.y), vector2d(1, 1), 0, bufferFrame, commandBuffer);
				gf3d_sprite_draw(cursor, vector2d(mousex - (cursor->texture->width * 0.25), mousey - (cursor->texture->height * 0.25)), vector2d(1, 1), 0, bufferFrame, commandBuffer);
			}
			else
			{
				if (p->health != 0)
					gf3d_sprite_draw(hud, vector2d(600 - ((hud->texture->width * 0.25) / 10), 700 - ((hud->texture->height * 0.5)/ 10)), vector2d(1, 1), p->health-1, bufferFrame, commandBuffer);
				if (p->stamina > 0)
					gf3d_sprite_draw(stam, vector2d(600 - ((stam->texture->width * 0.25) / 10), 640 - ((stam->texture->height * 0.5) / 10)), vector2d(1, 1), p->stamina - 1, bufferFrame, commandBuffer);
				else
					gf3d_sprite_draw(stam, vector2d(600 - ((stam->texture->width * 0.25) / 10), 640 - ((stam->texture->height * 0.5) / 10)), vector2d(1, 1), p->stamina, bufferFrame, commandBuffer);
			}
			gf3d_command_rendering_end(commandBuffer);

			gf3d_vgraphics_render_end(bufferFrame);

			/*
			frames++;
			if (time(0) - last_second >= 1)
			{
			slog("%f", frames);
			frames = 0;
			last_second = time(0);
			}
			*/
			

			//ENET
			sendpos.x = p->ent->position.x;
			sendpos.y = p->ent->position.y;
			sendpos.z = p->ent->position.z;

			if (connected && !isserver)
			{
				pack = enet_packet_create(send, sizeof(Vector3D), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, pack);
			}
			//ENET
		}
		
		if (keys[SDL_SCANCODE_ESCAPE])
		{
			menu = 1;
		}
	}

	vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());
	//cleanup

	entity_manager_close();
	player_manager_close();

	enet_host_destroy(host);

	slog("gf3d program end");
	slog_sync();
	return 0;
}

/*eol@eof*/
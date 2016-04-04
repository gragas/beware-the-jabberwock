#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "main_menu.h"
#include "create_character.h"
#include "serialize_utils.h"
#include "debug.h"
#include "game_assets.h"

void partial_back(void) { destroy_create_character(); init_main_menu(); }

void partial_create(void) {
	if(load_game_assets() == -1) {
		fprintf(stderr, "Failed to load game assets.\n");
		exit(1);
	}
	son_t* son = create_son("Created Character", 200.0, 200.0);
	init_son_hud_t(&son_hud, &son, SON_HUD_PADDING, w_height - (SON_HUD_HEIGHT + SON_HUD_PADDING) * 3);
	init_debug(son);
}

void init_create_character() {
	create_character_back_button = Button(
		10, w_height - 40,
		create_character_back_button_up,
		create_character_back_button_down,
		partial_back);
	create_character_buttons[0] = create_character_back_button;

	create_character_create_button = Button(
		w_width - 125, w_height - 40,
		create_character_create_button_up,
		create_character_create_button_down,
		partial_create);
	create_character_buttons[1] = create_character_create_button;

	/* background color and main loop functions */
	SDL_FillRect(screen, NULL,
				 SDL_MapRGBA(screen->format,
							 0x33, 0x00, 0x00, 0xFF));
	poll_events = create_character_poll_events;
	update = create_character_update;
	render = create_character_render;
	/* end background color and main loop functions */

	destroy_main_menu();
}

void create_character_poll_events(SDL_Event* event)
{
	while (SDL_PollEvent(event) != 0) {
		if (event->type == SDL_QUIT)
		{
			exit_SDL = 1;
		}
		else if (event->type == SDL_KEYDOWN)
		{
			switch (event->key.keysym.sym)
			{
			case SDLK_ESCAPE:
				partial_back();
				break;
			}
		} else if (event->type == SDL_MOUSEBUTTONDOWN) {
			size_t index;
			for (index = 0; index < NUM_CREATE_CHARACTER_BUTTONS; index++) {
				if (create_character_buttons[index] == NULL) continue;
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				if (Button_within(create_character_buttons[index], mouse_x, mouse_y)) {
					Button_press(create_character_buttons[index]);
				}
			}
		} else if (event->type == SDL_MOUSEBUTTONUP) {
			size_t index;
			for (index = 0; index < NUM_CREATE_CHARACTER_BUTTONS; index++) {
				if (create_character_buttons[index] == NULL) continue;
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				if (Button_within(create_character_buttons[index], mouse_x, mouse_y)) {
					Button_release(create_character_buttons[index], 1);
				} else {
					Button_release(create_character_buttons[index], 0);
				}
			}			
		}
	}
}

void create_character_update(void)
{
	
}

void create_character_render(void)
{
	size_t index;
	for (index = 0; index < NUM_CREATE_CHARACTER_BUTTONS; index++) {
		if (create_character_buttons[index] == NULL) continue;
		Button_blit(create_character_buttons[index], screen);
	}
}

void destroy_create_character() {
	Button_destroy(create_character_back_button);
}

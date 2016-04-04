#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "main_menu.h"
#include "utils.h"
#include "channel.h"
#include "debug.h"
#include "game_assets.h"
#include "son.h"
#include "son_hud.h"
#include "camera.h"

void init_debug(son_t* s) {
	/* main loop functions */
	poll_events = debug_poll_events;
	update = debug_update;
	render = debug_render;
	/* end main loop functions */

	if (!s) {
		if (init_son_t(&son, "Tom", w_width / 2 - 7, w_height / 2 - 27) == -1) {
			fprintf(stderr, "Failed to initialize son.\n");
			exit(-1);
		}
	} else {
		son = *s;
	}
	init_son_hud_t(&son_hud, &son, SON_HUD_PADDING, w_height - (SON_HUD_HEIGHT + SON_HUD_PADDING) * 3);
	
	/* initialize channels */
	init_channel_t(&temperature_channel, TEMPERATURE_HGRID, TEMPERATURE_RANGE);
	init_channel_t(&humidity_channel, HUMIDITY_HGRID, HUMIDITY_RANGE);
	init_channel_t(&spirit_channel, SPIRIT_HGRID, SPIRIT_RANGE);
	/* end initialize channels */

	/* initialize debug labels */
	#define DEFAULT_TTF_FONT_NAME FONT_PATH"/LiberationMono-Regular.ttf"
    #define DEFAULT_TTF_FONT_SIZE 18
	#define DEFAULT_TTF_FONT_X 10
	#define DEFAULT_TTF_FONT_X_OFFSET 200
	#define DEFAULT_TTF_FONT_Y 10
	#define DEFAULT_TTF_FONT_Y_OFFSET 25
	#define DEFAULT_TTF_FONT_R 0x00
	#define DEFAULT_TTF_FONT_G 0x00
	#define DEFAULT_TTF_FONT_B 0x00
	#define DEFAULT_TTF_FONT_A 0xFF
	init_label_t(&tile_position_name_label, "Tile Position: ",
				 DEFAULT_TTF_FONT_X, DEFAULT_TTF_FONT_Y,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 DEFAULT_TTF_FONT_R, DEFAULT_TTF_FONT_G, DEFAULT_TTF_FONT_B,
				 DEFAULT_TTF_FONT_A);
	init_label_t(&temperature_name_label, "Temperature: ",
				 DEFAULT_TTF_FONT_X, DEFAULT_TTF_FONT_Y + \
				 DEFAULT_TTF_FONT_Y_OFFSET,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 DEFAULT_TTF_FONT_R, DEFAULT_TTF_FONT_G, DEFAULT_TTF_FONT_B,
				 DEFAULT_TTF_FONT_A);
	init_label_t(&humidity_name_label, "Humidity: ",
				 DEFAULT_TTF_FONT_X, DEFAULT_TTF_FONT_Y + \
				 DEFAULT_TTF_FONT_Y_OFFSET * 2,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 DEFAULT_TTF_FONT_R, DEFAULT_TTF_FONT_G, DEFAULT_TTF_FONT_B,
				 DEFAULT_TTF_FONT_A);
	init_label_t(&spirit_name_label, "Spirit: ",
				 DEFAULT_TTF_FONT_X, DEFAULT_TTF_FONT_Y + \
				 DEFAULT_TTF_FONT_Y_OFFSET * 3,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 DEFAULT_TTF_FONT_R, DEFAULT_TTF_FONT_G, DEFAULT_TTF_FONT_B,
				 DEFAULT_TTF_FONT_A);
	tile_x = 0;
	tile_y = 0;
	temperature = 0.0;
	humidity = 0.0;
	spirit = 0.0;
	snprintf(tile_position_buffer, 128, "%d, %d", tile_x, tile_y);
	snprintf(temperature_buffer, 8, "%.1f F", temperature);
	snprintf(humidity_buffer, 8, "%.1f %%", humidity);
	snprintf(spirit_buffer, 8, "%.1f", spirit);
	init_label_t(&tile_position_label, tile_position_buffer,
				 DEFAULT_TTF_FONT_X + DEFAULT_TTF_FONT_X_OFFSET,
				 DEFAULT_TTF_FONT_Y,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 DEFAULT_TTF_FONT_R, DEFAULT_TTF_FONT_G, DEFAULT_TTF_FONT_B,
				 DEFAULT_TTF_FONT_A);
	init_label_t(&temperature_label, temperature_buffer,
				 DEFAULT_TTF_FONT_X + DEFAULT_TTF_FONT_X_OFFSET,
				 DEFAULT_TTF_FONT_Y + DEFAULT_TTF_FONT_Y_OFFSET,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 DEFAULT_TTF_FONT_R, DEFAULT_TTF_FONT_G, DEFAULT_TTF_FONT_B,
				 DEFAULT_TTF_FONT_A);
	init_label_t(&humidity_label, humidity_buffer,
				 DEFAULT_TTF_FONT_X + DEFAULT_TTF_FONT_X_OFFSET,
				 DEFAULT_TTF_FONT_Y + DEFAULT_TTF_FONT_Y_OFFSET * 2,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 DEFAULT_TTF_FONT_R, DEFAULT_TTF_FONT_G, DEFAULT_TTF_FONT_B,
				 DEFAULT_TTF_FONT_A);
	init_label_t(&spirit_label, spirit_buffer,
				 DEFAULT_TTF_FONT_X + DEFAULT_TTF_FONT_X_OFFSET,
				 DEFAULT_TTF_FONT_Y + DEFAULT_TTF_FONT_Y_OFFSET * 3,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 DEFAULT_TTF_FONT_R, DEFAULT_TTF_FONT_G, DEFAULT_TTF_FONT_B,
				 DEFAULT_TTF_FONT_A);
	/* end initialize debug labels */

	/* initialize the camera */
	init_camera();
	/* end initialize the camera */
}

void debug_poll_events(SDL_Event* event)
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
				exit_SDL = 1;
				break;
			}
		} else if (event->type == SDL_MOUSEBUTTONDOWN) {
			
		} else if (event->type == SDL_MOUSEBUTTONUP) {
			
		}
	}
}

void debug_update(void)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (update_son_t(&son, keys) != 0) {
		render_son_hud_t(&son_hud);
	}
	
	/* Update channels */
	int temp_tile_x = (int)son.x / TILE_SIZE;
	int temp_tile_y = (int)son.y / TILE_SIZE;
	float temp_temperature = channel_get(&temperature_channel, tile_x, tile_y);
	float temp_humidity = channel_get(&humidity_channel, tile_x, tile_y);
	float temp_spirit = channel_get(&spirit_channel, tile_x, tile_y);
	
	if (temp_tile_x != tile_x || temp_tile_y != tile_y) {
		tile_x = temp_tile_x;
		tile_y = temp_tile_y;
		snprintf(tile_position_buffer, 128, "%d, %d", tile_x, tile_y);		
		render_text(&tile_position_label);
	}
	if (temp_temperature != temperature) {
		temperature = temp_temperature;
		snprintf(temperature_buffer, 8, "%.1f F", temperature);
		render_text(&temperature_label);
	}
	if (temp_humidity != humidity) {
		humidity = temp_humidity;
		snprintf(humidity_buffer, 8, "%.1f %%", humidity);
		render_text(&humidity_label);
	}
	if (temp_spirit != spirit) {
		spirit = temp_spirit;
		snprintf(spirit_buffer, 8, "%.1f", spirit);
		render_text(&spirit_label);
	}
	/* End update channels */
	
	/* Update the camera */
	update_camera(tile_x, tile_y,
				  &temperature_channel,
				  &humidity_channel,
				  &spirit_channel);
	/* End update the camera */
}

void debug_render(void)
{
	SDL_FillRect(screen, NULL,
				 SDL_MapRGBA(screen->format,
							 0xFF, 0xEE, 0xCC, 0xFF));
	blit_map_from_camera(son.x, son.y, screen);
	blit_son_t(&son, screen);
	blit_son_hud_t(&son_hud, screen);
	blit_label_t(&tile_position_name_label, screen);
	blit_label_t(&temperature_name_label, screen);
	blit_label_t(&humidity_name_label, screen);
	blit_label_t(&spirit_name_label, screen);
	blit_label_t(&tile_position_label, screen);
	blit_label_t(&temperature_label, screen);
	blit_label_t(&humidity_label, screen);
	blit_label_t(&spirit_label, screen);
}

void destroy_debug() {
	destroy_game_assets();
}

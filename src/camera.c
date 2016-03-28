#include <math.h>
#include <SDL2/SDL.h>
#include "camera.h"
#include "utils.h"
#include "channel.h"
#include "main.h"

static SDL_Surface* camera_surf;
static SDL_Rect camera_rect;
static int camera_width;
static int camera_height;
static int camera_cornerx;
static int camera_cornery;
static SDL_Surface* minimap_surf;
static SDL_Rect minimap_rect;
static int minimap_width;
static int minimap_height;
static int last_cx;
static int last_cy;

static void render_map(int x, int y,
					   channel_t* temperature_channel,
					   channel_t* humidity_channel,
					   channel_t* spirit_channel);

static Uint32 color_function(int tile_x, int tile_y,
							 channel_t* temperature_channel,
							 channel_t* humidity_channel,
							 channel_t* spirit_channel);

void blit_map_from_camera(float x, float y, SDL_Surface* dest) {
	camera_rect.x = camera_cornerx - (int)x % TILE_SIZE;
	camera_rect.y = camera_cornery - (int)y % TILE_SIZE;
	SDL_BlitSurface(camera_surf, NULL, dest, &camera_rect);
	SDL_BlitSurface(minimap_surf, NULL, dest, &minimap_rect);
}

void update_camera(int tile_x, int tile_y,
				channel_t* temperature_channel,
				channel_t* humidity_channel,
				channel_t* spirit_channel) {
	if (tile_x != last_cx || tile_y != last_cy) {
		last_cx = tile_x;
		last_cy = tile_y;
		render_map(tile_x, tile_y,
				   temperature_channel,
				   humidity_channel,
				   spirit_channel);
	}
}

static void render_map(int x, int y,
					   channel_t* temperature_channel,
					   channel_t* humidity_channel,
					   channel_t* spirit_channel) {
	SDL_Rect temp_camera_rect, temp_minimap_rect;
	temp_camera_rect.w = TILE_SIZE;
	temp_camera_rect.h = TILE_SIZE;
	temp_minimap_rect.w = MINIMAP_TILE_SIZE;
	temp_minimap_rect.h = MINIMAP_TILE_SIZE;
	for (int i = 0; i < camera_width; i++) {
		for (int j = 0; j < camera_height; j++) {
			temp_camera_rect.x = i * TILE_SIZE;
			temp_camera_rect.y = j * TILE_SIZE;
			SDL_FillRect(camera_surf, &temp_camera_rect,
						 color_function((i + x) * TILE_SIZE,
										(j + y) * TILE_SIZE,
										temperature_channel,
										humidity_channel,
										spirit_channel));
			temp_minimap_rect.x = (MINIMAP_BORDER_SIZE + i) * MINIMAP_TILE_SIZE;
			temp_minimap_rect.y = (MINIMAP_BORDER_SIZE + j) * MINIMAP_TILE_SIZE;
			SDL_FillRect(minimap_surf, &temp_minimap_rect,
						 color_function((i + x) * MINIMAP_TILE_SIZE,
										(j + y) * MINIMAP_TILE_SIZE,
										temperature_channel,
										humidity_channel,
										spirit_channel));
		}
	}
}

static Uint32 color_function(int tile_x, int tile_y,
							 channel_t* temperature_channel,
							 channel_t* humidity_channel,
							 channel_t* spirit_channel) {
	float temperature = channel_get(temperature_channel, tile_x, tile_y);
	float humidity = channel_get(humidity_channel, tile_x, tile_y);
	float spirit = channel_get(spirit_channel, tile_x, tile_y);

	float tdev = fabs(0.5f - temperature / (float)TEMPERATURE_RANGE) / 3.0f;
	float hdev = fabs(0.5f - humidity / (float)HUMIDITY_RANGE) / 3.0f;
	float sdev = fabs(0.5f - spirit / (float)SPIRIT_RANGE) / 3.0f;

	Uint8 R = (Uint8)((sdev * 0.5f + tdev + hdev * 1.5f) * 256);
	Uint8 G = (Uint8)((0.95f - (sdev + tdev + hdev)) * 256);
	Uint8 B = (Uint8)((sdev * 1.5f + tdev + hdev * 0.5f) * 256);
	
	return SDL_MapRGBA(screen->format, R, G, B, 0xFF);
}

void init_camera() {
	/* initialize camera */
	last_cx = 0;
	last_cy = 0;
	if (w_width % TILE_SIZE == 0) camera_width = w_width / TILE_SIZE;
	else camera_width = w_width / TILE_SIZE + 1;
	if (w_height % TILE_SIZE == 0) camera_height = w_height / TILE_SIZE;
	else camera_height = w_height / TILE_SIZE + 1;
	camera_width += 2 * BORDER_SIZE;
	camera_height += 2 * BORDER_SIZE;
	camera_cornerx = -1 * TILE_SIZE * BORDER_SIZE;
	camera_cornery = -1 * TILE_SIZE * BORDER_SIZE;
	camera_surf = SDL_CreateRGBSurface(0,
									   camera_width * TILE_SIZE,
									   camera_height * TILE_SIZE,
									   32, 0, 0, 0, 0);
	SDL_FillRect(camera_surf, NULL,
				 SDL_MapRGBA(screen->format,
							 0x00, 0x00, 0x00, 0xFF));
	camera_rect.w = camera_surf->w;
	camera_rect.h = camera_surf->h;
	/* end initialize camera */

	/* initialize minimap */
	minimap_width = camera_width + 2 * MINIMAP_BORDER_SIZE;
	minimap_height = camera_height + 2 * MINIMAP_BORDER_SIZE;
	minimap_rect.x = w_width - 10 - minimap_width * MINIMAP_TILE_SIZE;
	minimap_rect.y = 10;
	minimap_surf = SDL_CreateRGBSurface(0,
										minimap_width * MINIMAP_TILE_SIZE,
										minimap_height * MINIMAP_TILE_SIZE,
										32, 0, 0, 0, 0);
	SDL_FillRect(minimap_surf, NULL,
				 SDL_MapRGBA(screen->format,
							 MINIMAP_BORDER_R, MINIMAP_BORDER_G, MINIMAP_BORDER_B, 0xFF));
	minimap_rect.w = minimap_surf->w;
	minimap_rect.h = minimap_surf->h;
	/* end initialize minimap */
}

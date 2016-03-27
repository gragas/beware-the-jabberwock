#ifndef _CAMERA_H
#define _CAMERA_H

#include <SDL2/SDL.h>
#include "channel.h"

#define BORDER_SIZE 1

SDL_Surface* camera_surf;

int camera_width, camera_height;

void init_camera(void);
void blit_map_from_camera(float x, float y, SDL_Surface* dest);
void update_camera(int tile_x, int tile_y,
				channel_t* temperature_channel,
				channel_t* humidity_channel,
				channel_t* spirit_channel);

#endif

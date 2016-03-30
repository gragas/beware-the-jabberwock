#ifndef _DEBUG_H
#define _DEBUG_H

#include "button.h"
#include "channel.h"
#include "son.h"
#include "son_hud.h"
#include "label.h"

void init_debug();
void debug_poll_events(SDL_Event* event);
void debug_update(void);
void debug_render(void);
void destroy_debug(void);

son_t son;
son_hud_t son_hud;

channel_t temperature_channel;
channel_t humidity_channel;
channel_t spirit_channel;

label_t tile_position_name_label;
label_t temperature_name_label;
label_t humidity_name_label;
label_t spirit_name_label;

int tile_x, tile_y;
float temperature;
float humidity;
float spirit;

char tile_position_buffer[128];
char temperature_buffer[8];
char humidity_buffer[8];
char spirit_buffer[8];

label_t tile_position_label;
label_t temperature_label;
label_t humidity_label;
label_t spirit_label;

#endif

#ifndef _DEBUG_H
#define _DEBUG_H

#include "button.h"
#include "channel.h"
#include "son.h"

void init_debug();
void debug_poll_events(SDL_Event* event);
void debug_update(void);
void debug_render(void);
void destroy_debug(void);

son_t* son;
channel_t temperature;
channel_t humidity;
channel_t spirit;

#endif

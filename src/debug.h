#ifndef _DEBUG_H
#define _DEBUG_H

#include "button.h"
#include "son.h"

void init_debug();
void debug_poll_events(SDL_Event* event);
void debug_update(void);
void debug_render(void);
void destroy_debug(void);

son_t* son;

#endif

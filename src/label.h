#ifndef _LABEL_H
#define _LABEL_H

#include <SDL2/SDL.h>

typedef struct Label {
	SDL_Surface* surf;
	SDL_Rect rect;
	SDL_Color color;
	const char* s;
	const char* font_name;
	int font_size;
} label_t;

void init_label_t(label_t* label, char* s, int x, int y,
				  char* font_name, int font_size,
				  Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void render_text(label_t* label);
void blit_label_t(label_t* label, SDL_Surface* dest);

#endif

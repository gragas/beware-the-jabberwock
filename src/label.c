#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "label.h"

void init_label_t(label_t* label, char* s, int x, int y,
				  char* font_name, int font_size,
				  Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	label->color.r = r;
	label->color.g = g;
	label->color.b = b;
	label->color.a = a;
	label->s = s;
	label->rect.x = x;
	label->rect.y = y;
	label->font_name = font_name;
	label->font_size = font_size;
	render_text(label);
}

void render_text(label_t* label) {
	TTF_Font* font = TTF_OpenFont(label->font_name, label->font_size);
	if (font == NULL) {
		fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
		exit(1);
	}
	label->surf = TTF_RenderText_Solid(font, label->s, label->color);
	TTF_CloseFont(font);
	font = NULL;
	label->rect.w = label->surf->w;
	label->rect.h = label->surf->h;
}

void blit_label_t(label_t* label, SDL_Surface* dest) {
	SDL_BlitSurface(label->surf, NULL, dest, &label->rect);
}

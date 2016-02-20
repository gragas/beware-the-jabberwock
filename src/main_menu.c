#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "main_menu.h"

void init_main_menu() {
	#ifdef DEBUG
      #if (DEBUG == 1)
	/* debug button rect */
	main_menu_debug_button_rect.w = main_menu_debug_button->w;
	main_menu_debug_button_rect.h = main_menu_debug_button->h;
	main_menu_debug_button_rect.x = 10;
	main_menu_debug_button_rect.y = 10;
	/* end debug button rect */
	  #endif
	#endif

	/* background color and main loop functions */
	SDL_FillRect(screen, NULL,
				 SDL_MapRGBA(screen->format,
							 0x33, 0x00, 0x00, 0xFF));
	poll_events = main_menu_poll_events;
	update = main_menu_update;
	render = main_menu_render;
	/* end background color and main loop functions */
}

void main_menu_poll_events(SDL_Event* event) {
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
		}
	}
}

void main_menu_update(void) {

}

void main_menu_render(void) {

	#ifdef DEBUG
      #if (DEBUG == 1)
	SDL_BlitSurface(main_menu_debug_button, NULL,
					screen, &main_menu_debug_button_rect);
	  #endif
	#endif
}

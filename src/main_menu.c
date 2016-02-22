#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "main_menu.h"

void partial_exit(void) { destroy_main_menu(); exit(0); }

void init_main_menu() {
	#ifdef DEBUG
      #if (DEBUG == 1)
	main_menu_debug_button = Button(10, 10,
						  main_menu_debug_button_up,
						  main_menu_debug_button_down,
						  NULL);
	main_menu_buttons[0] = main_menu_debug_button;
      #endif
	#endif

	main_menu_exit_button = Button(w_width / 2, w_height - 50,
						  main_menu_exit_button_up,
						  main_menu_exit_button_down,
								   partial_exit);
	Button_set_pos(main_menu_exit_button,
				   main_menu_exit_button->x - main_menu_exit_button->w / 2,
				   main_menu_exit_button->y);
	main_menu_buttons[1] = main_menu_exit_button;


	/* background color and main loop functions */
	SDL_FillRect(screen, NULL,
				 SDL_MapRGBA(screen->format,
							 0x33, 0x00, 0x00, 0xFF));
	poll_events = main_menu_poll_events;
	update = main_menu_update;
	render = main_menu_render;
	/* end background color and main loop functions */
}

void main_menu_poll_events(SDL_Event* event)
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
			size_t index;
			for (index = 0; index < NUM_MAIN_MENU_BUTTONS; index++) {
				if (main_menu_buttons[index] == NULL) continue;
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				if (Button_within(main_menu_buttons[index], mouse_x, mouse_y)) {
					Button_press(main_menu_buttons[index]);
				}
			}
		} else if (event->type == SDL_MOUSEBUTTONUP) {
			size_t index;
			for (index = 0; index < NUM_MAIN_MENU_BUTTONS; index++) {
				if (main_menu_buttons[index] == NULL) continue;
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				if (Button_within(main_menu_buttons[index], mouse_x, mouse_y)) {
					Button_release(main_menu_buttons[index], 1);
				} else {
					Button_release(main_menu_buttons[index], 0);
				}
			}			
		}
	}
}

void main_menu_update(void)
{
	
}

void main_menu_render(void)
{
	size_t index;
	for (index = 0; index < NUM_MAIN_MENU_BUTTONS; index++) {
		if (main_menu_buttons[index] == NULL) continue;
		Button_blit(main_menu_buttons[index], screen);
	}
}

void destroy_main_menu() {
	#ifdef DEBUG
      #if (DEBUG == 1)
	Button_destroy(main_menu_debug_button);
      #endif
	#endif

	Button_destroy(main_menu_exit_button);
}

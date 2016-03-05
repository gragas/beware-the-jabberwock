#include "game_assets.h"
#include "utils.h"

/*
   * RETURN VALUE:
   * If this function fails, -1 is returned.
   * Otherwise, 0 is returned.
*/
int load_game_assets(void) {

	bedrock_sand_0 = load_image(
		ASSETS_PATH"/bedrock/sand_0.png");
	if (bedrock_sand_0 == NULL) return -1;

	bedrock_sand_1 = load_image(
		ASSETS_PATH"/bedrock/sand_1.png");
	if (bedrock_sand_1 == NULL) return -1;

	bedrock_sand_2 = load_image(
		ASSETS_PATH"/bedrock/sand_2.png");
	if (bedrock_sand_2 == NULL) return -1;

	bedrock_sand_3 = load_image(
		ASSETS_PATH"/bedrock/sand_3.png");
	if (bedrock_sand_3 == NULL) return -1;

	bedrock_sand_4 = load_image(
		ASSETS_PATH"/bedrock/sand_4.png");
	if (bedrock_sand_4 == NULL) return -1;

	son_down = malloc(sizeof(SDL_Surface *) * NUM_SON_DOWN);

	size_t son_down_index;
	for(son_down_index = 0; son_down_index < NUM_SON_DOWN; son_down_index++) {
		size_t n_bytes = 128;
		char* buffer = calloc(n_bytes, 1);
		snprintf(buffer, n_bytes, ASSETS_PATH"/son/down_%zu.png", son_down_index);
		son_down[son_down_index] = load_image(buffer);
		if(son_down[son_down_index] == NULL) return -1;
		free(buffer);
	}

	son_shadow = load_image(
		ASSETS_PATH"/son/shadow.png");
	if (son_shadow == NULL) return -1;

	return 0;
}

void destroy_game_assets(void) {
	free(son_down); son_down = NULL;
}

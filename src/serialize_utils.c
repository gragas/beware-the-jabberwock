#include <stdio.h>
#include "utils.h"
#include "serialize_utils.h"
#include "son.h"

// the returned son must be freed by the user
son_t* create_son(char* name, float x, float y) {
	son_t* son = malloc(sizeof(son_t));
    if(init_son_t(son, name, x, y) == -1) {
		fprintf(stderr, "Could not initialize son_t.\n");
		exit(1);
	}
	save_son(son);
	return son;
}

void save_son(son_t* son) {
	#define MAXIMUM_PATH_BYTES 1024
	char path[MAXIMUM_PATH_BYTES];
	snprintf(path, MAXIMUM_PATH_BYTES, CHARACTER_SAVE_PATH"/%s", son->name);
	FILE* save_file = fopen(path, "wb+");
	// first, don't save SDL stuff
	// then, save numerical stuff
	fprintf(save_file, "%f %f %f %f\n", son->x, son->y, son->xv, son->yv);
	fprintf(save_file, "%f\n", son->base_speed);
	fprintf(save_file, "%f %f %f\n", son->max_health, son->max_energy, son->max_spirit);
	fprintf(save_file, "%f %f %f\n", son->health, son->energy, son->spirit);
	// then save the character name
	fprintf(save_file, "%s", son->name); // notice the lack of a newline
	fclose(save_file);
}

// the returned son must be freed by the user
son_t* load_son(char* name) {
	float x, y, xv, yv;
	float base_speed;
	float max_health, max_energy, max_spirit;
	float health, energy, spirit;
	char son_name[SON_MAX_NAME_BYTES];
	#define MAXIMUM_PATH_BYTES 1024
	char path[MAXIMUM_PATH_BYTES];
	snprintf(path, MAXIMUM_PATH_BYTES, CHARACTER_SAVE_PATH"/%s", name);
	FILE* load_file = fopen(path, "r");
	if (load_file == NULL) {
		fprintf(stderr, "Could not open file at %s.\n", path);
		exit(1);
	}
	fscanf(load_file, "%f %f %f %f\n", &x, &y, &xv, &yv);
	fscanf(load_file, "%f\n", &base_speed);
	fscanf(load_file, "%f %f %f\n", &max_health, &max_energy, &max_spirit);
	fscanf(load_file, "%f %f %f\n", &health, &energy, &spirit);
	size_t nbytes;
	getline((char**)&son_name, &nbytes, load_file);
	fclose(load_file);
	son_t* son = malloc(sizeof(son_t));
	init_son_t(son, son_name, x, y);
	son->xv = xv;
	son->yv = yv;
	son->base_speed = base_speed;
	son->max_health = max_health;
	son->max_energy = max_energy;
	son->max_spirit = max_spirit;
	son->health = health;
	son->energy = energy;
	son->spirit = spirit;
	return son;
}

#include <stdlib.h>
#include <pthread.h>
#include "perlin.h"
#include "mapgen.h"

typedef struct channel_args {
	float x, y, gain;
	int octaves, hgrid;
	float** array;
} channel_args_t;

void* gen_channel(void* ptr) {
	channel_args_t* ca = (channel_args_t*)ptr;
	size_t height = ca->y;
	size_t width  = ca->x;
	float gain    = ca->gain;
	int octaves   = ca->octaves;
	int hgrid     = ca->hgrid;

	float** array = malloc(sizeof(float*)*height);

	size_t row, col;
	for (row = 0; row < height; row++) {
		array[row] = malloc(sizeof(float)*width);
		for (col = 0; col < width; col++) {
			array[row][col] = perlin_two((float)col, (float)row, gain, octaves, hgrid);
		}
	}
	ca->array = array;
	return NULL;
}

map_t* gen_map(float x, float y, float gain, int octaves, int hgrid) {
	pthread_t pr, pg, pb;
	channel_args_t car, cag, cab;
	car.x = x;
	car.y = y;
	car.gain = gain;
	car.octaves = octaves;
	car.hgrid = hgrid;
	cag.x = x;
	cag.y = y;
	cag.gain = gain;
	cag.octaves = octaves;
	cag.hgrid = hgrid;
	cab.x = x;
	cab.y = y;
	cab.gain = gain;
	cab.octaves = octaves;
	cab.hgrid = hgrid;
	pthread_create(&pr, NULL, gen_channel, &car);
	pthread_create(&pg, NULL, gen_channel, &cag);
	pthread_create(&pb, NULL, gen_channel, &cab);
	pthread_join(pr, NULL);
	pthread_join(pg, NULL);
	pthread_join(pb, NULL);
	map_t* m = malloc(sizeof(map_t));
	m->r = car.array;
	m->g = cag.array;
	m->b = cab.array;
	return m;
}

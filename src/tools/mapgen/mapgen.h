#ifndef _MAPGEN_H
#define _MAPGEN_H

typedef struct map {
	float** r;
	float** g;
	float** b;
} map_t;

void* gen_channel(void* ptr);
map_t* gen_map(float x, float y, float gain, int octaves, int hgrid);

#endif

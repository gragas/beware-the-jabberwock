#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "perlin.h"

typedef struct Channel {
	int hgrid;
	float mult;
} channel_t;

void init_channel_t(channel_t* ch, int hgrid, float mult);
float channel_get(channel_t* ch, float x, float y);

#endif

#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "perlin.h"

#define TEMPERATURE_HGRID 5
#define HUMIDITY_HGRID 10
#define SPIRIT_HGRID 7

#define TEMPERATURE_RANGE 120.0f
#define HUMIDITY_RANGE 100.0f
#define SPIRIT_RANGE 10.0f

typedef struct Channel {
	int hgrid;
	float mult;
} channel_t;

void init_channel_t(channel_t* ch, int hgrid, float mult);
float channel_get(channel_t* ch, float x, float y);

#endif

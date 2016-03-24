#include "channel.h"
#include "perlin.h"

void init_channel_t(channel_t* ch, int hgrid, float mult) {
	ch->hgrid = hgrid;
	ch->mult = mult;
}

// Returns a value between 0 and ch->mult
float channel_get(channel_t* ch, float x, float y) {
	return ch->mult * (perlin_two(x, y, 0.5, 1, ch->hgrid) + 0.5);
}

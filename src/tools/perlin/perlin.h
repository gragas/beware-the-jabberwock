#ifndef __PERLIN_H
#define __PERLIN_H

#include <stdlib.h>
#include <math.h>

float noise(int x, int y);

float interpolate(float a, float b, float x);
float smooth_noise(int x, int y);
float noise_handler(float x, float y);
float perlin_two(float x, float y, float gain, int octaves, int hgrid);

#endif

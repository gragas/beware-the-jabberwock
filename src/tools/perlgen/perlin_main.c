#include <stdlib.h>
#include <stdio.h>
#include "perlin.h"

void print_usage() {
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "perlgen <size_t w> <size_t h> <float gain> <int octaves> <int hgrid>\n");
}

int main(int argc, char* argv[]) {
	if (argc != 6) {
		print_usage();
		exit(1);
	} else {
		size_t width = atoi(argv[1]);
		size_t height = atoi(argv[2]);
		float gain = atof(argv[3]);
		int octaves = atoi(argv[4]);
		int hgrid = atoi(argv[5]);

		FILE* image_file = fopen("output.txt", "w");
		if (image_file == NULL) {
			fprintf(stderr, "Failed open filestream.\n");
			exit(1);
		}

		float** array = alloca(sizeof(float*)*height);

		size_t row, col;
		for (row = 0; row < height; row++) {
			array[row] = alloca(sizeof(float)*width);
			for (col = 0; col < width; col++) {
				array[row][col] = perlin_two((float)col, (float)row, gain, octaves, hgrid);
				fprintf(image_file, "%f ", array[row][col]);
			}
			fprintf(image_file, "\n");
		}
	}
}

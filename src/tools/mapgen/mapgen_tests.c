#include <stdio.h>
#include "mapgen.h"

int main() {
	fprintf(stderr, "Running tests...");
	map_t* m;
	m = gen_map(1024, 1024, 128, 1, 1);
	fprintf(stderr, "complete\n");
}

#include "Tilemap.h"
#include <stdio.h>
#include <SOIL/SOIL.h>

//uses bitmap to load tiles coordinates to any array of Tile
Tilemap loadTiles(const char* bitMapFile) {

	int width, height;
	//load da bitmap
	unsigned char* bitmap = SOIL_load_image (
		bitMapFile,
		&width,
		&height,
		0,
		SOIL_LOAD_RGB
	);

	if(!bitmap) {
		fprintf(stderr, "Failed to load da bitmap. %s\n", SOIL_last_result());
	}

	//breakdown the loaded bitmap in pixels 32x32 + 3 colors r,g,b
	unsigned char (*pixels)[32][3] = (unsigned char (*)[32][3]) bitmap;

	//allocate space for 100 tiles
	Tile *tiles = (Tile *) malloc(sizeof(Tile)*100);
	int ntile = 0, ctile = 0, size = 100;

	//iterate through the pixels and get r,g,b value of each pixel
	for(int x = 0; x < 32; ++x)
		for(int y = 0; y < 32; ++y) {
			unsigned char r = pixels[x][y][0];
			unsigned char g = pixels[x][y][1];
			unsigned char b = pixels[x][y][2];

			if(r==255) {
				Tile tile;
				tile.pos.x = x;
				tile.pos.y = y;
				tiles[ntile] = tile;
				++ntile;
				++ctile;
			}

			if(ntile >= 100) {
				size += 100;
				tiles = (Tile *)realloc(tiles, sizeof(Tile)*size);
				fprintf(stderr,"Reallocated total size: %ld\n", sizeof(Tile)*size);
				ntile = 0;
			}
		}

		printf("\nNo.of Tiles: %d\n", ctile);
		fflush(stdout);

	//create tilemap from da loaded data
	Tilemap tilemap;
	tilemap.tiles = tiles;
	tilemap.nTiles = ctile;

	SOIL_free_image_data(bitmap);

	return tilemap;
}

void freeMap(Tilemap* map) {
	if(map->tiles) {
		free(map->tiles);
		fprintf(stderr,"Map Destroyed.\n");
	}
}
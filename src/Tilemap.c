#include "Tilemap.h"
#include "Shader.h"
#include <stdio.h>
#include <SOIL/SOIL.h>

#define MAP_WIDTH 256
#define MAP_HEIGHT 32

static Tile createTile(int x, int y, int spriteX, int  spriteY,
					   bool rigid, bool animate) {

	Tile tile;
	tile.pos.x = x*TILE_SIZE;
	tile.pos.y = y*TILE_SIZE;
	tile.sprite.x = spriteX;
	tile.sprite.y = spriteY;
	tile.rigid = rigid;
	tile.animate = animate;
	return tile;
}

//uses bitmap to load tiles coordinates to any array of Tile
Tilemap loadTilemap(const char* bitMapFile, SpriteSheet spriteSheet) {


	Tilemap tilemap;
	tilemap.spriteSheet = spriteSheet;

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
	unsigned char (*pixels)[MAP_HEIGHT][3] = (unsigned char (*)[MAP_HEIGHT][3]) bitmap;


	int ntile = 0, size = 500;
	//allocate space for 100 tiles
	Tile *tiles = (Tile *) malloc(sizeof(Tile)*size);

	//pre create spriteSheet & animationFor Coin
	SpriteSheet coinSheet = loadSpriteSheet("coin.png", (Vec2D){32,32},
											(Vec2D){192, 32});
	Animation coinAnimation = initAnimation(coinSheet);

	//iterate through the pixels and get r,g,b value of each pixel
	for(int x = 0; x < MAP_WIDTH; ++x)
		for(int y = 0; y < MAP_HEIGHT; ++y) {
			unsigned char r = pixels[x][y][0];
			unsigned char g = pixels[x][y][1];
			unsigned char b = pixels[x][y][2];

			if(r==255 && g==0 && b==0) {

					tiles[ntile] = createTile(x, y, 0, 0, true, false);
					++ntile;

			} else if(r==255 && g==0 && b==204) {

					tiles[ntile] = createTile(x, y, 1, 0, false, false);
					++ntile;
			} else if(r==100 && g==100 && b==0) {

				tiles[ntile] = createTile(x, y, 0, 0, false, true);
				tiles[ntile].animation = coinAnimation;
				++ntile;
			}

			if(ntile+4 >= size) { //ntile + no.of unique tiles+1
				size += 100;
				tiles = (Tile *)realloc(tiles, sizeof(Tile)*size);
				fprintf(stderr,"Reallocated total size: %ld\n", sizeof(Tile)*size);
			}
		}

		tiles = (Tile *)realloc(tiles, sizeof(Tile)*ntile);
		fprintf(stderr, "Trim size: %ld\n", sizeof(Tile)*ntile);
		printf("\nNo.of Tiles: %d\n", ntile);
		fflush(stdout);

	//create tilemap from da loaded data
	tilemap.tiles = tiles;
	tilemap.nTiles = ntile;

	SOIL_free_image_data(bitmap);

	return tilemap;
}

void freeMap(Tilemap* map) {
	if(map->tiles) {
		free(map->tiles);
		fprintf(stderr,"Map Destroyed.\n");
	}
}
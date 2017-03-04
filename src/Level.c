#include "Level.h"
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

static Enemy createEnemy(int x, int y, Entity emy, enum EnemyType type) {
	Enemy enemy;
	emy.pos.x = x*TILE_SIZE;
	emy.pos.y = y*TILE_SIZE;
	enemy.point.x = emy.pos.x + TILE_SIZE*2;
	enemy.point.y = emy.pos.x - TILE_SIZE*2;
	enemy.reach = false;
	enemy.entity = emy;
	enemy.type = type;
	return enemy;
}

//uses bitmap to load tiles coordinates to any array of Tile
Level loadTilemap(const char *bitMap, const char *spriteSheet, const char* bg,
			   const char* aSpriteSheet) {

	Tilemap tilemap;
	tilemap.spriteSheet = loadSpriteSheet(spriteSheet, (Vec2D){64,64},
													   (Vec2D){128,256});

	int width, height;
	//load da bitmap
	unsigned char* bitmap = SOIL_load_image (
		bitMap,
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


	int ntile = 0, sizeT = 500, nEnemy = 0, sizeE = 20;
	//allocate space for 100 tiles
	Tile *tiles = (Tile *) malloc(sizeof(Tile)*sizeT);
	Enemy *enemies = (Enemy *) malloc(sizeof(Enemy)*sizeE);

	SpriteSheet enemySheet = loadSpriteSheet("sprites.png", (Vec2D){64,64},
											(Vec2D){384, 128});
	Entity enemyTest = initEntity((Vec2D){0, 0}, enemySheet);

	//pre create spriteSheet & animationFor Coin
	SpriteSheet coinSheet = loadSpriteSheet(aSpriteSheet, (Vec2D){32,32},
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

			} else if (r == 255 && g == 102 && b == 204) {
				tiles[ntile] = createTile(x, y, 1, 0, true, false);
				++ntile;
			} else if(r==255 && g==0 && b==204) {

				tiles[ntile] = createTile(x, y, 1, 1, false, false);
				++ntile;
			} else if(r == 102 && g == 51 && b ==102) {
				tiles[ntile] = createTile(x, y, 0, 2, false, false);
				++ntile;
			} else if(r == 51 && g == 0 && b == 51) {
				tiles[ntile] = createTile(x, y, 0, 1, true, false);
				++ntile;

			} else if(r == 0 && g == 0 && b == 255) {
				tiles[ntile] = createTile(x, y, 0, 3, true, false);
				++ntile;
			} else if(r==100 && g==100 && b==0) {

				tiles[ntile] = createTile(x, y, 0, 0, false, true);
				tiles[ntile].animation = coinAnimation;
				tiles[ntile].animation.state = 0;
				++ntile;
			} else if(r == 153 && g == 255 && b == 153) {
				enemies[nEnemy] = createEnemy(x, y, enemyTest, NORMAL);
				++nEnemy;
			}

			if(ntile+4 >= sizeT) { //ntile + no.of unique tiles+1
				sizeT += 100;
				tiles = (Tile *)realloc(tiles, sizeof(Tile)*sizeT);
				fprintf(stderr,"Reallocated Tiles total size: %ld\n", sizeof(Tile)*sizeT);
			}
			if(nEnemy+1 >= sizeE) {
				sizeE += 10;
				enemies = (Enemy *)realloc(enemies, sizeof(Enemy)*sizeE);
				fprintf(stderr,"Reallocated Enemies total size: %ld\n", sizeof(Enemy)*sizeE);
			}
		}

		tiles = (Tile *)realloc(tiles, sizeof(Tile)*ntile);
		enemies = (Enemy *)realloc(enemies, sizeof(Enemy)*nEnemy);
		fprintf(stderr, "Tiles trim size: %ld\n", sizeof(Tile)*ntile);
		fprintf(stderr, "Enemies trim size: %ld\n", sizeof(Enemy)*nEnemy);

		printf("\nNo.of Tiles: %d\n", ntile);
		printf("\nNo.of Enemies: %d\n", nEnemy);
		fflush(stdout);

	//create tilemap from da loaded data
	tilemap.tiles = tiles;
	tilemap.nTiles = ntile;

	Level lvl;
	lvl.bg = loadTexture(bg);
	lvl.enemies = enemies;
	lvl.nEnemies = nEnemy;
	lvl.map = tilemap;

	SOIL_free_image_data(bitmap);

	return lvl;
}

void freelvl(Level lvl) {
	if(lvl.map.tiles) {
		free(lvl.map.tiles);
	}
	if(lvl.enemies) {
		free(lvl.enemies);
	}
	printf("Level Destroyed.\n");
}
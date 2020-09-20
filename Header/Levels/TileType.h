#pragma once

#define TILE_SIZE	32
#define MAP_WIDTH	100
#define MAP_HEIGHT	19

enum class TILE_TYPE {
	EMPTY = 0,
	BLOCK, // non destructible tiles
	INVISIBLE_BLOCK,
	CLOUD_1,
	CLOUD_2,
	CLOUD_3,
	WATER,
	COUNT
};
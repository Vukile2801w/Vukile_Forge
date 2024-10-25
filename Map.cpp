#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map() {
}

Map::~Map() {

}

void Map::Load_Map(std::string path, int size_x, int size_y)
{
	char tile;
	std::fstream map_file;
	map_file.open(path);

	for (int y = 0; y < size_y; y++) {
		for (int x = 0; x < size_x; x++) {
			map_file.get(tile);
			Game::Add_Tile(atoi(&tile), x * 32, y * 32);
			map_file.ignore();
		}
	}
}

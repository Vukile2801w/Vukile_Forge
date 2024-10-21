#pragma once
#include "Game.h"


class Map
{
public:
	Map();
	~Map();

	void Load_Map(int arr[31][57]);
	void Draw_Map();

private:

	SDL_Rect src_rect, dest_rect;
	SDL_Texture* dirt;
	SDL_Texture* water;
	SDL_Texture* grass;

	int map[31][57];


};


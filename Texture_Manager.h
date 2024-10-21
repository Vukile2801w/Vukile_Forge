#pragma once
#include "Game.h"

class Texture_Manager
{
public:
	static SDL_Texture* Load_Texture(const char* file_name);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);

};


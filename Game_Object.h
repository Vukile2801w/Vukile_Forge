#pragma once
#include "Game.h" 

class Game_Object
{
public:
	Game_Object(const char* texturesheet, int x, int y);
	~Game_Object();

	void Update();
	void Render();

private:
	int x_pos;
	int y_pos;

	SDL_Texture* obj_texture;
	SDL_Rect src_rect, dest_rect;
	SDL_Renderer* renderer;


};


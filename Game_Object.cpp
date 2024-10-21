#include "Game_Object.h"
#include "Texture_Manager.h"

Game_Object::Game_Object(const char* texturesheet, int x, int y){
	

	obj_texture = Texture_Manager::Load_Texture(texturesheet);

	x_pos = x;
	y_pos = y;

}

Game_Object::~Game_Object(){

}


void Game_Object::Update() {
	
	x_pos++;
	y_pos++;

	src_rect.h = 16;
	src_rect.w = 16;
	src_rect.x = 0;
	src_rect.y = 0;

	dest_rect.x = x_pos;
	dest_rect.y = y_pos;
	dest_rect.w = src_rect.w * 4;
	dest_rect.h = src_rect.h * 4;

}

void Game_Object::Render() {
	SDL_RenderCopy(Game::renderer, obj_texture, &src_rect, &dest_rect);
}
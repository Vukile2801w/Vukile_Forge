#pragma once
#include "ECS.h"
#include "Components.h"
#include "SDL.h"

class Tile_Component : public Component
{
public:
	Transform_Component* transform;
	Sprite_Component* sprite;

	SDL_Rect tile_rect;
	int tile_id;
	char* path;

	Tile_Component() = default;
	Tile_Component(int x, int y, int w, int h, int id) {
		tile_rect.x = x;
		tile_rect.y = y;

		tile_rect.w = w;
		tile_rect.h = h;

		tile_id = id;

		switch (tile_id)
		{
			case 0:
				path = "Assets/Tile_Map/water.png";
				break;

			case 1:
				path = "Assets/Tile_Map/dirt.png";
				break;
		
			case 2:
				path = "Assets/Tile_Map/grass.png";
				break;

		default:
			break;
		}
	}

	void init() override {
		entity->Add_Component<Transform_Component>(tile_rect.x, tile_rect.y, tile_rect.w, tile_rect.h, 1);
		transform = &entity->get_Component <Transform_Component>();
		
		entity->Add_Component<Sprite_Component>(path);
		sprite = &entity->get_Component<Sprite_Component>();
	}

private:

};

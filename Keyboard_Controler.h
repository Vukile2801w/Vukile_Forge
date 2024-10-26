#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"


class Keyboard_Controler : public Component
{
public:
	Transform_Component* transform;
	Sprite_Component* sprite;

	void init() override {
		transform = &entity->get_Component<Transform_Component>();
		sprite = &entity->get_Component<Sprite_Component>();
	}

	void update() override {

		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
				case SDLK_w:
					transform->velocity.y = -1;
					sprite->Play("Idle");
					break;

				case SDLK_s:
					transform->velocity.y = 1;
					sprite->Play("Idle");
					break;

				case SDLK_a:
					transform->velocity.x = -1;
					sprite->Play("Idle");
					break;

				case SDLK_d:
					transform->velocity.x = 1;
					sprite->Play("Idle");
					break;

				case SDLK_ESCAPE:
					break;

				default:
					break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("Dying");
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Dying");
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Dying");
				break;
				 
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Dying");
				break;

			default:
				sprite->Play("Dying");
				break;
			}
		}

	}

private:

};


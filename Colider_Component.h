#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class Colider_Component : public Component
{
public:
	SDL_Rect colider;
	std::string tag;

	Transform_Component* transform;

	Colider_Component() {

	}

	Colider_Component(std::string t) {
		tag = t;
	}

	void init() override {
		if (!entity->has_component<Transform_Component>()) {
			entity->Add_Component<Transform_Component>();
		}

		transform = &entity->get_Component<Transform_Component>();

		Game::colliders.push_back(this);
	}

	void update() override {
		colider.x = static_cast<int>(transform->postion.x);
		colider.y = static_cast<int>(transform->postion.y);

		// Osiguraj da koristiš transformaciju koja se koristi za stvaranje zida
		colider.w = static_cast<int>(transform->width * transform->scale);
		colider.h = static_cast<int>(transform->height * transform->scale);
	}

};


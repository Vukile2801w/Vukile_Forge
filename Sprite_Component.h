// Sprite_Component.h
#pragma once
#include "Components.h"
#include "SDL.h"
#include "Transform_Component.h"

class Sprite_Component : public Component {
private:
    Transform_Component* transform;
    SDL_Texture* texture;
    SDL_Rect src_rect, dest_rect;

public:

    Sprite_Component() = default;

    Sprite_Component(const char* path) {
        texture = Texture_Manager::Load_Texture(path);
    }

    void init() override {
        // Povezivanje sa Transform_Component
        transform = &entity->get_Component<Transform_Component>();

        src_rect.x = 0;
        src_rect.y = 0;
        src_rect.w = transform->width;
        src_rect.h = transform->height;

        // Inicijalno postavljanje dimenzija dest_rect
        dest_rect.w = transform->width * transform->scale;
        dest_rect.h = transform->height * transform->scale;
    }

    void update() override {
        // Podesi poziciju i veličinu dest_rect prema transformaciji
        dest_rect.x = static_cast<int>(transform->postion.x);
        dest_rect.y = static_cast<int>(transform->postion.y);
        dest_rect.w = transform->width * transform->scale;
        dest_rect.h = transform->height * transform->scale;
    }

    void draw() override {
        Texture_Manager::Draw(texture, src_rect, dest_rect);
    }
};

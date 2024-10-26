// Sprite_Component.h
#pragma once
#include "Components.h"
#include "SDL.h"
#include "Transform_Component.h"
#include "Texture_Manager.h"
#include "Animation.h"
#include <map>

class Sprite_Component : public Component {
private:
    Transform_Component* transform;
    SDL_Texture* texture;
    SDL_Rect src_rect, dest_rect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:

    int anim_index = 0;
    int current_frame;
    const char* anim_name;


    std::map<const char*, Animation> animations;


    Sprite_Component() = default;

    Sprite_Component(const char* path) {
        Set_Tex(path);
    }

    Sprite_Component(const char* path, bool is_Animated) {

        animated = is_Animated;

        Animation idle = Animation(0, 12, 100, Vector2(26, 60), Vector2(0, 0));
        Animation eat = Animation(1, 10, 100, Vector2(25, 61), Vector2(0, 61));
        Animation dying = Animation(2, 6, 150, Vector2(26, 59), Vector2(0, 122));

        animations.emplace("Idle", idle);
        animations.emplace("Eat", eat);
        animations.emplace("Dying", dying);


        Play("Idle");

        
        Set_Tex(path);
    }


    void Set_Tex(const char* path) {
        texture = Texture_Manager::Load_Texture(path);
        if (!texture) {
            std::cerr << "Failed to load texture: " << path << std::endl;
        }
    }


    void init() override {
        transform = &entity->get_Component<Transform_Component>();
        if (!transform) {
            std::cerr << "Failed to initialize Transform_Component." << std::endl;
            return;
        }
        src_rect.x = 0;
        src_rect.y = 0;
        src_rect.w = transform->width;
        src_rect.h = transform->height;
        dest_rect.w = transform->width * transform->scale;
        dest_rect.h = transform->height * transform->scale;
    }



    void update() override {
        if (animated) {
            // Izračunaj trenutni frejm prema brzini
            current_frame = static_cast<int>((SDL_GetTicks() / speed) % frames);

            // Podesi src_rect.x tako da bude precizno pomeren na odgovarajući frejm
            src_rect.x = src_rect.w * current_frame + animations[anim_name].offset_anim.x;
        }

        // Ažuriraj y koordinate prema indeksu animacije
        src_rect.y = anim_index * src_rect.h;

        // Podesi poziciju i veličinu dest_rect prema transformaciji
        dest_rect.x = static_cast<int>(transform->postion.x);
        dest_rect.y = static_cast<int>(transform->postion.y);
        dest_rect.w = static_cast<int>(transform->width * transform->scale);
        dest_rect.h = static_cast<int>(transform->height * transform->scale);
    }

    void draw() override {
        Texture_Manager::Draw(texture, src_rect, dest_rect);
    }

    void Play(const char* anim_name) {
        auto it = animations.find(anim_name);
        if (it != animations.end()) {
            frames = it->second.frames;
            anim_index = it->second.index;
            speed = it->second.speed;

            // Postavi širinu i visinu jednog frejma animacije
            src_rect.w = it->second.size_frame.x;
            src_rect.h = it->second.size_frame.y;

            // Postavi ofset animacije
            src_rect.x = it->second.offset_anim.x;
            src_rect.y = it->second.offset_anim.y;

            // Resetuj početnu poziciju da izbegnemo klizanje
            current_frame = 0;
        }
        else {
            std::cerr << "Animation not found: " << anim_name << std::endl;
        }
    }



};

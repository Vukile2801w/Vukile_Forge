#include <string> // Dodaj ovu liniju na početak

class Tile_Component : public Component {
public:
    Transform_Component* transform;
    Sprite_Component* sprite;

    SDL_Rect tile_rect;
    int tile_id;
    std::string path; // Promeni tip na std::string

    Tile_Component() = default;

    Tile_Component(int x, int y, int w, int h, int id) {
        tile_rect.x = x;
        tile_rect.y = y;
        tile_rect.w = w;
        tile_rect.h = h;
        tile_id = id;

        switch (tile_id) {
        case 0:
            path = "Assets/Tile_Map/water.png"; // Jednostavno dodeli string
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
        entity->Add_Component<Transform_Component>((float)tile_rect.x, (float)tile_rect.y, (float)tile_rect.w, (float)tile_rect.h, 1);
        transform = &entity->get_Component<Transform_Component>();

        entity->Add_Component<Sprite_Component>(path.c_str()); // Koristi c_str() za dobivanje C-style stringa
        sprite = &entity->get_Component<Sprite_Component>();
    }


    void update() override {
        tile_rect.x = static_cast<int>(transform->postion.x);
        tile_rect.y = static_cast<int>(transform->postion.y);

        // Proveri da li koristiš scale ispravno
        tile_rect.w = static_cast<int>(transform->width * transform->scale);
        tile_rect.h = static_cast<int>(transform->height * transform->scale);
    }



private:
};

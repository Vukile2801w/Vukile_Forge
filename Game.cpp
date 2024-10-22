#include "Game.h"
#include "Texture_Manager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "Colision.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager; // Ispravi ovu liniju

std::vector<Colider_Component*> Game::colliders;

Entity& wall(manager.Add_Entity());

Entity& tile0(manager.Add_Entity());
Entity& tile1(manager.Add_Entity());
Entity& tile2(manager.Add_Entity());
Entity& tile3(manager.Add_Entity());

Entity& Player(manager.Add_Entity()); // Ispravi ovu liniju


Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int width, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 214, 200, 255, 255);
        }

        isRunning = true;
    }


    map = new Map();

    tile0.Add_Component<Tile_Component>(200, 200, 32, 32, 0);
    tile1.Add_Component<Tile_Component>(232, 200, 32, 32, 1);
    tile2.Add_Component<Tile_Component>(200, 232, 32, 32, 2);
    tile3.Add_Component<Tile_Component>(232, 232, 32, 32, 1);

    tile1.Add_Component<Colider_Component>("dirt");
    tile2.Add_Component<Colider_Component>("grass");
    tile3.Add_Component<Colider_Component>("dirt");


    Player.Add_Component<Transform_Component>(0, 0, 14, 6, 5);
    Player.Add_Component<Sprite_Component>("Assets/Player01.png");
    Player.Add_Component<Colider_Component>("player");
    Player.Add_Component<Keyboard_Controler>();

    
    wall.Add_Component<Transform_Component>(300, 300, 32, 32, 1);
    wall.Add_Component<Sprite_Component>("Assets/Tile_Map/dirt.png");
    wall.Add_Component<Colider_Component>("wall");
    
}

void Game::handleEvents() {


    SDL_PollEvent(&event);


    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;

    case SDL_WINDOW_MAXIMIZED:
        SDL_MaximizeWindow(window);
        break;

    case SDL_WINDOW_MINIMIZED:
        SDL_MinimizeWindow(window);
        break;

    default:
        break;
    }
}

void Game::update() {
    cnt++;

    manager.refresh();
    manager.update();

    Colider_Component& player_colider = Player.get_Component<Colider_Component>();

    for (auto& e : manager.get_entities()) {
        if (e->has_component<Colider_Component>()) {
            Colider_Component& e_colider = e->get_Component<Colider_Component>();

            if (e_colider.tag != player_colider.tag) {
                bool is_colided = Collision::AABB(player_colider.colider, e_colider.colider);
                if (is_colided) {
                    // Reaguj na koliziju (npr. resetuj poziciju igrača, ili onemogući kretanje)
                    Player.get_Component<Transform_Component>().velocity *= Vector2(-1, -1);
                }
            }
        }
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    //map->Draw_Map();


    manager.draw();


    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

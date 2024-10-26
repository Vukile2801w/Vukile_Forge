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
Entity& Player(manager.Add_Entity()); // Ispravi ovu liniju

enum group_lables : std::size_t {
    groupMap,
    groupPlayer,
    groupEnemies,
};

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

    Map::Load_Map("Assets/Tile_Map/map.map", 60, 34);
    

    Player.Add_Component<Transform_Component>(0, 0, 60, 27, 1.6);
    Player.Add_Component<Sprite_Component>("Assets/Player/Player_Anim.png", true);
    Player.Add_Component<Colider_Component>("player");
    Player.Add_Group(groupPlayer);
    Player.Add_Component<Keyboard_Controler>();
    
    wall.Add_Component<Transform_Component>(300, 300, 32, 32, 1);
    wall.Add_Component<Sprite_Component>("Assets/Tile_Map/dirt.png");
    wall.Add_Component<Colider_Component>("wall");
    wall.Add_Group(groupMap);
    
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

    for (auto cc : colliders) {

        Collision::AABB(Player.get_Component<Colider_Component>(), *cc);
        
    }
}

auto& tiles(manager.get_Group(groupMap));
auto& players(manager.get_Group(groupPlayer));
auto& enemies(manager.get_Group(groupEnemies));


void Game::render() {
    SDL_RenderClear(renderer);


    for (auto& t : tiles) {
        t->draw();
    }

    for (auto& p : players) {
        p->draw();
    }

    for (auto& e : enemies) {
        e->draw();
    }


    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::Add_Tile(int id, int x, int y)
{
    auto& tile(manager.Add_Entity());
    tile.Add_Component<Tile_Component>(x, y, 32, 32, id);
    tile.Add_Group(groupMap);
}

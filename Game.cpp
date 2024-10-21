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

Entity& wall = manager.Add_Entity();
Entity& Player = manager.Add_Entity(); // Ispravi ovu liniju

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

    Player.Add_Component<Transform_Component>(2);
    Player.Add_Component<Sprite_Component>("Assets/Player01.png");
    Player.Add_Component<Colider_Component>("player");
    Player.Add_Component<Keyboard_Controler>();


    wall.Add_Component<Transform_Component>(300, 300, 300, 20, 1);
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
   
    if (Collision::AABB(Player.get_Component<Colider_Component>().colider, wall.get_Component<Colider_Component>().colider)) {
        Player.get_Component<Transform_Component>().scale += .1;
        std::cout << "Wall Hit!" << std::endl;
    }

}

void Game::render() {
    SDL_RenderClear(renderer);

    map->Draw_Map();


    manager.draw();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

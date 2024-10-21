#include "Texture_Manager.h"


SDL_Texture* Texture_Manager::Load_Texture(const char* file_name) {
    SDL_Surface* temp_surface = IMG_Load(file_name);
    if (!temp_surface) {
        std::cout << "Failed to load surface: " << file_name << ";   SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    if (!tex) {
        std::cout << "Failed to create texture from surface: " << file_name << ";   SDL_Error: " << SDL_GetError() << std::endl;
    }

    return tex;
}


void Texture_Manager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

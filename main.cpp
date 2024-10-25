#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 165;
	const int frame_delay = 1000 / FPS;

	Uint32 frame_start;
	int frame_time;
	
	game = new Game();
	game->init("GameWindow", 1900, 1000, false);

	while (game->running())
	{
		frame_start = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frame_time = SDL_GetTicks() - frame_start;

		if (frame_delay > frame_time) {
			SDL_Delay(frame_delay - frame_time);
		}

		
	}

	game->clean();
	return 0;
}

#pragma once
#include <SDL.h>

class Colider_Component;

class Collision
{
public:
	
	static bool AABB(const SDL_Rect& rect_A, const SDL_Rect& rect_B);
	static bool AABB(const Colider_Component& colA, const Colider_Component& colB);


private:

};

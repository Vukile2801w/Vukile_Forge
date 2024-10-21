#pragma once
#include "Colision.h"

bool Collision::AABB(const SDL_Rect& rect_A, const SDL_Rect& rect_B) {
	if (
		rect_A.x + rect_A.w >= rect_B.x &&
		rect_B.x + rect_B.w >= rect_A.x &&
		rect_A.y + rect_A.h >= rect_B.y &&
		rect_B.y + rect_B.h >= rect_A.y
		) {
		return true;
	}

	return false;
}
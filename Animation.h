#pragma once

struct Animation
{
	int index;
	int frames;
	int speed;
	Vector2 size_frame;
	Vector2 offset_anim;
	
	Animation() {}

	Animation(int i, int f, int s, Vector2 size, Vector2 offset) {
		index = i;
		frames = f;
		speed = s;

		size_frame = size;
		offset_anim = offset;
	}
};
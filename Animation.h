#pragma once

struct Animation
{
	int index;
	int frames;
	int speed;

	size_t id;

	Vector2 size_frame;
	Vector2 offset_anim;

	bool is_playing;

	Animation() {}

	Animation(int i, int f, int s, Vector2 size, Vector2 offset) {
		index = i;
		frames = f;
		speed = s;

		id = Get_New_Animation_ID();

		size_frame = size;
		offset_anim = offset;
	}


	inline size_t Get_New_Animation_ID() {
		static size_t lastID = 0u;
		return lastID++;
	}

};
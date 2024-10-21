#pragma once
#include "Components.h"
#include "Vector2.h"

class Transform_Component : public Component {
public:

    Vector2 postion;
    Vector2 velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 1;

    Transform_Component(int sc) {
        postion.x = 0.0f;
        postion.y = 0.0f;
        
        scale = sc;
    }

    Transform_Component(float x, float y) {
        postion.x = x;
        postion.y = y;
    }

    Transform_Component(float x, float y, int h, int w, int scale) {
        postion.x = x;
        postion.y = y;

        height = h;
        width = w;
        this->scale = scale;
    }

    Transform_Component() {
        postion.x = 0.0f;
        postion.y = 0.0f;
    }

    



    int x() const { return postion.x; }
    int y() const { return postion.y; }

    void init() override {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override {
        postion.x += velocity.x * speed;
        postion.y += velocity.y * speed;

        
    }

};

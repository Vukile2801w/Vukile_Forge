#pragma once
#include "Components.h"
#include "Vector2.h"

class Transform_Component : public Component {
public:

    Vector2 postion;
    Vector2 velocity;

    int height = 32;
    int width = 32;
    float scale = 1;

    int speed = 3;

    Transform_Component(int sc) {
        postion.Zero();
        
        scale = sc;
    }

    Transform_Component(float x, float y) {
        postion.x = x;
        postion.y = y;
    }

    Transform_Component(float x, float y, int h, int w, float scale) {
        postion.x = x;
        postion.y = y;

        height = h;
        width = w;
        this->scale = scale;
    }

    Transform_Component() {
        postion.Zero();
    }

    



    int x() const { return postion.x; }
    int y() const { return postion.y; }

    void init() override {
        velocity.Zero();
    }

    void update() override {
        postion.x += velocity.x * speed;
        postion.y += velocity.y * speed;

        
    }

};

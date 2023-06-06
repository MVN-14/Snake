#pragma once

#include "TexturedRect.hpp"

class Food {
public:
    Food(SDL_Renderer *renderer, int x = 0, int y = 0);

    void setPosition(int x, int y);
    void render();
    TexturedRect const &getRect() const;

private:
    TexturedRect rect_;
};
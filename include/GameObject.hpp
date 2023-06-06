#pragma once

#include "TexturedRect.hpp"
#include <SDL2/SDL.h>

class GameObject {
public:
    GameObject();
    GameObject(SDL_Renderer *renderer, const char *spritepath);

    void Update();
    void Render();
    TexturedRect &GetSprite() {
        return *sprite_;
    }

private:
    TexturedRect *sprite_{nullptr};
    SDL_Renderer *renderer_{nullptr};
};

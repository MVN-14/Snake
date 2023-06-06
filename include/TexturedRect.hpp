#pragma once

#include <SDL2/SDL.h>

class TexturedRect {
public:
    TexturedRect(SDL_Renderer *renderer, const char *filepath);
    ~TexturedRect();

    void render();

    void setPosition(int x, int y);
    void setX(int x);
    void setY(int y);
    void setDimensions(int w, int h);
    void setW(int w);
    void setH(int h);

    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;

    bool isInRange(int xMin, int xMax, int yMin, int yMax) const;
    bool isColliding(TexturedRect const &testRect) const;

    SDL_Rect const &getRect() const;

private:
    SDL_Rect rect_;
    SDL_Texture *texture_;
    SDL_Renderer *renderer_;
};
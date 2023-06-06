#pragma once

#include "TexturedRect.hpp"
#include <memory>
#include <vector>

constexpr int HEAD_SIZE = 50;

enum class SnakeDirection {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
public:
    Snake(SDL_Renderer *renderer, int x = 0, int y = 0);

    void render();
    void update();
    void setDirection(SnakeDirection const &direction);
    void setHeadPosition(int x, int y);
    void reset(int x = 0, int y = 0);
    void onEatFood();

    SnakeDirection const &getDirection();
    TexturedRect const &getHead() const;

private:
    SDL_Renderer *renderer_{nullptr};

    bool isEating_{false};
    std::vector<std::shared_ptr<TexturedRect>> rects_{};
    SnakeDirection direction_{SnakeDirection::NONE};
};
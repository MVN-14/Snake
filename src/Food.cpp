#include "Food.hpp"

Food::Food(SDL_Renderer *renderer, int x, int y) : rect_(renderer, "../images/Food.bmp") {
    rect_.setDimensions(50, 50);
    rect_.setPosition(x, y);
}

void Food::setPosition(int x, int y) {
    rect_.setX(x);
    rect_.setY(y);
}

void Food::render() {
    rect_.render();
}

TexturedRect const &Food::getRect() const {
    return rect_;
}
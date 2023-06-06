#include "TexturedRect.hpp"
#include "ResourceManager.hpp"

TexturedRect::TexturedRect(SDL_Renderer *renderer, const char *filepath)
    : renderer_(renderer) {

    SDL_Surface *surface = ResourceManager::GetInstance().GetSurface(filepath);
    texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
}

TexturedRect::~TexturedRect() {
    SDL_DestroyTexture(texture_);
}

void TexturedRect::setPosition(int x, int y) {
    setX(x);
    setY(y);
}

void TexturedRect::setX(int x) {
    rect_.x = x;
}

void TexturedRect::setY(int y) {
    rect_.y = y;
}

void TexturedRect::setDimensions(int w, int h) {
    rect_.w = w;
    rect_.h = h;
}

void TexturedRect::setW(int w) {
    rect_.w = w;
}

void TexturedRect::setH(int h) {
    rect_.h = h;
}

void TexturedRect::render() {
    SDL_RenderCopy(renderer_, texture_, NULL, &rect_);
}

int TexturedRect::getX() const {
    return rect_.x;
}

int TexturedRect::getY() const {
    return rect_.y;
}

int TexturedRect::getW() const {
    return rect_.w;
}

int TexturedRect::getH() const {
    return rect_.h;
}

bool TexturedRect::isInRange(int xMin, int xMax, int yMin, int yMax) const {
    return rect_.x >= xMin && rect_.x <= xMax && rect_.y >= yMin && rect_.y <= yMax;
}

bool TexturedRect::isColliding(TexturedRect const &testRect) const {
    return SDL_HasIntersection(&rect_, &testRect.getRect()) == SDL_TRUE;
}

SDL_Rect const &TexturedRect::getRect() const {
    return rect_;
}

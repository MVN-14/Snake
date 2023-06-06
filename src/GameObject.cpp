#include "GameObject.hpp"
#include "TexturedRect.hpp"

GameObject::GameObject() {
}

GameObject::GameObject(SDL_Renderer *renderer, const char *spritepath)
    : renderer_(renderer) {
    sprite_ = new TexturedRect(renderer_, spritepath);
}

void GameObject::Update() {
}

void GameObject::Render() {
    if (sprite_) {
        sprite_->render();
    }
}
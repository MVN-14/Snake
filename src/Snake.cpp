#include "Snake.hpp"

Snake::Snake(SDL_Renderer *renderer, int x, int y) : renderer_(renderer) {
    std::shared_ptr<TexturedRect> head =
        std::make_shared<TexturedRect>(renderer_, "../images/Player.bmp");
    head->setPosition(x, y);
    head->setDimensions(HEAD_SIZE, HEAD_SIZE);
    rects_.push_back(head);

    // std::shared_ptr<TexturedRect> temp =
    //     std::make_shared<TexturedRect>(renderer_, "../images/Player.bmp");
    // temp->setPosition(x + 50, y);
    // temp->setDimensions(HEAD_SIZE, HEAD_SIZE);
    // rects_.push_back(temp);
}

void Snake::render() {
    for (auto &rect : rects_) {
        rect->render();
    }
}

void Snake::update() {
    if (direction_ == SnakeDirection::NONE) {
        return;
    }

    // Keep track of last head position
    int lastX = rects_[0]->getX();
    int lastY = rects_[0]->getY();

    // move head
    if (SnakeDirection::RIGHT == direction_) {
        rects_[0]->setX(rects_[0]->getX() + HEAD_SIZE);
    }
    else if (SnakeDirection::UP == direction_) {
        rects_[0]->setY(rects_[0]->getY() - HEAD_SIZE);
    }
    else if (SnakeDirection::LEFT == direction_) {
        rects_[0]->setX(rects_[0]->getX() - HEAD_SIZE);
    }
    else if (SnakeDirection::DOWN == direction_) {
        rects_[0]->setY(rects_[0]->getY() + HEAD_SIZE);
    }

    for (int i = 1; i < rects_.size(); ++i) {
        int tempX = rects_[i]->getX();
        int tempY = rects_[i]->getY();
        rects_[i]->setPosition(lastX, lastY);
        lastX = tempX;
        lastY = tempY;
    }
    if (isEating_) {
        std::shared_ptr<TexturedRect> newRect =
            std::make_shared<TexturedRect>(renderer_, "../images/Player.bmp");

        newRect->setDimensions(HEAD_SIZE, HEAD_SIZE);
        newRect->setPosition(lastX, lastY);
        rects_.push_back(newRect);
        isEating_ = false;
    }
}

void Snake::setDirection(SnakeDirection const &direction) {
    direction_ = direction;
}

void Snake::setHeadPosition(int x, int y) {
    rects_[0]->setX(x);
    rects_[0]->setY(y);
}

void Snake::reset(int x, int y) {
    std::shared_ptr<TexturedRect> head = rects_[0];
    rects_.clear();
    rects_.push_back(head);
    setHeadPosition(x, y);
    direction_ = SnakeDirection::NONE;
}

void Snake::onEatFood() {
    isEating_ = true;
}

SnakeDirection const &Snake::getDirection() {
    return direction_;
}

TexturedRect const &Snake::getHead() const {
    return *rects_[0];
}
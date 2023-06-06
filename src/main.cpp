#include <SDL2/SDL.h>

#include <iostream>
#include <random>

#include "Food.hpp"
#include "SDLApp.hpp"
#include "Snake.hpp"

// screen width and heightshould be multiples of the snake head size
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 650;
constexpr int GRID_WIDTH = SCREEN_WIDTH / HEAD_SIZE;
constexpr int GRID_HEIGHT = SCREEN_HEIGHT / HEAD_SIZE;

int randomNumberInRange(int min, int max) {
    static std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distr(min, max);
    int rand = distr(gen);
    return rand;
}

void SetValidFoodPosition(Food &food, Snake &snake) {
    int foodX{0}, foodY{0};
    do {
        foodX = randomNumberInRange(0, GRID_WIDTH - 1) * HEAD_SIZE;
        foodY = randomNumberInRange(0, GRID_HEIGHT - 1) * HEAD_SIZE;
    } while (snake.getHead().getX() == foodX && snake.getHead().getY() == foodY);

    std::cout << "Setting new food location at " << foodX << ", " << foodY << '\n';
    food.setPosition(foodX, foodY);
}

int main(int, char **) {
    SDLApp app("Snake",
               SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED,
               SCREEN_WIDTH,
               SCREEN_HEIGHT,
               60);

    Snake snake(&app.GetRenderer(), GRID_WIDTH / 2 * 50, GRID_HEIGHT / 2 * 50);
    Food food(&app.GetRenderer());
    SetValidFoodPosition(food, snake);

    app.SetEventCallback([&] {
        static int frameCount = 0;
        static int framesPerMove = 10;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app.Stop();
            }

            if (event.type == SDL_KEYDOWN) {
                Uint8 const *keyboardState = SDL_GetKeyboardState(NULL);
                if (keyboardState[SDL_SCANCODE_RIGHT] &&
                    snake.getDirection() != SnakeDirection::LEFT) {
                    snake.setDirection(SnakeDirection::RIGHT);
                }
                else if (keyboardState[SDL_SCANCODE_LEFT] &&
                         snake.getDirection() != SnakeDirection::RIGHT) {
                    snake.setDirection(SnakeDirection::LEFT);
                }
                else if (keyboardState[SDL_SCANCODE_UP] &&
                         snake.getDirection() != SnakeDirection::DOWN) {
                    snake.setDirection(SnakeDirection::UP);
                }
                else if (keyboardState[SDL_SCANCODE_DOWN] &&
                         snake.getDirection() != SnakeDirection::UP) {
                    snake.setDirection(SnakeDirection::DOWN);
                }
            }
        }

        ++frameCount;
        if (frameCount > framesPerMove) {
            frameCount = 0;
            snake.update();
            if (!snake.getHead().isInRange(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT)) {
                snake.reset(GRID_WIDTH / 2 * HEAD_SIZE, GRID_HEIGHT / 2 * HEAD_SIZE);
                SetValidFoodPosition(food, snake);
            }

            if (snake.getHead().isColliding(food.getRect())) {
                snake.onEatFood();
                SetValidFoodPosition(food, snake);
            }
        }
    });

    app.SetRenderCallback([&] {
        SDL_SetRenderDrawColor(&app.GetRenderer(), 0, 255, 0, 255);
        snake.render();
        food.render();
    });

    app.RunLoop();

    return 0;
}

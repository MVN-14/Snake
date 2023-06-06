#include "SDLApp.hpp"
#include <SDL2/SDL.h>
#include <iostream>

SDLApp::SDLApp(const char *title, int x, int y, int w, int h, int fps)
    : width_(w), height_(h), maxFps_(fps) {
    if (0 > SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init() failed: " << SDL_GetError() << '\n';
        return;
    }

    window_ = SDL_CreateWindow(title,
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width_,
                               height_,
                               SDL_WINDOW_SHOWN);

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    isRunning_ = true;
}

SDLApp::~SDLApp() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void SDLApp::SetEventCallback(std::function<void(void)> func) {
    keyboardState_ = SDL_GetKeyboardState(NULL);

    eventCallback_ = func;
}

void SDLApp::SetRenderCallback(std::function<void(void)> func) {
    renderCallback_ = func;
}

void SDLApp::RunLoop() {
    while (isRunning_) {
        Uint32 frameStartTicks{SDL_GetTicks()};

        eventCallback_();
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer_);

        renderCallback_();

        SDL_RenderPresent(renderer_);

        // Frame capping
        Uint32 elapsedTicks = SDL_GetTicks() - frameStartTicks;
        Uint32 ticksPerFrame = 1000 / maxFps_;
        if (elapsedTicks < ticksPerFrame) {
            SDL_Delay(ticksPerFrame - elapsedTicks);
        }
    }
}

void SDLApp::Stop() {
    isRunning_ = false;
}

Uint8 const *SDLApp::GetKeyboardState() {
    return keyboardState_;
}

int SDLApp::GetWindowHeight() {
    return height_;
}

int SDLApp::GetWindowWidth() {
    return width_;
}

bool SDLApp::GetIsRunning() {
    return isRunning_;
}

SDL_Renderer &SDLApp::GetRenderer() const {
    return *renderer_;
}

void SDLApp::SetMaxFPS(int fps) {
    maxFps_ = fps;
}
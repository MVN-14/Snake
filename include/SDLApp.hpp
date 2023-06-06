#pragma once

#include <SDL2/SDL.h>
#include <functional>

class SDLApp {
public:
    SDLApp(const char *title, int x, int y, int w, int h, int fps = 30);
    ~SDLApp();

    void SetEventCallback(std::function<void(void)> func);
    void SetRenderCallback(std::function<void(void)> func);
    void SetMaxFPS(int fps);
    void RunLoop();
    void Stop();
    int GetMouseX();
    int GetMouseY();
    Uint8 const *GetKeyboardState();
    int GetWindowWidth();
    int GetWindowHeight();
    bool GetIsRunning();
    SDL_Renderer &GetRenderer() const;

private:
    SDL_Window *window_{nullptr};
    SDL_Renderer *renderer_{nullptr};

    std::function<void(void)> eventCallback_{nullptr};
    std::function<void(void)> renderCallback_{nullptr};
    bool isRunning_{false};
    const Uint8 *keyboardState_;
    int width_{0};
    int height_{0};
    int maxFps_{0};
};
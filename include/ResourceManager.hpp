#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>

class ResourceManager {
public:
    std::unordered_map<const char *, SDL_Surface *> surfaces_;

    static ResourceManager &GetInstance();
    SDL_Surface *GetSurface(const char *filepath);

private:
    ResourceManager();
    ~ResourceManager();
    ResourceManager(ResourceManager const &) = delete;
    ResourceManager operator=(ResourceManager const &rhs) = delete;
};

#include "ResourceManager.hpp"

ResourceManager &ResourceManager::GetInstance() {
    static ResourceManager *instance = new ResourceManager();
    return *instance;
}

SDL_Surface *ResourceManager::GetSurface(const char *filepath) {
    auto search = surfaces_.find(filepath);
    if (search != surfaces_.end()) {
        return surfaces_[filepath];
    } else {
        SDL_Surface *surface = SDL_LoadBMP(filepath);
        surfaces_.insert(std::make_pair(filepath, surface));
        return surfaces_[filepath];
    }
    return nullptr;
}

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

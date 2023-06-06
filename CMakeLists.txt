cmake_minimum_required(VERSION 3.0.0)
project(Snake VERSION 0.1.0)

include_directories(include)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/TexturedRect.cpp
    src/ResourceManager.cpp 
    src/GameObject.cpp
    src/SDLApp.cpp
    src/Snake.cpp
    src/Food.cpp)

target_link_libraries(
    Snake
    SDL2)

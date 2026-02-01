#pragma once
#include <vector>
#include <array>
#include <string>
#include <SDL2/SDL.h>
#include "Mesh.hpp"


class Window
{
private:
    int frametime;
public:
    void init(const int &w ,const int &h ,const int &frametime);
    void handle_inputs(bool &running, tf_vec &tranlation ,rot_vec &rotation);
    void close();
    void update();

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    std::array<int ,2> origin;
};


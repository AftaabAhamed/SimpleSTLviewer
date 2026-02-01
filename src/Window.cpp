#include <vector>
#include <array>
#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include "Mesh.hpp"
#include "Window.hpp"

void Window::init(const int &w ,const int &h, const int &frametime){
    
    Window::frametime = frametime;
    Window::width = w;
    Window::height = h;
    Window::origin = {w/2, h/2};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << "\n";
    }

    Window::window = SDL_CreateWindow("Viewer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        Window::width, Window::height, SDL_WINDOW_SHOWN);

    if (!Window::window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << "\n";
        SDL_Quit();
    }

    Window::renderer = SDL_CreateRenderer(Window::window, -1, SDL_RENDERER_ACCELERATED);
    if (!Window::renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(Window::window);
        SDL_Quit();
    }
}

void Window::update(){
    SDL_RenderPresent(Window::renderer);
    SDL_Delay(Window::frametime);
    SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Window::renderer);
}

void Window::close(){
    SDL_DestroyRenderer(Window::renderer);
    SDL_DestroyWindow(Window::window);
    SDL_Quit();
}

void Window::handle_inputs(bool &running, tf_vec &translation ,rot_vec &rotation){
    float scroll_sensitivity = 0.05f;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        else if (e.type == SDL_MOUSEWHEEL){
            translation.z += (float)(scroll_sensitivity*e.wheel.y);
            // std::cout << e.wheel.y <<std::endl;
        }
    }

    int mousex, mousey;
    Uint32 buttons = SDL_GetRelativeMouseState(&mousex, &mousey);
     
    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        float sensitivity = 0.005f; 
        
        rotation.y += (float)mousex * sensitivity;
        rotation.x += (float)mousey * sensitivity;
    }
}
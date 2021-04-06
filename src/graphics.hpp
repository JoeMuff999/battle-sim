/*
    a collection of graphics headers. first function is for sdl2 wrappers
*/
#include <SDL.h>
#include <iostream>

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

namespace Graphics
{
    bool initializeSDL(SDL_Window *&window, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    SDL_Surface *loadSurface(const SDL_Surface* screenSurface, const std::string path);
    bool shutdownSDL(SDL_Window *window);
};

#endif
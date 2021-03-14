/*
    a collection of graphics headers. first function is for sdl2 wrappers
*/
#include <SDL.h>
#include <iostream>

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

using namespace std;
bool initializeSDL(SDL_Window*& window, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{

    //The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else{
        window = SDL_CreateWindow("Battle Sim!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //unsuccessful window creation?
        if(window == NULL){
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            return false;
        }
        
    }
    //success
    return true;
}

bool shutdownSDL(SDL_Window* window)
{
    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();
}

#endif
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include "game.hpp"
#include "graphics.hpp"
using namespace std;

//Screen dimension constants

int main(int argc, char *args[])
{

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    SDL_Window *window = NULL;
    if (!Graphics::initializeSDL(window, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        cout << "SDL window creation failed " << endl;
        return 1;
    }
    //The surface contained by the window
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    //Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x77, 0x77, 0x77));
    Game game(window, screenSurface);
    //Update the surface
    SDL_UpdateWindowSurface(window);
    game.start();
    game.mainLoop();

    return 0;
}
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include "game.hpp"
#include "graphics.hpp"
using namespace std;

//Screen dimension constants

int main(int argc, char *args[])
{

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Window *window = NULL;
    if (!initializeSDL(window, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        cout << "SDL window creation failed " << endl;
        return 1;
    }
    //The surface contained by the window
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    //Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    Game game(window, screenSurface);
    //Update the surface
    SDL_UpdateWindowSurface(window);
    game.start();
    game.mainLoop();

    return 0;
}
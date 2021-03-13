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
    game.test_game(300,200);
    //Update the surface
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    game.cleanup();
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }
    shutdownSDL(window);
    cout << "hello world" << endl;
    return 0;
}
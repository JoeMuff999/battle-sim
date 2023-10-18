#include "graphics.hpp"

using namespace std;

bool Graphics::initializeSDL(SDL_Window *&window, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{

    //The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        window = SDL_CreateWindow("Battle Sim!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //unsuccessful window creation?
        if (window == NULL)
        {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            return false;
        }
    }
    //success
    return true;
}

SDL_Surface *Graphics::loadSurface(const SDL_Surface* screenSurface, const string imgPath)
{
    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* imageSurface = SDL_LoadBMP(imgPath.c_str());
    if(imageSurface == NULL)
    {
        cout << "Failed to load image " << imgPath << endl;
        return NULL;
    }
    optimizedSurface = SDL_ConvertSurface(imageSurface, screenSurface->format, 0);
    if(optimizedSurface == NULL)
    {
        cout << "Failed to optimize image " << imgPath <<endl;
        return imageSurface;
    }
    SDL_FreeSurface(imageSurface);
    //map cyan to be transparent. eventually change this to use some getTransparent() from the drawable
    uint32_t colorKey = SDL_MapRGB(optimizedSurface->format, 0x00, 0xFF, 0xFF);
    if(SDL_SetColorKey(optimizedSurface, SDL_TRUE, colorKey))
    {
        cout << "failed to set color key for " << imgPath << " " << SDL_GetError() << endl;
    }

    return optimizedSurface;
}

bool Graphics::shutdownSDL(SDL_Window *window)
{
    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();
	return 0;
}

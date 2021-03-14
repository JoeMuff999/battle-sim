#include "InputManager.hpp"
#include <iostream>

using namespace std; 

bool InputManager::handleInput(vector<Controllable*> controllables)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                cout << "QUITTING " <<endl;
                return false;
            case SDL_MOUSEBUTTONDOWN:
                Point point = {0, 0};
                SDL_GetMouseState(&point.x,&point.y);
                for(Controllable* controllable : controllables)
                {
                    controllable->handleInput(e, point);
                }
        }
    }
    return true;
}
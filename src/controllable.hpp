#include <SDL.h>
#include "point.hpp"
#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

class Controllable{
    public:
        virtual void handleInput(SDL_Event& e, Point& mousePosition) = 0;
};

#endif
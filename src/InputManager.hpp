#include <vector>
#include "controllable.hpp"

#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

namespace InputManager{
    extern bool handleInput(std::vector<Controllable*>);
}

#endif
#pragma once

#include "drawable.hpp"

class Background : Drawable {
public: 
    Point getPos() override {
        return Point{0, 0};
    }
};
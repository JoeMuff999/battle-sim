#pragma once

#include "point.hpp"
#include "rect.hpp"
#include <iostream>

//YAGNI: circular colliders?
//YAGNI: collider is locked to the agents true position (could do an offset, but this is how Unity does it)
//TODO: Why do we have StaticCollidable and MovingCollidable? Why not just use a boolean if you really need the difference?
class Collidable
{
protected:
    float _w;
    float _h;
    Vec2D _offset;
    virtual Vec2D getTruePosition() const = 0;

public:
    Collidable(float w, float h) {
        _w = w;
        _h = h;
        _offset = {0.0f, 0.0f};
    }

    Collidable(float w, float h, Vec2D offset) {
        _w = w;
        _h = h;
        _offset = offset;
    }

    virtual Rect2D getRect() const = 0;

    virtual bool isColliding(const Collidable& other) const = 0;
};

class StaticCollidable : public Collidable
{
public:
    StaticCollidable(float w, float h) : Collidable(w, h) {}

    StaticCollidable(float w, float h, Vec2D offset) : Collidable(w, h, offset) {}

    Rect2D getRect() const override {
        // TODO: this should only be done once, but since I have const everywhere 
        //I couldnt use a boolean to check if it was initialized 😪
        Vec2D currPos = getTruePosition();
        return {
            currPos.x + _offset.x,
            currPos.y + _offset.y,
            currPos.x + _offset.x + _w, 
            currPos.y + _offset.y + _h};
    }

    bool isColliding(const Collidable& other) const override {
        std::cout << "StaticCollidable::isColliding - Dont use this please" << std::endl;
        return false;
    }
};

class MovingCollidable : Collidable 
{
public:
    MovingCollidable(float w, float h) : Collidable(w, h) {}

    MovingCollidable(float w, float h, Vec2D offset) : Collidable(w, h, offset) {}

    Rect2D getRect() const override {
        Vec2D currPos = getTruePosition();
        const Rect2D myRect = {
            currPos.x + _offset.x,
            currPos.y + _offset.y,
            currPos.x + _offset.x + _w, 
            currPos.y + _offset.y + _h
        };
        return myRect;
    }

    /**
     * Is the RIGHT edge of r1 to the RIGHT of the LEFT edge of r2?
     * Is the LEFT edge of r1 to the LEFT of the RIGHT edge of r2?
     * Is the BOTTOM edge of r1 BELOW the TOP edge of r2?
     * Is the TOP edge of r1 ABOVE the BOTTOM edge of r2?
     * REMINDER that the coord system has x increasing from left to right, and y increasing from top to bottom
     * topLeft = (0,0), bottomRight = (1920,1080)
    */
    bool isColliding(const Collidable& other) const override {
        const Rect2D r1 = getRect();
        const Rect2D r2 = other.getRect();

        return r1.x2 >= r2.x1 && r1.x1 <= r2.x2 && r1.y2 >= r2.y1 && r1.y1 <= r2.y2;
    }
};
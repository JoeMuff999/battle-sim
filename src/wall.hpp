#pragma once

#include "collidable.hpp"
#include "drawable.hpp"
#include "drawableLinkedList.hpp"


class Wall : public StaticCollidable {
protected:
    const Vec2D pos;

public:
    Wall(float x, float y, float w, float h) : StaticCollidable(w, h), pos({x, y}) {}

    Wall(float x, float y, float w, float h, Vec2D offset) : StaticCollidable(w, h, offset), pos({x, y}) {}

    Vec2D getTruePosition() const override {
        return pos;
    }

};

class DrawableWall : public Wall, public Drawable {
private:
    const string CONFIG_PATH = "/config/wall";
    const Layer RENDER_LAYER = Layer::TERRAIN;

public:
    DrawableWall(float x, float y, float w, float h, Vec2D offset, LayeredDrawableList& drawableStore) : Wall(x, y, w, h, offset) {
        drawableStore.insert(this);
    } 

    Point getPos() override {
        return {(int)pos.x, (int)pos.y};
    }

    Layer getLayer() override {
        return RENDER_LAYER;
    }

    const string getImageConfigPath() override {
        return PathHelper::generatePath(CONFIG_PATH);
    }
};
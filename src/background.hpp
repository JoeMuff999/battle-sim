#pragma once

#include "drawable.hpp"
#include "drawableLinkedList.hpp"
#include "pathHelper.hpp"

class Background : public Drawable {
    const string CONFIG_PATH = "/config/bridge";
    const Layer RENDER_LAYER = Layer::BACKGROUND;
public: 
    Background(LayeredDrawableList& drawableStore) {
        drawableStore.insert(this);
    }

    Point getPos() override {
        return Point{0, 0};
    }

    Layer getLayer() override {
        return RENDER_LAYER;
    }

    const string getImageConfigPath() override {
        return PathHelper::generatePath(CONFIG_PATH);
    }
};
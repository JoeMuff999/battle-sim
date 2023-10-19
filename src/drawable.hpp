#include "point.hpp"
#include <SDL.h>
#include <iostream>
#include "graphics.hpp"
#include "pathHelper.hpp"
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

using namespace std;

enum Layer {
    BACKGROUND, TERRAIN, NPC, PLAYER
};

struct configRow
{
    string name;
    string pathToImage;
    string numFrames;
};

typedef struct configRow ConfigRow;

struct imageData
{
    string name;
    int numFrames;
    SDL_Rect clip;
    SDL_Surface *image;
};
typedef struct imageData ImageData;

class Drawable
{
public:
    SDL_Rect spriteRect;

    virtual const string getImageConfigPath() = 0;

    virtual Point getPos() = 0; // force consistency between graphics position and entity position

    virtual Layer getLayer() = 0;

    void initializeSprite(const SDL_Surface *_mainSurface)
    {
        string tmp = getImageConfigPath();
        vector<ConfigRow> config = parseConfig(tmp);

        for (ConfigRow configRow : config)
        {
            SDL_Surface *image = Graphics::loadSurface(_mainSurface, configRow.pathToImage);
            if (image == NULL)
            {
                cout << "Drawable not initialized! img path = " << configRow.pathToImage << " error = " << SDL_GetError() << endl;
                return;
            }
            ImageData _imageData;
            _imageData.image = image;
            _imageData.name = configRow.name;
            _imageData.numFrames = stoi(configRow.numFrames);
            _imageData.clip.h = image->h / 1;
            _imageData.clip.w = image->w / _imageData.numFrames;
            mapStateToImage[configRow.name] = _imageData;
        }
        //TODO: set the default state in a generic way
        setState("Idle");
    }

    void updateSprite(SDL_Surface *&mainSurface)
    {
        drawToScreen(mainSurface);
    }

    void drawToScreen(SDL_Surface *&mainSurface)
    {
        Point currPoint = getPos();
        m_currentFrame.x += 1;
        m_currentFrame.y += 1;
        if (m_currentFrame.y >= 1)
        {
            m_currentFrame.y = 0;
        }
        if (m_currentFrame.x >= currentImage.numFrames)
        {
            m_currentFrame.x = 0;
        }

        currentImage.clip.x = m_currentFrame.x * currentImage.clip.w;
        currentImage.clip.y = m_currentFrame.y * currentImage.clip.h;

        spriteRect.x = currPoint.x;
        spriteRect.y = currPoint.y;
        spriteRect.h = currentImage.image->h;
        spriteRect.w = currentImage.image->w;

        int ret = SDL_BlitSurface(currentImage.image, &currentImage.clip, mainSurface, &spriteRect);
        if (ret == -1) {
            cout << "Failed to display drawable: " << SDL_GetError() << endl;
        }
    }

    void setState(string state)
    {
        //check if state exists first
        auto item = mapStateToImage.find(state);

        if (item == mapStateToImage.end())
        {
            std::cout << "Key " << state << " does not exist." << std::endl;
            return;
        }

        currentImage = mapStateToImage[state];
    }

    void cleanupSprite()
    {
        for (const auto& pair : mapStateToImage) {
            SDL_FreeSurface(pair.second.image);
        }
    }

private:
    ImageData currentImage;
    Point m_currentFrame = {0, 0};
    int m_layer;

    map<string, ImageData> mapStateToImage;

    vector<ConfigRow> parseConfig(const string &pathToConfig)
    {
        vector<ConfigRow> data;
        ifstream file(pathToConfig);

        if (!file.is_open())
        {
            cerr << "Failed to open the file." << endl;
            return data;
        }

        string line;
        string cell;

        // Read and discard the header row if it exists.
        getline(file, line);

        while (getline(file, line))
        {
            istringstream lineStream(line);
            ConfigRow row;

            // Parse each cell in the row using ',' as the delimiter.
            getline(lineStream, row.name, ',');
            getline(lineStream, row.pathToImage, ',');
            getline(lineStream, row.numFrames, ',');
            // Add more lines for additional columns as needed.

            row.pathToImage = PathHelper::generatePath(row.pathToImage);

            data.push_back(row);
        }

        file.close();
        return data;
    }
};

#endif
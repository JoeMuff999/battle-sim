#include "point.hpp"
#include <SDL.h>
#include <iostream>
#include "graphics.hpp"

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

using namespace std;

class Drawable {

    SDL_Surface* image = NULL;
    int m_rows = 0;
    int m_columns = 0;
    Point m_currentFrame = {0,0};
    SDL_Rect m_clip;
    

    public:
    SDL_Rect spriteRect;

        virtual const string getImgPath() = 0;

        virtual Point getPos() = 0; //force consistency between graphics position and entity position

        void initializeSprite(const SDL_Surface* _mainSurface, int _rows, int _columns)
        {   
            std::string tmp = getImgPath();
            image = Graphics::loadSurface(_mainSurface, tmp);

            if(image == NULL)
            {
                cout << "Drawable not initialized! img path = "<< getImgPath() << " error = " << SDL_GetError() << endl;
                return;
            }

            m_clip.h = image->h / _rows;
            m_clip.w = image->w / _columns;

            m_rows = _rows;
            m_columns = _columns;

            spriteRect = {0, 0, image->w, image->h};
        }

        void updateSprite(SDL_Surface*& mainSurface)
        {
           drawToScreen(mainSurface);
        }

        void drawToScreen(SDL_Surface*& mainSurface)
        {
            Point currPoint = getPos();
            m_currentFrame.x += 1;
            m_currentFrame.y += 1;
            if (m_currentFrame.y >= m_rows) {
                m_currentFrame.y = 0;
            }
            if (m_currentFrame.x >= m_columns) {
                m_currentFrame.x = 0;
            }

            m_clip.x = m_currentFrame.x * m_clip.w;
            m_clip.y = m_currentFrame.y * m_clip.h;

            spriteRect.x = currPoint.x;
            spriteRect.y = currPoint.y;
            SDL_BlitSurface(image, &m_clip, mainSurface, &spriteRect);    
        }

        void cleanupSprite()
        {
            SDL_FreeSurface(image);
            image = NULL;
        }
        
};

#endif
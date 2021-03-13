#include "point.hpp"
#include <SDL.h>
#include <iostream>
using namespace std;
class Drawable{

    Point center;
    SDL_Surface* image = NULL;

    public:
        virtual const string getImgPath() = 0;

        void initializeSprite()
        {   
            std::string tmp = getImgPath();
            cout << tmp <<endl;
            image = SDL_LoadBMP(tmp.c_str());   
        }
        void drawToScreen(SDL_Surface*& gameWindow, Point point)
        {
            if(image == NULL)
            {
                cout << "Drawable not initialized! img path = "<< getImgPath() << " error = " << SDL_GetError() << endl;
                return;
            }
            // use SDL rect to define where the bitmap will be drawn
            SDL_Rect destRect;
            destRect.x = point.x;
            destRect.y = point.y;
            destRect.w = image->w;
            destRect.h = image->h;
            SDL_BlitSurface(image, NULL, gameWindow, &destRect);
        }

        void drawToScreen(SDL_Surface*& gameWindow, int x, int y)
        {
            if(image == NULL)
            {
                cout << "Drawable not initialized! img path = "<< getImgPath() << " error = " << SDL_GetError() << endl;
                return;
            }
            // use SDL rect to define where the bitmap will be drawn
            SDL_Rect destRect;
            destRect.x = x;
            destRect.y = y;
            destRect.w = image->w;
            destRect.h = image->h;
            SDL_BlitSurface(image, NULL, gameWindow, &destRect);
        }

        void cleanupSprite()
        {
            SDL_FreeSurface(image);
            image = NULL;
        }
        
};
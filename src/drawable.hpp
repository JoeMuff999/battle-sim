#include "point.hpp"
#include <SDL.h>
#include <iostream>
using namespace std;
class Drawable{

    SDL_Surface* image = NULL;
    public:
    SDL_Rect spriteRect;

        virtual const string getImgPath() = 0;

        virtual Point getPos() = 0; //force consistency between graphics position and entity position

        void initializeSprite()
        {   
            std::string tmp = getImgPath();
            image = SDL_LoadBMP(tmp.c_str());   
        }

        void updateSprite(SDL_Surface*& mainSurface)
        {
            Point currPoint = getPos();
            // cout << "accessed position " << spriteRect.y <<endl;
            Uint32 white = 0xffffffff;
            SDL_FillRect(mainSurface, &spriteRect, white);    

            spriteRect.x = currPoint.x;
            spriteRect.y = currPoint.y;
            SDL_BlitSurface(image, NULL, mainSurface, &spriteRect);    

    
        }

        void drawToScreen(SDL_Surface*& mainSurface)
        {
            if(image == NULL)
            {
                cout << "Drawable not initialized! img path = "<< getImgPath() << " error = " << SDL_GetError() << endl;
                return;
            }
            // use SDL rect to define where the bitmap will be drawn'
            Point point = getPos();
            // spriteRect->x = point.x;
            // spriteRect->y = point.y;
            // spriteRect->w = image->w;
            // spriteRect->h = image->h;
            spriteRect = {point.x, point.y, image->w, image->h};
            // cout << spriteRect.x << " " << spriteRect.y << endl;
            SDL_BlitSurface(image, NULL, mainSurface, &spriteRect);    

        }

        void cleanupSprite()
        {
            SDL_FreeSurface(image);
            image = NULL;
        }
        
};
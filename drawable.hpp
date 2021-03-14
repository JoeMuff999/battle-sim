#include "point.hpp"
#include <SDL.h>
#include <iostream>
using namespace std;
class Drawable{

    SDL_Surface* image = NULL;
    SDL_Rect spriteRect;
    public:
        virtual const string getImgPath() = 0;

        virtual Point getPos() = 0; //force consistency between graphics position and entity position

        void initializeSprite()
        {   
            std::string tmp = getImgPath();
            cout << tmp <<endl;
            image = SDL_LoadBMP(tmp.c_str());   
        }

        void updateSprite()
        {
            Point currPoint = getPos();
            cout << "accessed position " << spriteRect.x <<endl;

            spriteRect.x = currPoint.x;
            spriteRect.y = currPoint.y;
            // SDL_BlitSurface(image, NULL, gameWindow, &spriteRect);

        }

        void drawToScreen(SDL_Surface* gameWindow)
        {
            if(image == NULL)
            {
                cout << "Drawable not initialized! img path = "<< getImgPath() << " error = " << SDL_GetError() << endl;
                return;
            }
            // use SDL rect to define where the bitmap will be drawn'
            Point point = getPos();
            spriteRect.x = point.x;
            spriteRect.y = point.y;
            spriteRect.w = image->w;
            spriteRect.h = image->h;
            SDL_BlitSurface(image, NULL, gameWindow, &spriteRect);
            spriteRect.x+=100;
        }

        void cleanupSprite()
        {
            SDL_FreeSurface(image);
            image = NULL;
        }
        
};
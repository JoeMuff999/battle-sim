/*
    Game.hpp. Overarching class which contains all state information for the simulation
*/
#include <vector>
#include "agent.hpp"
#include "graphics.hpp"
#include "time.hpp"
#include "InputManager.hpp"
#include "drawableLinkedList.hpp"
#include "background.hpp"
#include "wall.hpp"

#ifndef GAME_HPP
#define GAME_HPP

class Game
{
    SDL_Window *_gameWindow;
    SDL_Surface *_mainSurface;
    vector<Agent*> agents;
    LayeredDrawableList drawables;
    vector<Controllable*> controllables;
    vector<StaticCollidable*> staticCollidables;

public:
    Game(SDL_Window *&gameWindow, SDL_Surface *&mainSurface)
    {
        _gameWindow = gameWindow;
        _mainSurface = mainSurface;
    }

    //initialize all of the gameobjects, do drawing, etc
    void start()
    {
        Wall* wall = new Wall(0 ,390-55-10, 1920, 10);
        staticCollidables.push_back(wall);

        PlayerAgent* pagent = new PlayerAgent(0,500, {40, 55}, {28, 50}, agents, drawables, controllables);
        pagent->initializeSprite(_mainSurface);
        pagent->drawToScreen(_mainSurface);
        FlockingAgent* fagent = new FlockingAgent(100,200, agents, drawables);
        fagent->initializeSprite(_mainSurface);
        fagent->drawToScreen(_mainSurface);
        Background* background = new Background(drawables);
        background->initializeSprite(_mainSurface);
        background->drawToScreen(_mainSurface);
    }

    void mainLoop()
    {
        bool quit = false;
        //read 1 input per frame, update player then update the agents then update graphics
        using namespace std::chrono;
        steady_clock::time_point lastFrameStartTime = Time::getTime();
        while (!quit)
        {
            steady_clock::time_point startTime = Time::getTime();
            const float frameDeltaTime = Time::getTimeBetween(startTime, lastFrameStartTime);
            SDL_Event e;
            //Handle events on queue
            if(!InputManager::handleInput(controllables))
                break;
            

            update(frameDeltaTime);

            const float frameTimeSoFar = Time::getElapsedTime(startTime)*1000;
            Time::sleepForMilliseconds(Time::MS_PER_FRAME - frameTimeSoFar);
            lastFrameStartTime = startTime;
        }
        cleanup();
        Graphics::shutdownSDL(_gameWindow);
    }
    //record time at the start of the frame
    void update(const float previousFrameStartTime)
    {        
        //update agents
        for(Agent* agent : agents)
        {
            agent->updateAgent(previousFrameStartTime, staticCollidables);
        }
        SDL_FillRect(_mainSurface, NULL, SDL_MapRGB(_mainSurface->format, 0x77, 0x77, 0x77));

        //update graphics
        drawables.renderAll(_mainSurface);
        SDL_UpdateWindowSurface(_gameWindow);
    }

    void cleanup()
    {
        drawables.cleanupAll();
    }
};

#endif
/*
    Game.hpp. Overarching class which contains all state information for the simulation
*/
#include <vector>
#include "agent.hpp"
#include "graphics.hpp"
#include "time.hpp"
#include "InputManager.hpp"
class Game
{
    SDL_Window *_gameWindow;
    SDL_Surface *_mainSurface;
    vector<Agent*> agents;
    vector<Drawable*> drawables;
    vector<Controllable*> controllables;

public:
    Game(SDL_Window *&gameWindow, SDL_Surface *&mainSurface)
    {
        _gameWindow = gameWindow;
        _mainSurface = mainSurface;
    }

    //initialize all of the gameobjects, do drawing, etc
    void start()
    {
        PlayerAgent* fagent = new PlayerAgent(300,200);
        agents.push_back(fagent);
        drawables.push_back(fagent);
        controllables.push_back(fagent);
        fagent->initializeSprite();
        fagent->drawToScreen(_mainSurface);
    }

    void mainLoop()
    {
        bool quit = false;
        //read 1 input per frame, update player then update the agents then update graphics
        using namespace std::chrono::_V2;
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
        shutdownSDL(_gameWindow);
    }
    //record time at the start of the frame
    void update(const float previousFrameStartTime)
    {        
        //update agents
        for(Agent* agent : agents)
        {
            agent->updateAgent(previousFrameStartTime);
        }
        //update graphics
        for(Drawable* drawable : drawables)
        {
            drawable->updateSprite(_mainSurface);
        }
        SDL_UpdateWindowSurface(_gameWindow);
    }

    void cleanup()
    {
        for (int i = 0; i < agents.size(); i++)
        {
            agents[i]->cleanupSprite();
        }
    }
};
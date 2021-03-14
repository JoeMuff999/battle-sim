/*
    Game.hpp. Overarching class which contains all state information for the simulation
*/
#include <vector>
#include "agent.hpp"
#include "graphics.hpp"
#include "time.hpp"
class Game
{
    SDL_Window *_gameWindow;
    SDL_Surface *_mainSurface;
    vector<Agent> agents;

public:
    Game(SDL_Window *&gameWindow, SDL_Surface *&mainSurface)
    {
        _gameWindow = gameWindow;
        _mainSurface = mainSurface;
    }

    //initialize all of the gameobjects, do drawing, etc
    void start()
    {
        FriendlyAgent fagent(300,200);
        agents.push_back(fagent);
        fagent.initializeSprite();
        fagent.drawToScreen(_mainSurface);
    }

    void mainLoop()
    {
        //read 1 input per frame, update player then update the agents then update graphics
        Time::sleepForMilliseconds(Time::MS_PER_FRAME);
        std::chrono::_V2::steady_clock::time_point lastFrameStartTime = Time::getTime();
        while (true)
        {
            std::chrono::_V2::steady_clock::time_point startTime = Time::getTime();
            const float frameDeltaTime = Time::getTimeBetween(startTime, lastFrameStartTime);
            SDL_Event e;
            //Handle events on queue
            if(SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if(e.type == SDL_QUIT)
                {
                    cout << "QUITTING " <<endl;
                    break;
                }
            }
            update(frameDeltaTime);

            const float frameTimeSoFar = Time::getElapsedTime(startTime)*1000;
            Time::sleepForMilliseconds(Time::MS_PER_FRAME - frameTimeSoFar);
            // cout << "new frame " << frameTimeSoFar << endl;
            lastFrameStartTime = startTime;
        }
        shutdownSDL(_gameWindow);
    }
    //record time at the start of the frame
    void update(const float previousFrameStartTime)
    {
        // for (int i = 0; i < agents.size(); i++)
        // {
        //     agents[i].updateAgent(previousFrameStartTime);
        // }
        //update agents
        for(Agent& agent : agents)
        {
            agent.updateAgent(previousFrameStartTime);
        }
        // update graphics
        for(Agent& agent : agents)
        {
            agent.updateSprite();
        }
        // for(int i = 0; i < agents.size(); i++)
        // {
        //     agents[i].updateSprite();
        // }
        SDL_UpdateWindowSurface(_gameWindow);
    }

    void cleanup()
    {
        for (int i = 0; i < agents.size(); i++)
        {
            agents[i].cleanupSprite();
        }
    }
};
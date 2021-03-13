/*
    Game.hpp. Overarching class which contains all state information for the simulation
*/
#include <vector>
#include "agent.hpp"
class Game{   
    SDL_Window* _gameWindow;
    SDL_Surface* _mainSurface;
    vector<Agent> agents;
    public:
    Game(SDL_Window*& gameWindow, SDL_Surface*& mainSurface)
    {
        _gameWindow = gameWindow;
        _mainSurface = mainSurface;
    }
    void test_game(int x, int y)
    {
        FriendlyAgent fagent;
        agents.push_back(fagent);
        Point p = point(x,y);
        fagent.setPos(p);
        fagent.initializeSprite();
        fagent.drawToScreen(_mainSurface, fagent.getPos());
    }

    void cleanup()
    {
        for(int i = 0; i < agents.size(); i++)
        {
            agents[i].cleanupSprite();
        }
    }
    
};
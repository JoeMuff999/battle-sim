#include "point.hpp"
#include "drawable.hpp"
#include "controllable.hpp"
#include "pathHelper.hpp"

#include <string>
#include <stdio.h>
#include <queue>
#include <math.h> 
/*
    base class from which all other agents inherit their functions
*/

#ifndef AGENT_HPP
#define AGENT_HPP

class Agent : public Drawable
{
protected:
    Point _position;
    Point _target;
    Vec2D _truePosition;
    float _movementSpeed = 100.0f;

public:
    Agent(int x, int y)
    {
        _position ={x,y};
        _truePosition.x = x;
        _truePosition.y = y;
        _target = {x, y};
    }
    Agent(int x, int y, vector<Agent*>& agentStore, vector<Drawable*>& drawableStore)
    {
        _position ={x,y};
        _truePosition.x = x;
        _truePosition.y = y;
        _target = {x, y};
        agentStore.push_back(this);
        drawableStore.push_back(this);
    }
    const std::string getImageConfigPath()
    {
        string dummy;
        return dummy;
    }
    Point getPos()
    {
        return _position;
    }
    void setPos(Point point)
    {
        _position = point;
    }
    //should update the agent's internal position
    virtual void updateAgent(const float frameDeltaTime)
    {
        pathToTarget(frameDeltaTime);
    }
    /*
        allow derived classes to define their own movement speed
    */
    virtual float getMoveSpeed()
    {
        return _movementSpeed;
    }

    void pathToTarget(const float frameDeltaTime);

    void setTarget(int x, int y)
    {
        _target = {x,y};
    }
    //A*
    void pathToPoint()
    {

    }
};

class PlayerAgent : public Agent, public Controllable
{
    string cfg_path = "/config/warrior";
    float _movementSpeed = 200.0f;
public:        
    PlayerAgent(int x, int y, vector<Agent*>& agentStore, vector<Drawable*>& drawableStore, vector<Controllable*>& controllables) : Agent(x, y) {
        controllables.push_back(this);
        agentStore.push_back(this);
        drawableStore.push_back(this);
    }

    float getMoveSpeed()
    {
        return _movementSpeed;
    }

    void updateAgent(const float frameDeltaTime)
    {
        Agent::updateAgent(frameDeltaTime);
    }

    void handleInput(SDL_Event& e, Point& mousePosition)
    {
        setTarget(mousePosition.x, mousePosition.y);
    }

    const std::string getImageConfigPath() override
    {
        return PathHelper::generatePath(cfg_path);
    }
    
};

class FlockingAgent : public Agent
{
    string cfg_path = "/config/warrior";
    //smart pointer please :)
    vector<Agent*>* _agents;
    float _heading;

public:        
    FlockingAgent(int x, int y, vector<Agent*>& agentStore, vector<Drawable*>& drawableStore) : Agent(x, y) {
        agentStore.push_back(this);
        _agents = &agentStore;
        drawableStore.push_back(this);
        _heading = 0.0f;
    }

    const std::string getImageConfigPath() override
    {
        return PathHelper::generatePath(cfg_path);
    }
    /*
        TODO: smart pointer please :)
    */

   void updateHeading();
    
    //override: behavior should be following the player, although this will eventually be more in-depth.
    void updateAgent(const float frameDeltaTime);
};

#endif

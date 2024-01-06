#include "point.hpp"
#include "drawable.hpp"
#include "controllable.hpp"
#include "pathHelper.hpp"
#include "drawableLinkedList.hpp"

#include <string>
#include <stdio.h>
#include <queue>
#include <math.h> 
/*
    base class from which all other agents inherit their functions
*/

#ifndef AGENT_HPP
#define AGENT_HPP

class Agent
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

    void setPos(Point point)
    {
        _position = point;
    }
    //should update the agent's internal position, returns the continuous change in position
    virtual Vec2D updateAgent(const float frameDeltaTime)
    {
        return pathToTarget(frameDeltaTime);
    }
    /*
        allow derived classes to define their own movement speed
    */
    virtual float getMoveSpeed()
    {
        return _movementSpeed;
    }

    Vec2D pathToTarget(const float frameDeltaTime);

    void setTarget(int x, int y)
    {
        _target = {x,y};
    }
    //A*
    void pathToPoint()
    {

    }
};

class PlayerAgent : public Agent, public Controllable, public Drawable
{
    string cfg_path = "/config/warrior";
    float _movementSpeed = 200.0f;

    const Layer m_layer = Layer::PLAYER;
public:        
    PlayerAgent(int x, int y, vector<Agent*>& agentStore, LayeredDrawableList& drawableStore, vector<Controllable*>& controllables) : Agent(x, y) {
        controllables.push_back(this);
        agentStore.push_back(this);
        drawableStore.insert(this);
    }

    Point getPos() override
    {
        return _position;
    }

    float getMoveSpeed()
    {
        return _movementSpeed;
    }

    Vec2D updateAgent(const float frameDeltaTime) override
    {
        Vec2D totalMovement = Agent::updateAgent(frameDeltaTime);
        if(abs(totalMovement.x) > 0.0f || abs(totalMovement.y) > 0.0f) {
            setState("Walk");
        } else {
            setState("Idle");
        }
        return totalMovement;
    }

    void handleInput(SDL_Event& e, Point& mousePosition)
    {
        setTarget(mousePosition.x, mousePosition.y);
    }

    const std::string getImageConfigPath() override
    {
        return PathHelper::generatePath(cfg_path);
    }

    Layer getLayer() override {
        return m_layer;
    }

    
};

class FlockingAgent : public Agent, public Drawable
{
    string cfg_path = "/config/warrior";
    //smart pointer please :)
    vector<Agent*>* _agents;
    float _heading;

    const Layer m_layer = Layer::NPC;


public:        
    FlockingAgent(int x, int y, vector<Agent*>& agentStore, LayeredDrawableList& drawableStore) : Agent(x, y) {
        agentStore.push_back(this);
        _agents = &agentStore;
        drawableStore.insert(this);
        _heading = 0.0f;
    }

    Point getPos() override
    {
        return _position;
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
    Vec2D updateAgent(const float frameDeltaTime) override;

    Layer getLayer() override {
        return m_layer;
    }
};

#endif

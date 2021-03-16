#include "point.hpp"
#include "drawable.hpp"
#include "controllable.hpp"

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <queue>
#include <math.h> 
/*
    base class from which all other agents inherit their functions
*/
class Agent : public Drawable
{
protected:
    Point _position;
    Point _target;
    floatPoint _truePosition;
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
    const std::string getImgPath()
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

    void pathToTarget(const float frameDeltaTime)
    {
        float totalMovementForThisFrame = getMoveSpeed() * frameDeltaTime;

        float x = _target.x - _truePosition.x;
        float y = _target.y - _truePosition.y;
        float xx = x*x;
        float yy = y*y;

        float mag = sqrt(xx+yy);
        if(mag < totalMovementForThisFrame)
        {

            return;
        }

        float x_norm = x/mag;
        float y_norm = y/mag;

        float x_movement = totalMovementForThisFrame * x_norm;
        float y_movement = totalMovementForThisFrame * y_norm;

        _truePosition.x+=x_movement;
        _truePosition.y+=y_movement;
        _position.x = (int)_truePosition.x;
        _position.y = (int)_truePosition.y;
    }

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
    string bmp_path = "/sprites/player_agent.bmp";
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

    const std::string getImgPath()
    {
        char cwd[FILENAME_MAX];
        getcwd(cwd, FILENAME_MAX);

        std::string currDir(cwd);
        currDir += bmp_path;

        return currDir;
    }
    
};

class FriendlyAgent : public Agent
{
    string bmp_path = "/sprites/friendly_agent.bmp";
    Agent* _toFollow;
public:        
    FriendlyAgent(int x, int y, vector<Agent*>& agentStore, vector<Drawable*>& drawableStore) : Agent(x, y) {
        agentStore.push_back(this);
        drawableStore.push_back(this);
    }

    const std::string getImgPath()
    {
        char cwd[FILENAME_MAX];
        getcwd(cwd, FILENAME_MAX);

        std::string currDir(cwd);
        currDir += bmp_path;

        return currDir;
    }
    /*
        TODO: smart pointer please :)
    */
    void setTargetAgent(Agent* toFollow)
    {
        _toFollow = toFollow;
    }
    //override: behavior should be following the player, although this will eventually be more in-depth.
    void updateAgent(const float frameDeltaTime)
    {
        Point targetAgentPos = _toFollow->getPos();
        setTarget(targetAgentPos.x, targetAgentPos.y);
        pathToTarget(frameDeltaTime);
    }   

};
#include "point.hpp"
#include "drawable.hpp"
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
public:
    Point _position;
    Point _target;
    floatPoint _truePosition;
    float movementSpeed = 10.0f;
    queue<Point> path;

public:
    Agent(int x, int y)
    {
        _position.x = x;
        _position.y = y;
        _truePosition.x = x;
        _truePosition.y = y;
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
    void updateAgent(const float frameDeltaTime)
    {
        // if(path.empty())
        //     return;

        float totalMovementForThisFrame = movementSpeed * frameDeltaTime;

        float x = 0 - _truePosition.x;
        float y = 0 - _truePosition.y;
        float xx = x*x;
        float yy = y*y;

        float mag = sqrt(xx+yy);
        if(mag < 1)
        {
            cout << "reached target " <<endl;
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

    //A*
    void pathToPoint()
    {
    }
};

class FriendlyAgent : public Agent
{
    string bmp_path = "/sprites/agent.bmp";
public:        
    FriendlyAgent(int x, int y) : Agent(x, y) {}

    const std::string getImgPath()
    {
        char cwd[FILENAME_MAX];
        getcwd(cwd, FILENAME_MAX);

        std::string currDir(cwd);
        currDir += bmp_path;
        // cout << "in img path " << currDir <<  " size = " << currDir.size() <<endl;

        return currDir;
    }
};
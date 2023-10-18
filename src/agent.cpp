#include "agent.hpp"

void Agent::pathToTarget(const float frameDeltaTime)
{
    float totalMovementForThisFrame = getMoveSpeed() * frameDeltaTime;

    float x = _target.x - _truePosition.x;
    float y = _target.y - _truePosition.y;
    float xx = x * x;
    float yy = y * y;

    float mag = sqrt(xx + yy);
    if (mag < totalMovementForThisFrame)
    {
        setState("Idle");
        return;
    }
    //NOTE: this should be moved
    setState("Walk");
   

    float x_norm = x / mag;
    float y_norm = y / mag;

    float x_movement = totalMovementForThisFrame * x_norm;
    float y_movement = totalMovementForThisFrame * y_norm;

    _truePosition.x += x_movement;
    _truePosition.y += y_movement;
    _position.x = (int)_truePosition.x;
    _position.y = (int)_truePosition.y;
}

void FlockingAgent::updateHeading()
{
    
}

void FlockingAgent::updateAgent(const float frameDeltaTime)
{
    this->updateHeading();
    float totalMovementForThisFrame = getMoveSpeed() * frameDeltaTime;
    float x_move = totalMovementForThisFrame * cosf(_heading);
    float y_move = totalMovementForThisFrame * sinf(_heading);
    _truePosition.x = _truePosition.x + x_move;
    _truePosition.y = _truePosition.y + y_move;
    _position.x = (int)_truePosition.x;
    _position.y = (int)_truePosition.y;
}
        
 
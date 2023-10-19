#include "agent.hpp"

Point Agent::pathToTarget(const float frameDeltaTime)
{
    float totalMovementForThisFrame = getMoveSpeed() * frameDeltaTime;

    float x = _target.x - _truePosition.x;
    float y = _target.y - _truePosition.y;
    float xx = x * x;
    float yy = y * y;

    float mag = sqrt(xx + yy);
    if (mag < totalMovementForThisFrame)
    {
        return Point{0,0};
    }   

    float x_norm = x / mag;
    float y_norm = y / mag;

    float x_movement = totalMovementForThisFrame * x_norm;
    float y_movement = totalMovementForThisFrame * y_norm;

    _truePosition.x += x_movement;
    _truePosition.y += y_movement;
    _position.x = (int)_truePosition.x;
    _position.y = (int)_truePosition.y;

    return Point{x_movement, y_movement};
}

void FlockingAgent::updateHeading()
{
    
}

Point FlockingAgent::updateAgent(const float frameDeltaTime)
{
    this->updateHeading();
    float totalMovementForThisFrame = getMoveSpeed() * frameDeltaTime;
    float x_move = totalMovementForThisFrame * cosf(_heading);
    float y_move = totalMovementForThisFrame * sinf(_heading);
    _truePosition.x = _truePosition.x + x_move;
    _truePosition.y = _truePosition.y + y_move;
    _position.x = (int)_truePosition.x;
    _position.y = (int)_truePosition.y;
    return Point{x_move, y_move};
}
        
 
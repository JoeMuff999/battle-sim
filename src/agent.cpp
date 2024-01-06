#include "agent.hpp"

Vec2D Agent::pathToTarget(const float frameDeltaTime)
{
    float totalMovementForThisFrame = getMoveSpeed() * frameDeltaTime;

    float x = _target.x - _truePosition.x;
    float y = _target.y - _truePosition.y;
    float xx = x * x;
    float yy = y * y;

    float mag = sqrt(xx + yy);
    if (mag < totalMovementForThisFrame)
    {
        return Vec2D{0,0};
    }   

    float x_norm = x / mag;
    float y_norm = y / mag;

    float x_movement = totalMovementForThisFrame * x_norm;
    float y_movement = totalMovementForThisFrame * y_norm;

    _truePosition.x += x_movement;
    _truePosition.y += y_movement;
    _position.x = (int)_truePosition.x;
    _position.y = (int)_truePosition.y;

    return Vec2D{x_movement, y_movement};
}

void FlockingAgent::updateHeading()
{
    
}

Vec2D FlockingAgent::updateAgent(const float frameDeltaTime)
{
    this->updateHeading();
    float totalMovementForThisFrame = getMoveSpeed() * frameDeltaTime;
    float x_move = totalMovementForThisFrame * cosf(_heading);
    float y_move = totalMovementForThisFrame * sinf(_heading);
    _truePosition.x = _truePosition.x + x_move;
    _truePosition.y = _truePosition.y + y_move;
    _position.x = (int)_truePosition.x;
    _position.y = (int)_truePosition.y;
    return Vec2D{x_move, y_move};
}
        
 
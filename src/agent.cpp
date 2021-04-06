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
        return;
    }

    float x_norm = x / mag;
    float y_norm = y / mag;

    float x_movement = totalMovementForThisFrame * x_norm;
    float y_movement = totalMovementForThisFrame * y_norm;

    _truePosition.x += x_movement;
    _truePosition.y += y_movement;
    _position.x = (int)_truePosition.x;
    _position.y = (int)_truePosition.y;
}
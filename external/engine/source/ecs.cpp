#include "ECS.h"

void GameActor::b2BodyToInterpolation(b2Body*& body)
{
    PreviousPosition = body->GetPosition();
}

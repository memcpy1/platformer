#include "ECS.h"
#include "Engine.h"

void GameActor::b2BodyToInterpolation(b2Body*& body)
{
    PreviousPosition = body->GetPosition();
}

void System::Player::Update(const std::size_t& ID, Registry& reg)
{
    
}
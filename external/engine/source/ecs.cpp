#include "ECS.h"
#include "Engine.h"

void System::Player::Update(const std::size_t& ID, Registry& reg, bool collision)
{

}


#pragma region PHYSICSD
System::Physics::Physics(const float& timestepFixed, const float& gravity)
    : TimestepAccumulator(0), TimestepAccumulatorRatio(0), VelocityIterations(6), PositionIterations(2)
{
    FixedTimestep = timestepFixed;

    World = new b2World(b2Vec2(0, -gravity));
    World->SetAutoClearForces(0);
}

void System::Physics::Update(float& Dt, Registry& reg) //should refactor
{  
    if (Dt > 0.03f)
        Dt = 0.03f;
    
    TimestepAccumulator += Dt;
    while (TimestepAccumulator >= Dt)
    {    
        World->Step(Dt, VelocityIterations, PositionIterations);
        TimestepAccumulator -= Dt;
    }

    const double Alpha = TimestepAccumulator / Dt;
    Interpolate(reg, Alpha);
}

void System::Physics::Interpolate(Registry& reg, const double& alpha)
{
    
}

#pragma endregion PHYSICS

void Component::Physics::Actor::b2BodyToInterpolation(b2Body*& body)
{
    PreviousPosition = body->GetPosition();
}

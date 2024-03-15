#include "Physics.h"
#include "Engine.h"


PhysicsWorld::PhysicsWorld(const float& timestepFixed, const float& gravity)
    : TimestepAccumulator(0), TimestepAccumulatorRatio(0), VelocityIterations(6), PositionIterations(2)
{
    FixedTimestep = timestepFixed;

    World = new b2World(b2Vec2(0, -gravity));
    World->SetAutoClearForces(0);
}

void PhysicsWorld::Update(float& Dt, Registry& reg)
{  
    if (Dt > 0.05f)
        Dt = 0.05f;
    
    TimestepAccumulator += Dt;
    while (TimestepAccumulator >= Dt)
    {
            
        World->Step(Dt, VelocityIterations, PositionIterations);
        TimestepAccumulator -= Dt;
    }

    const double Alpha = TimestepAccumulator / Dt;
    Interpolate(reg, Alpha);
}

void PhysicsWorld::Interpolate(Registry& reg, const double& alpha)
{
    
}
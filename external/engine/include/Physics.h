#pragma once
//engine
#include "ECS.h"
//STL
#include <vector>
//vendor
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

class PhysicsWorld
{
private:
    int32_t VelocityIterations;
    int32_t PositionIterations;

    float TimestepAccumulator;
    float TimestepAccumulatorRatio;

    b2World* World;
public:
    float FixedTimestep;
private:
    
    void Update(float& Dt, Registry& reg);
    
    void Interpolate(Registry& reg, const double& alpha);
    PhysicsWorld(const float& timestepFixed, const float& gravity);

    friend class Engine;
};
#include "ECS.h"
#include "Engine.h"


void System::Player::Update(const std::size_t& ID, Registry& reg, bool collision, b2World* world, DebugDrawSDL& debug)
{
    b2Vec2 Vel = reg.regPhysics[ID].body->GetLinearVelocity();

    if (Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_RIGHT))
        reg.regPlayer[ID].MoveState = PlayerMoveX::MOVE_RIGHT;
    else if (Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_LEFT))
        reg.regPlayer[ID].MoveState = PlayerMoveX::MOVE_LEFT;
    else if (Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_RIGHT) && Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_LEFT))
        reg.regPlayer[ID].MoveState = PlayerMoveX::STOP;
    else
        reg.regPlayer[ID].MoveState = PlayerMoveX::STOP;

    float VelChangeX = reg.regPlayer[ID].MoveState * 0.33f - Vel.x;

    if (Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_C))
    {
        if (reg.regPlayer[ID].GroundContacts < 1) 
            return;
        else
        {
            reg.regPhysics[ID].body->ApplyLinearImpulse(b2Vec2(0, reg.regPhysics[ID].body->GetMass() / 9), reg.regPhysics[ID].body->GetWorldCenter(), 0);
        }      
    }
        
            

    

    reg.regPhysics[ID].body->ApplyLinearImpulse(b2Vec2((VelChangeX * reg.regPhysics[ID].body->GetMass()), 0), 
    reg.regPhysics[ID].body->GetWorldCenter(), 0);

    //std::cout << reg.regPlayer[ID].GroundContacts << '\n';
}

#pragma region PHYSICS
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

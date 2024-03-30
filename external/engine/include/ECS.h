#pragma once
//STL
#include <unordered_map>
//box2D
#include <box2d/b2_math.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

enum PlayerMoveX
{
    MOVE_LEFT = -1,
    STOP = 0,
    MOVE_RIGHT = 1
};

struct Material
{

};

struct ActorData : b2BodyUserData
{
    std::size_t ECS_ID;
};

struct Component
{
    struct Physics
    {
        struct Actor
        {
            b2Body* body;

            b2Vec2 SmoothedPosition;
            b2Vec2 PreviousPosition;
            void b2BodyToInterpolation(b2Body*& body);
        };

        struct Solid
        {
            b2Body* body;

            Material Mat;
        };
    };

    struct Player
    {
        b2Vec2 Acceleration;
        b2Vec2 Velocity; 
        PlayerMoveX MoveState;
        b2RayCastInput GroundCheck;
    };
};

struct Registry
{
    std::unordered_map<std::size_t, Component::Physics> regPhysics;
    std::unordered_map<std::size_t, Component::Physics::Actor> regActor;
    std::unordered_map<std::size_t, Component::Physics::Solid> regSolid; 
    std::unordered_map<std::size_t, Component::Player> regPlayer;
};

struct System
{
    std::size_t MaxEntities;



    struct Physics
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
        Physics(const float& timestepFixed, const float& gravity);

    public:
        b2Body* GetBodyList()
        {
            return World->GetBodyList();
        }

        unsigned int GetBodyCount()
        {
            return World->GetBodyCount();
        }

        b2World* GetWorld()
        {
            return World;
        }

        friend class Engine;
    };

    struct Actor
    {

    };

    struct Solid
    {

    };

    struct Player
    {
        const float MaxJumpHeight = 0.1f;
        const float MaxFallSpeed = 0.1f;
        const float Gravity = 90.0f;
        const float DecelerationSpeed = 0.1f;

        void Update(const std::size_t& ID, Registry& reg, bool collision);
          
        void Jump(const float& amount);

        void Render();
    };

    std::size_t CreateEntity()
    {
    	static std::size_t Entities = 0;
    	++Entities;

    	MaxEntities = Entities;
    	return Entities;
    }
};














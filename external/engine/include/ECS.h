#pragma once
//STL
#include <unordered_map>
//box2D
#include <box2d/b2_math.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

#include "Debug.h"

enum PlayerMoveX
{
    MOVE_LEFT = -1,
    STOP = 0,
    MOVE_RIGHT = 1
};

enum Material
{
    Stone = 0,
    Glass = 1,
    Ice = 2
};

struct Component
{
    struct Box2DUserData
    {
        std::size_t ECS_ID;
        Material MATERIAL_ID;
        bool GroundCheck;
    };

    struct Physics
    {
        b2Body* body;

        struct Actor
        {    
            b2Vec2 SmoothedPosition;
            b2Vec2 PreviousPosition;
            
            void b2BodyToInterpolation(b2Body*& body);
        };

        struct Solid
        {
            Material Mat;
        };
    };

    struct Player
    {
        b2Vec2 Dimensions;
        b2Vec2 Velocity; 
        PlayerMoveX MoveState;

        int DoubleJump;
        int GroundContacts;
    };
};

struct Registry
{
    std::unordered_map<std::size_t, Component::Player> regPlayer;
    std::unordered_map<std::size_t, Component::Physics> regPhysics;
    std::unordered_map<std::size_t, Component::Physics::Actor> regActor;
    std::unordered_map<std::size_t, Component::Physics::Solid> regSolid; 
    std::unordered_map<std::size_t, Component::Box2DUserData> regUser;
};
struct System 
{
    struct Physics
    {
    private:
        int32_t VelocityIterations;
        int32_t PositionIterations;

        float TimestepAccumulator;
        float TimestepAccumulatorRatio;
    public:
        b2World* World;
        float FixedTimestep;
        void Update(float& Dt, Registry& reg);
        void Interpolate(Registry& reg, const double& alpha);
    public:
        Physics(const float& timestepFixed, const float& gravity);

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
    };

    struct Player
    {
        const float MaxJumpHeight = 0.1f;
        const float MaxFallSpeed = 0.1f;
        const float Gravity = 90.0f;
        const float DecelerationSpeed = 0.1f;

        void Update(const std::size_t& ID, Registry& reg, bool collision, b2World* world, DebugDrawSDL& debug);
          
        void Jump(const float& amount);

        void Render();
    };
};














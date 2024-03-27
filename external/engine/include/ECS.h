#pragma once
//STL
#include <unordered_map>
//box2D
#include <box2d/b2_math.h>
#include <box2d/b2_body.h>

enum PlayerMoveState
{
    MOVE_LEFT = -1,
    STOP = 0,
    MOVE_RIGHT = 1
};

struct GameActor
{
    b2Vec2 SmoothedPosition;
    b2Vec2 PreviousPosition;

    void b2BodyToInterpolation(b2Body*& body);
    
    b2Body* Body;
};

struct GameSolid
{
    b2Body* Body;
};

struct Component
{
    struct Physics
    {
        GameActor Actor;
        GameSolid Solid;
        bool isActor;
    };

    struct Player
    {
        b2Vec2 Acceleration;
        b2Vec2 Velocity;

        PlayerMoveState MoveState;

        b2RayCastInput GroundCheck;
    };
};

struct Registry
{
    std::unordered_map<std::size_t, Component::Physics> regPhysics;
    std::unordered_map<std::size_t, Component::Player> regPlayer;
};

struct System
{
    std::size_t MaxEntities;

    struct Physics
    {
        void Update();
    };

    struct Player
    {
        const float MaxJumpHeight = 0.1f;
        const float MaxFallSpeed = 0.1f;
        const float Gravity = 90.0f;
        const float DecelerationSpeed = 0.1f;

        void Update(const std::size_t& ID, Registry& reg);
        
        bool GroundCollisionCheck(const std::size_t& ID);
        bool CollisionCheck(const std::size_t& ID);
        
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














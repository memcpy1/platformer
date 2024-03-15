#pragma once
//STL
#include <unordered_map>
//box2D
#include <box2d/b2_math.h>
#include <box2d/b2_body.h>

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

        
    };
};

struct Registry
{
    std::unordered_map<std::size_t, Component::Physics> regPhysics;
};

struct System
{
    std::size_t MaxEntities;

    struct Physics
    {
        void Update();
    };

    std::size_t CreateEntity()
    {
    	static std::size_t Entities = 0;
    	++Entities;

    	MaxEntities = Entities;
    	return Entities;
    }
};














#pragma once
//STL
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <fstream>
//box2D
#include <box2d/b2_math.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

#include "Debug.h"
#include "Timer.h"

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

struct SpriteAttrib
{
	int ClipNumber;
	int ClipHeight;
	int ClipWidth;				//Width of a single clip.
	int ClipsInRow;
	
	SDL_Rect* spriteClips; 
};


struct Component
{
    struct Visual
    {   
        std::size_t TextureID;
        b2Vec2 TextureDimensions;
        SDL_Rect Dst;

        unsigned int Frames;
        unsigned int CurrentFrame;
        
        int Delay;
    };

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

        SDLTimer JumpTime;
        SDLTimer CoyoteTime;
        unsigned int DoubleJump;
        int GroundContacts;
    };
};

struct Registry
{
    std::unordered_map<std::size_t, Component::Visual> regGraphics;
    std::unordered_map<std::size_t, Component::Player> regPlayer;
    std::unordered_map<std::size_t, Component::Physics> regPhysics;
    std::unordered_map<std::size_t, Component::Physics::Actor> regActor;
    std::unordered_map<std::size_t, Component::Physics::Solid> regSolid; 
    std::unordered_map<std::size_t, Component::Box2DUserData> regUser;
};
struct System 
{
    struct Visual
    {
    private:
	    std::unordered_map<std::size_t, SDL_Texture*> TextureMap;
	    std::unordered_map<std::size_t, SDL_Rect*> SpriteMap;

        unsigned int TextureCount = 0;
    public:
	    const std::size_t& LoadFromFile(const std::size_t& ID, const char* path);
	    void Drop(const std::size_t& ID);

	    void RenderTexture(const std::size_t& ID, const SDL_Rect& pDst, const float& angle, SDL_Point* center,
	    SDL_RendererFlip flip);
	    void RenderSprite(const std::size_t& ID, const int& spriteIndex, const b2Vec2& vec2, const double& angle, 
	    SDL_Point* center, SDL_RendererFlip flip);

	    void SetBlending(const std::size_t& ID, const SDL_BlendMode& blend);	
	    void SetAlpha(const std::size_t& ID, const Uint8& alpha);	
	    void Tint(const std::size_t& ID, const SDL_Color& tint);
	
	    std::size_t LoadSpriteSheetFromFile(const std::size_t ID, const std::string& filepath, const int& pClipNumber, const int& pClipHeight, const int& pClipWidth, 
	    const int& pClipsInARow);
	    void PlayAnimation(const std::size_t& ID, const SDL_Rect& dst, const int& frames, const int& delay, 
	    const double& angle, SDL_Point* center, SDL_RendererFlip flip);

	    SDL_Texture* GetTexturePtr(const std::size_t& ID);

        const std::size_t GenTextureID()
        {
            static std::size_t Texture;
            ++Texture;

            TextureCount = Texture;
            return Texture;
        }
    
	    ~Visual();
        Visual() {}
    public:
        void Render(Registry& reg);
        void Update(Registry& pReg);
    };
    

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

    struct Input
    {
        void Listen(Registry& reg, const std::size_t& ID);
    };

    struct Player
    {
        const float MaxJumpHeight = 0.1f;
        const float MaxFallSpeed = 0.1f;
        const float Gravity = 90.0f;
        const float DecelerationSpeed = 0.1f;

        void Update(const std::size_t& ID, Registry& reg, bool collision, b2World* world, DebugDrawSDL& debug);
          
        void Jump(const float& amount);
    };
};














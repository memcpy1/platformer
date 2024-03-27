#pragma once
//STL
#include <iostream>
#include <string>
//vendor
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
//Engine
#include "Timer.h"
#include "Physics.h"
#include "Debug.h"
#include "Event.h"
#include "ECS.h"
//#include "Globals.h"
//box2D
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

class Engine
{
private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    static Engine* sInstance;
    
    Registry EngineRegistry;
    System EngineSystem;
    System::Player PlayerSystem;
    EventHandler KeyboardInput;

    PhysicsWorld* PhysicsSystem;
    float Gravity;

    std::size_t Player;

    DebugDrawSDL PhysicsDebugger;

    unsigned int Width;
    unsigned int Height;

    SDLTimer EngineTimer;
    SDLTimer FPSLimiter;
    float FPS;
    uint32_t FrameCount = 0;

    uint64_t CurrentTick;
    uint64_t LastTick;
    float DeltaTime;

    bool Running = 1;
public:
    float FixedFPS = 120.0f;
    float TicksPerFrame = 1000.0f / FixedFPS;
public:
    static Engine* Get();
    bool Initialize(std::string title, const unsigned int& width, const unsigned int& height);

    void Update();
    void PollEvents();
    void Render();
    void Quit();

    void ToggleVisualDebugging();

    bool IsRunning();
    SDLTimer* GetTimer();
    SDL_Renderer* GetRenderer();
    SDL_Surface* GetWindowSurface();

    b2Vec2 SDLBox2D(const b2Vec2& vec2);
	b2Vec2 Box2DSDL(const b2Vec2& vec2);
	float Box2DSDLf(const float& f);
	float SDLBox2Df(const float& f);

    //ECS
    std::size_t RegisterSolid(const b2Vec2& position, const b2Vec2& dimensions);
    std::size_t RegisterActor(const b2Vec2& position, const b2Vec2& dimensions, const bool& kinematic, const float& angle, const float& density, const float& frictionCoeff);
    std::size_t RegisterPlayer(const b2Vec2& position, const b2Vec2& dimensions);
    std::size_t GetMaxEntity();
private:
    Engine() 
        : PhysicsSystem(new PhysicsWorld(1.0f / FPS, Gravity)){};

    friend System::Player;
};
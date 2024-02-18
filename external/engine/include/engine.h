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

class Engine
{
private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    static Engine* sInstance;
    
    unsigned int Width;
    unsigned int Height;

    Timer EngineTimer;
public:
    static Engine* Get();
    bool Initialize(std::string title, const unsigned int& width, const unsigned int& height);

    Timer* GetTimer();

private:
    Engine() {};
};

void printff();
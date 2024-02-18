//STL
#include <iostream>
#include <string>
//vendor
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Engine
{
private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;

    unsigned int Width;
    unsigned int Height;
public:
    bool Initialize(std::string title, const unsigned int& width, const unsigned int& height);
    void Printf();
};
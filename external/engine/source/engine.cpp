#include <Engine.h>

bool Engine::Initialize(std::string title, const unsigned int& width, const unsigned int& height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "[SDL2]: Initalization failed   : " << SDL_GetError() << '\n';
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "[SDL_image]: IMG_Init() failed  :" << IMG_GetError() << '\n';
        return false;
    }
    if (TTF_Init() == -1)
    {
        std::cout << "[SDL_TTF]: TTF_Init() failed   : " << TTF_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        std::cout << "[SDL_mixer]: Mix_OpenAudio() failed   : " << Mix_GetError() << std::endl;
        return false;
    }

    Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!Window)
    {
        __debugbreak();
        std::cout << "[SDL_CreateWindow]: Could not create window   : " << SDL_GetError() << std::endl;
        return false;
    }

    
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
    if (!Renderer)
    {
        std::cout << "[SDL2]: Renderer creation failed!   : " << SDL_GetError() << std::endl;
        return false;
    }

    Width = width;
    Height = height;
    
    return true;
}

void Engine::Printf()
{
    std::cout << "a" << '\n';
}
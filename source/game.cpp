#include <Engine.h>
#include <stdlib.h>
#undef main

int main()
{
    Engine::Get()->Initialize("game", 1280, 720);
    
    bool running = 1;
    SDL_Event sdl;
    
    while (running)
    {
        while (SDL_PollEvent(&sdl) != 0)
        {
            switch (sdl.type)
            {
                case SDL_QUIT:
                    running = 0;
                break;
                case SDL_KEYDOWN:
                    Engine::Get()->GetTimer()->Start();
                break;
                case SDL_MOUSEBUTTONDOWN:
                    Engine::Get()->GetTimer()->Pause();
                break;
            }
        }

        std::cout << Engine::Get()->GetTimer()->GetMilliseconds() << '\n';
    }
} 
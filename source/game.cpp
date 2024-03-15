#include <Engine.h>
#include <stdlib.h>
#undef main

int main()
{
    Engine::Get()->Initialize("game", 1280, 720);
    

    SDL_Event sdl;
    
    while (Engine::Get()->IsRunning())
    {
        while (SDL_PollEvent(&sdl) != 0)
        {
            switch(sdl.type)
            {
                case SDL_KEYDOWN:
                    Engine::Get()->GetTimer()->Pause();
                case SDL_QUIT:
                    Engine::Get()->Quit();
                break;
            }
        }
        
        Engine::Get()->Update();
        Engine::Get()->Render();
    }
} 
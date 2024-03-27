#pragma once
#include <SDL.h>
 
class EventHandler
{
private:
    SDL_Event Event;
    const uint8_t* Keystates;
public:
    static EventHandler* GetInstance();
 
    void Poll();
    bool IsKeyDown(SDL_Scancode key);
    EventHandler();
private:
    void KeyDown();
    void KeyUp();        
};
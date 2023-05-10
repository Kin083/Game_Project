
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Engine.h"
#include "TextureManage.h"
#include "Timer.h"

int main(int argc, char* argv[])
{
    Engine::GetInstance()->Init();
    while (Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();
    return 0;
}

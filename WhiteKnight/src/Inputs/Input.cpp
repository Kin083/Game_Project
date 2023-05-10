#include "Input.h"
#include "Play.h"
#include "Engine.h"

Input* Input::s_Instance = nullptr;

Input::Input()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: Engine::GetInstance()->Quit(); break;
            case SDL_KEYDOWN:
                KeyDown();
                switch( event.key.keysym.sym )
                {
                    case SDLK_1: Engine::GetInstance()->SetIsPlay(); break;
                    case SDLK_2: Engine::GetInstance()->SetIsMenu(); break;
                }
                break;

            case SDL_KEYUP: KeyUp(); break;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat == 0)
        {
            m_ButtonDown = true;
        }
        else
        {
            m_ButtonDown = false;
        }
    }

}


bool Input::GetKeyDown(SDL_Scancode key)
{
    if (m_KeyStates[key] == 1)
        return true;
    return false;
}

bool Input::GetMouseButtonDown()
{
    return m_ButtonDown;
}

void Input::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

// return 1 or -1 according to the direction of the key pressed or 0 if nothing is pressed
int Input::GetAxisKey(Axis axis)
{
    switch(axis)
    {
        case HORIZONTAL:
            if (GetKeyDown(SDL_SCANCODE_D))
                return 1;
            if (GetKeyDown(SDL_SCANCODE_A))
                return -1;
            break;

        case VERTICAL:
            if (GetKeyDown(SDL_SCANCODE_W))
                return 1;
            if (GetKeyDown(SDL_SCANCODE_S))
                return -1;
            break;

        default:
            return 0;
    }
}

int Input::GetAxisKey2(Axis axis)
{
    switch(axis)
    {
        case HORIZONTAL:
            if (GetKeyDown(SDL_SCANCODE_RIGHT))
                return 1;
            if (GetKeyDown(SDL_SCANCODE_LEFT))
                return -1;
            break;

        case VERTICAL:
            if (GetKeyDown(SDL_SCANCODE_UP))
                return 1;
            if (GetKeyDown(SDL_SCANCODE_DOWN))
                return -1;
            break;

        default:
            return 0;
    }
}

Vector2D Input::GetMousePosition()
{
    Vector2D mouse = NULL;
    int x, y;
    SDL_GetMouseState(&x, &y);
    mouse.X = x;
    mouse.Y = y;
    return mouse;
}





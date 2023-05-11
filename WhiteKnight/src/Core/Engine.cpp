#include "Engine.h"

#include "TextureManage.h"
#include "Input.h"
#include "Warrior.h"
#include "Enemy.h"
#include "Timer.h"
#include <iostream>
#include "Camera.h"
#include "CollisionHandler.h"
#include <SDL_mixer.h>
#include "SoundMgr.h"
#include <SDL_ttf.h>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    m_Window = SDL_CreateWindow("Super Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (m_Window == nullptr)
    {
        SDL_Log("Failed to initialize Window: %s\n", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr)
    {
        SDL_Log("Failed to initialize Renderer: %s\n", SDL_GetError());
        return false;
    }

    Menu::GetInstance()->Init();
    Play::GetInstance()->Init();
    MenuPause::GetInstance()->Init();
    GameOver::GetInstance()->Init();

    SoundMgr::GetInstance()->LoadMusic("Opening", "assets/Sounds/M_Opening1.mp3");
    SoundMgr::GetInstance()->LoadMusic("Playing", "assets/Sounds/M_Playing.mp3");
    SoundMgr::GetInstance()->LoadMusic("W_Ending", "assets/Sounds/M_W_Ending.mp3");
    SoundMgr::GetInstance()->LoadMusic("L_Ending", "assets/Sounds/M_L_Ending.mp3");

    SoundMgr::GetInstance()->PlayMusic("Opening");
    m_IsRunning = true;
}

void Engine::Update()
{
    if (m_IsPlay)
        Play::GetInstance()->Update();
}

void Engine::Render()
{
    SDL_Delay(2);
    if (m_IsPlay)
    {
        Play::GetInstance()->Render();
    }
    if (m_IsMenu)
    {
        Menu::GetInstance()->Render();
    }
    if (m_IsPause)
        MenuPause::GetInstance()->Render();
    if (m_IsOver)
        GameOver::GetInstance()->Render();
}

void Engine::Events()
{
    Play::GetInstance()->Events();
}

void Engine::Clean()
{
    Play::GetInstance()->Clean();
    Menu::GetInstance()->Clean();
    MenuPause::GetInstance()->Clean();
    GameOver::GetInstance()->Clean();

    TextureManage::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

}

void Engine::SetIsPlay(bool isplay)
{
    m_IsPlay = isplay;
}

void Engine::SetIsMenu(bool ismenu)
{
    m_IsMenu = ismenu;
}

void Engine::SetIsEngine(bool isengine)
{
    m_IsRunning = isengine;
}

void Engine::SetIsPause(bool ispause)
{
    m_IsPause = ispause;
}

void Engine::SetIsOver(bool isover)
{
    m_IsOver = isover;
    if (m_IsOver)
    {
        m_IsMenu = false;
        m_IsPause = false;
        m_IsPlay = false;
    }
}


void Engine::Quit()
{
    m_IsRunning = false;
}

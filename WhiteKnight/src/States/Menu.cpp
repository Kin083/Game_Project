#include "Menu.h"
#include "TextureManage.h"
#include "SoundMgr.h"

Menu* Menu::s_Instance = nullptr;

bool Menu::Init()
{
    m_Renderer = Engine::GetInstance()->GetRenderer();

    TextureManage::GetInstance()->Load("Start", "assets/Menu/Button/Start.png");
    TextureManage::GetInstance()->Load("Exit", "assets/Menu/Button/Exit.png");
    TextureManage::GetInstance()->Load("BG", "assets/Menu/_Menu1.jpg");

    SoundMgr::GetInstance()->LoadEffect("click", "assets/Sounds/click.wav");
    SoundMgr::GetInstance()->LoadEffect("hover", "assets/Sounds/blop.wav");
    m_Starte = new Button(new Properties("Start", 540 ,  485, 143, 143));
    m_Exit = new Button(new Properties("Exit", 540 + 200 ,  485 , 143, 143));


}

void Menu::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    int dt = 1.2;
    TextureManage::GetInstance()->Draw("BG", 0, 0, 1409, 800, 1, 1, 0);
    m_Starte->Update(dt);
    m_Exit->Update(dt);

    m_Exit->Draw();
    m_Starte->Draw();

    if (m_Starte->GetIsPressed())
    {
        Engine::GetInstance()->SetIsMenu(false);
        Engine::GetInstance()->SetIsPlay(true);
        SoundMgr::GetInstance()->PlayMusic("Playing");
    }
    if (m_Exit->GetIsPressed())
    {
        Engine::GetInstance()->SetIsEngine(false);
    }

    SDL_RenderPresent(m_Renderer);
}

void Menu::Clean()
{
    m_Renderer = nullptr;
}


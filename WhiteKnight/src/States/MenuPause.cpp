#include "MenuPause.h"
#include "TextureManage.h"


MenuPause* MenuPause::s_Instance = nullptr;

bool MenuPause::Init()
{
    m_Renderer = Engine::GetInstance()->GetRenderer();

    TextureManage::GetInstance()->Load("MenuPause", "assets/Menu/Button/Menu_Pause.png");
    TextureManage::GetInstance()->Load("Resume", "assets/Menu/Button/B_Resume.png");
    TextureManage::GetInstance()->Load("B_Exit", "assets/Menu/Button/B_Exit.png");
    TextureManage::GetInstance()->Load("Restart", "assets/Menu/Button/B_Restart.png");

    m_Resume = new Button(new Properties("Resume", 578 , 220, 252, 108));
    m_Restart = new Button(new Properties("Restart", 578 , 220 + 162, 252, 108));
    m_Exit = new Button(new Properties("B_Exit", 578 ,  220 + 162 * 2 , 252, 108));
}

void MenuPause::Render()
{
    int dt = 1.2;
    TextureManage::GetInstance()->Draw("MenuPause", 429, 30, 550, 740, 1, 1, 0);
    m_Resume->Update(dt);
    m_Restart->Update(dt);
    m_Exit->Update(dt);

    m_Resume->Draw();
    m_Restart->Draw();
    m_Exit->Draw();

    if (m_Resume->GetIsPressed())
    {
        Engine::GetInstance()->SetIsPause(false);
        Engine::GetInstance()->SetIsPlay(true);
    }
    if (m_Restart->GetIsPressed())
    {
        Play::GetInstance()->Clean();
        Play::GetInstance()->InitAgain();
        Engine::GetInstance()->SetIsPause(false);
        Engine::GetInstance()->SetIsPlay(true);
    }
    if (m_Exit->GetIsPressed())
    {
        Engine::GetInstance()->SetIsEngine(false);
    }

    SDL_RenderPresent(m_Renderer);
}

void MenuPause::Clean()
{
    m_Renderer = nullptr;
}

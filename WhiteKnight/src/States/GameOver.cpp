#include "GameOver.h"
#include "TextureManage.h"
#include "SoundMgr.h"
GameOver* GameOver::s_Instance = nullptr;

bool GameOver::Init()
{
    m_Renderer = Engine::GetInstance()->GetRenderer();

    TextureManage::GetInstance()->Load("Lose", "assets/Menu/GameOver/_Lose.jpg");
    TextureManage::GetInstance()->Load("Win", "assets/Menu/GameOver/_Win.jpg");
    TextureManage::GetInstance()->Load("PlayAgain", "assets/Menu/GameOver/PlayAgain.png");

    m_PlayAgain = new Button(new Properties("PlayAgain", 540 ,  485, 143, 143));
    m_Exit = new Button(new Properties("Exit", 540 + 200 ,  485 , 143, 143));
}

void GameOver::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    int dt = 1.2;
    if (m_IsWin) TextureManage::GetInstance()->Draw("Win", 0, 0, 1408, 800, 1, 1, 0);
    else TextureManage::GetInstance()->Draw("Lose", 0, 0, 1408, 800, 1, 1, 0);
    m_PlayAgain->Update(dt);
    m_Exit->Update(dt);

    m_PlayAgain->Draw();
    m_Exit->Draw();

    if (m_PlayAgain->GetIsPressed())
    {
        Play::GetInstance()->Clean();
        Play::GetInstance()->InitAgain();
        Engine::GetInstance()->SetIsOver(false);
        Engine::GetInstance()->SetIsPlay(true);
        SoundMgr::GetInstance()->PlayMusic("Playing");
    }

    if (m_Exit->GetIsPressed())
    {
        Engine::GetInstance()->SetIsEngine(false);
    }

    SDL_RenderPresent(m_Renderer);
}

void GameOver::Clean()
{
    m_Renderer = nullptr;
}

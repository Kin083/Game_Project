#include "Play.h"
#include "TextureManage.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "MenuPause.h"
#include "GameOver.h"
#include "SoundMgr.h"
#include "TextMgr.h"
#include <stdlib.h>
#include <sstream>
#include <ctime>

Play* Play::s_Instance = nullptr;

bool Play::Init()
{
    m_Renderer = Engine::GetInstance()->GetRenderer();

    TextureManage::GetInstance()->Load("sky", "assets/Maps/Plains_Asset_Pack/Background/sky.png");
    TextureManage::GetInstance()->Load("cloud","assets/Maps/Plains_Asset_Pack/Background/cloud.png");
    TextureManage::GetInstance()->Load("mountain", "assets/Maps/Plains_Asset_Pack/Background/mountain.png");
    TextureManage::GetInstance()->Load("mist", "assets/Maps/Plains_Asset_Pack/Background/mist.png");
    TextureManage::GetInstance()->Load("hill", "assets/Maps/Plains_Asset_Pack/Background/hill.png");
    TextureManage::GetInstance()->Load("forest", "assets/Maps/Plains_Asset_Pack/Background/forest.png");
    TextureManage::GetInstance()->Load("foreground", "assets/Maps/Plains_Asset_Pack/Background/foreground.png");

    TextureManage::GetInstance()->Load("ground", "assets/Maps/s_4.png");

    TextureManage::GetInstance()->Load("player_idle", "assets/Warriors/Knight_1/_Idle.png");
    TextureManage::GetInstance()->Load("player_run", "assets/Warriors/Knight_1/_Run.png");
    TextureManage::GetInstance()->Load("player_jump", "assets/Warriors/Knight_1/_Jump.png");
    TextureManage::GetInstance()->Load("player_fall", "assets/Warriors/Knight_1/_Fall.png");
    TextureManage::GetInstance()->Load("player_attack", "assets/Warriors/Knight_1/_Attack 1.png");
    TextureManage::GetInstance()->Load("player_defend", "assets/Warriors/Knight_1/_Defend.png");
    TextureManage::GetInstance()->Load("player_hurt", "assets/Warriors/Knight_1/_Hurt.png");

    TextureManage::GetInstance()->Load("cnv_plant", "assets/Boss/RPG Maker MV format Animated Sideview Battlers/Carnivorous Plant Cathy/carnivorousplant.png");
    TextureManage::GetInstance()->Load("cnv_plant_attack", "assets/Boss/RPG Maker MV format Animated Sideview Battlers/Carnivorous Plant Cathy/attack.png");
    TextureManage::GetInstance()->Load("cnv_plant_died", "assets/Boss/RPG Maker MV format Animated Sideview Battlers/Carnivorous Plant Cathy/died.png");
    TextureManage::GetInstance()->Load("bod_idle", "assets/Boss/Bringer-Of-Death/SpriteSheet/Idle.png");
    TextureManage::GetInstance()->Load("bod_walk", "assets/Boss/Bringer-Of-Death/SpriteSheet/Walk.png");
    TextureManage::GetInstance()->Load("bod_attack", "assets/Boss/Bringer-Of-Death/SpriteSheet/_Attack.png");
    TextureManage::GetInstance()->Load("bod_hurt", "assets/Boss/Bringer-Of-Death/SpriteSheet/Hurt.png");
    TextureManage::GetInstance()->Load("bod_died", "assets/Boss/Bringer-Of-Death/SpriteSheet/_Died.png");

    TextureManage::GetInstance()->Load("Pause", "assets/Menu/Button/Pause.png");
    TextureManage::GetInstance()->Load("B_Sound", "assets/Menu/Button/Sound.png");
    TextureManage::GetInstance()->Load("Slash", "assets/Menu/Button/Slash.png");

    TextureManage::GetInstance()->Load("HP_0", "assets/Menu/Status/HP0.png");
    TextureManage::GetInstance()->Load("HP_1", "assets/Menu/Status/HP1.png");
    TextureManage::GetInstance()->Load("HP_2", "assets/Menu/Status/HP2.png");
    TextureManage::GetInstance()->Load("Avt", "assets/Menu/Status/_avt.jpg");

    SoundMgr::GetInstance()->LoadEffect("jump", "assets/Sounds/Jump.wav");
    SoundMgr::GetInstance()->LoadEffect("attack", "assets/Sounds/Player_Attack.wav");
    SoundMgr::GetInstance()->LoadEffect("p_attack", "assets/Sounds/_Plant_Attack.wav");
    SoundMgr::GetInstance()->LoadEffect("b_attack", "assets/Sounds/_Boss_Attack.wav");
    SoundMgr::GetInstance()->LoadEffect("hurt", "assets/Sounds/hurt.wav");
    SoundMgr::GetInstance()->LoadEffect("died", "assets/Sounds/died.wav");
    SoundMgr::GetInstance()->LoadEffect("block", "assets/Sounds/block.wav");
    SoundMgr::GetInstance()->LoadEffect("B_Hurt", "assets/Sounds/B_Hurt.wav");
    SoundMgr::GetInstance()->LoadEffect("B_Died", "assets/Sounds/B_Died.wav");
    SoundMgr::GetInstance()->LoadEffect("plant_died", "assets/Sounds/plant_died.wav");

    m_Warrior = new Warrior(new Properties("player_idle", 0, 0, 240, 240));

    srand(time(0));

    for (int i = 0; i < 6; i++)
    {
        int rd = rand() % 300;
        Enemy* boss = new Enemy(new Properties("cnv_plant", 1000 + 1000 * i + rd, -256, 256, 256));
        m_Enemies.push_back(boss);
    }
    Enemy* death = new Enemy(new Properties("bod_idle", 7300, 200, 336, 208));
    death->SetCollider(280, 208);
    death->SetBuffer(-115, -80, 220, 100);
    death->SetAnimaState(1);
    death->SetSpeedWalk(2);
    death->SetHP(540);
    m_Enemies.push_back(death);
    m_alive = true;

    m_Pause = new Button(new Properties("Pause", SCREEN_WIDTH - 87, 8, 80, 80));
    m_BSound = new Button(new Properties("B_Sound", SCREEN_WIDTH - 87 - 100, 8, 80, 80));
    Camera::GetInstance()->SetTarget(m_Warrior->GetOrigin());
    return m_IsRunning = true;
}


void Play::Update()
{
    double dt = Timer::GetInstance()->GetDeltaTime();
    dt = 1.2;
    m_Pause->Update(dt);
    m_BSound->Update(dt);

    if (m_Pause->GetIsPressed())
    {
        Engine::GetInstance()->SetIsMenu(false);
        Engine::GetInstance()->SetIsPlay(false);
        Engine::GetInstance()->SetIsPause(true);
    }
    if (Timer::GetInstance()->Wait(100, BSound_Time))
    {
        if (m_BSound->GetIsPressed())
        {
            SoundMgr::GetInstance()->SetOnSounds();
        }
    }
    if (SoundMgr::GetInstance()->GetOnSound())
    {
        if (Mix_PausedMusic() == 1)
            Mix_ResumeMusic();
    }
    else
    {
        if (!(Mix_PausedMusic() == 1))
            Mix_PauseMusic();
    }

    for(unsigned int i = 0; i < m_Enemies.size(); i++)
    {
        if (m_Warrior->GetIsAttacking())
        {
            if (CollisionHandler::GetInstance()->CheckCollision(m_Warrior->GetColliderAttacking()->Get(), m_Enemies[i]->GetCollider()->Get()) && Timer::GetInstance()->Wait(100, m_Warrior->Time_Attack) && m_Warrior->GetCurrentFrame() == 1)
            {
                m_Enemies[i]->m_DiedTime = SDL_GetTicks();
                m_Enemies[i]->MinusHP(80);
                m_Enemies[i]->SetHurt(true);
                SoundMgr::GetInstance()->PlayEffect("B_Hurt");
            }
            if (m_Enemies[i]->GetHP() <= 0)
            {
                m_Enemies[i]->SetDied();
                m_Enemies[i]->SetAttack(false);
            }
        }

        if (!m_Enemies[i]->GetIsDied())
        {
            if (abs(m_Enemies[i]->GetOrigin()->X - m_Warrior->GetOrigin()->X) < 100 && m_alive)
            {
                m_Enemies[i]->SetAttack(true);
            }
            else
            {
                m_Enemies[i]->SetAttack(false);
            }
            if (m_Enemies[i] && m_Enemies[i]->GetIsAttacking())
            {
                if (CollisionHandler::GetInstance()->CheckCollision(m_Enemies[i]->GetColliderAttacking()->Get(), m_Warrior->GetCollider()->Get()) && m_Enemies[i]->GetCurrentFrame() == 1)
                {
                    if (Timer::GetInstance()->Wait(600, m_Enemies[i]->Time_Attack)) {
                        if (!m_Enemies[i]->GetIsHurt())
                        {
                            if (m_Warrior->GetIsDefend()) SoundMgr::GetInstance()->PlayEffect("block");
                            else
                            {
                                if (m_Enemies[i]->GetAnimaState() == 1) SoundMgr::GetInstance()->PlayEffect("b_attack");
                                else SoundMgr::GetInstance()->PlayEffect("p_attack");
                                m_Warrior->MinusHP(40);
                                m_Warrior->SetIsHurt(true);
                                SoundMgr::GetInstance()->PlayEffect("hurt");
                            }
                        }
                    }
                    if (m_Warrior->GetHP() <= 0)
                    {
                        m_alive = false;
                    }
                }
            }
        }

        m_Enemies[i]->Update(dt);
        if (m_Enemies[i]->GetIsDied() && SDL_GetTicks() - m_Enemies[i]->m_DiedTime > 1000)
        {
            m_Score += 10;
            m_Enemies.erase(m_Enemies.begin() + i);
        }
    }
    if (m_Warrior->GetOrigin()->Y > SCREEN_HEIGHT + 50)
    {
        m_alive = false;
    }

    if (m_alive == false)
    {
        SoundMgr::GetInstance()->PlayEffect("died");
        SDL_Delay(400);
        GameOver::GetInstance()->setIsWin(false);
        Engine::GetInstance()->SetIsOver(true);
        SoundMgr::GetInstance()->PlayMusic("L_Ending");
    }
    if (m_alive == true && m_Warrior->GetOrigin()->X >= SCREEN_WIDTH * 6 - 50)
    {
        SDL_Delay(400);
        GameOver::GetInstance()->setIsWin(true);
        Engine::GetInstance()->SetIsOver(true);
        SoundMgr::GetInstance()->PlayMusic("W_Ending");
    }
    if (m_alive) m_Warrior->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Play::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    TextureManage::GetInstance()->Draw("sky", 0, 0, 1408, 648, 1, 1, 0);
    TextureManage::GetInstance()->DrawBG2("cloud", x_cloud, 32, 2304, 303, 1, 1, 0.1, 1.2);
    TextureManage::GetInstance()->DrawBG("mountain", 0, 5 * 32, 1532, 182, 1, 1, 0.17);
    TextureManage::GetInstance()->DrawBG2("mist", x_cloud, 7 * 32, 1536, 160, 1, 1, 0.15, 0);
    TextureManage::GetInstance()->DrawBG("hill", 0, 8 * 32, 1728, 349, 1, 1, 0.22);
    TextureManage::GetInstance()->DrawBG("forest", 0, 12 * 32, 1856, 279, 1, 1, 0.28);
    TextureManage::GetInstance()->DrawBG("foreground", 0, 9 * 32, 2154, 517, 1, 1, 0.37);

    TextureManage::GetInstance()->DrawBG("ground", 0, 32, 1408 * 2, 800, 1, 1, 1);

    m_Pause->Draw();
    m_BSound->Draw();
    if (!SoundMgr::GetInstance()->GetOnSound()) TextureManage::GetInstance()->Draw("Slash",SCREEN_WIDTH - 92 - 100, 11, 84, 79);

    TextureManage::GetInstance()->Draw("Avt", 10, 10 , 80, 80);
    TextureManage::GetInstance()->Draw("HP_0", 10, 100, 270, 19);
    TextureManage::GetInstance()->Draw("HP_1", 10, 100, m_Warrior->GetHP(), 19);
    TextureManage::GetInstance()->Draw("HP_2", 5, 94, 280, 31);

    for(unsigned int i = 0; i < m_Enemies.size(); i++)
    {
        m_Enemies[i]->Draw();
    }
    if (m_alive) m_Warrior->Draw();

    std::string score;
    std::stringstream ss;
    ss.str("");
    ss << m_Score;
    score = "Score: " + ss.str();
    TextMgr::GetInstance()->RenderText(score, 114, 67);

    SDL_RenderPresent(m_Renderer);
}

void Play::Events()
{
    Input::GetInstance()->Listen();
}

void Play::Clean()
{
    delete m_Warrior;
    for (int i = 0; i < m_Enemies.size(); i++)
    {
        delete m_Enemies[i];
    }
    m_Enemies.clear();
}

bool Play::InitAgain()
{
    m_Warrior = new Warrior(new Properties("player_idle", 0, 0, 240, 240));
    m_Warrior->SetHP(270);
    m_Score = 0;
    m_alive = true;
    for (int i = 0; i < 6; i++)
    {
        int rd = rand() % 300;
        Enemy* boss = new Enemy(new Properties("cnv_plant", 1000 + 1000 * i + rd, -256, 256, 256));
        m_Enemies.push_back(boss);
    }
    Enemy* death = new Enemy(new Properties("bod_idle", 7400, 200, 336, 208));
    death->SetCollider(280, 208);
    death->SetBuffer(-115, -80, 220, 100);
    death->SetAnimaState(1);
    death->SetSpeedWalk(2);
    death->SetHP(540);
    m_Enemies.push_back(death);
    Camera::GetInstance()->SetTarget(m_Warrior->GetOrigin());
    return m_IsRunning = true;
}






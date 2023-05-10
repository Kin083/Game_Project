#ifndef Play_H
#define Play_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameMap.h"
#include "GameObject.h"
#include "Warrior.h"
#include "Enemy.h"
#include "Engine.h"
#include "Button.h"

class Play
{
    public:
        static Play* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Play();
        }

        bool Init();
        bool InitAgain();
        void Clean();

        void Update();
        void Render();
        void Events();

        inline bool IsRunning() {return m_IsRunning;}
        inline SDL_Renderer* GetRenderer() {return m_Renderer;}

    private:
        Play(){}
        bool m_IsRunning;
        SDL_Renderer* m_Renderer;
        static Play* s_Instance;
        Warrior* m_Warrior;
        bool m_alive;
        int m_Score = 0;
        std::vector<Enemy*> m_Enemies;
        int x_cloud = 0;
        Button* m_Pause;
        Button* m_BSound;
        double BSound_Time = 0;
};

#endif // Play_H

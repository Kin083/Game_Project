#ifndef Engine_H
#define Engine_H

#include "Play.h"
#include "Menu.h"
#include "MenuPause.h"
#include "GameOver.h"

#define SCREEN_WIDTH 1408
#define SCREEN_HEIGHT 800

class Engine
{
    public:
        static Engine* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
        }

        inline bool IsRunning() {return m_IsRunning;}

        bool Init();
        void Clean();
        void Quit();

        void SetIsPlay(bool isplay = true);
        void SetIsMenu(bool ismenu = true);
        void SetIsPause(bool ispause = true);
        void SetIsOver(bool isover);

        void SetIsEngine(bool isengine = true);

        void Update();
        void Render();
        void Events();

        inline SDL_Window* GetWindow() {return m_Window;}
        inline SDL_Renderer* GetRenderer() {return m_Renderer;}

    private:
        Engine(){}
        static Engine* s_Instance;

        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;

        bool m_IsPlay = false;
        bool m_IsMenu = true;
        bool m_IsPause = false;
        bool m_IsOver = false;
        bool m_IsRunning;
};

#endif // Engine_H

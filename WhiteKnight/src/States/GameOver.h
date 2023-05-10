#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Engine.h"
#include "Button.h"
#include "Play.h"

class GameOver
{
   public:
        static GameOver* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new GameOver();
        }
        bool Init();
        void Clean();
        void Render();
        void setIsWin(bool iswin) {m_IsWin = iswin;}

        inline bool IsRunning() {return m_IsRunning;}
        inline SDL_Renderer* GetRenderer() {return m_Renderer;}
    private:
        GameOver(){}
        static GameOver* s_Instance;
        bool m_IsRunning;
        bool m_IsWin;
        SDL_Renderer* m_Renderer;
        Button* m_PlayAgain;
        Button* m_Exit;

};

#endif // GAMEOVER_H

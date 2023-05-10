#ifndef MENUPAUSE_H
#define MENUPAUSE_H

#include "Engine.h"
#include "Button.h"
#include "Play.h"


class MenuPause
{
   public:
        static MenuPause* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new MenuPause();
        }
        bool Init();
        void Clean();
        void Render();

        inline bool IsRunning() {return m_IsRunning;}
        inline SDL_Renderer* GetRenderer() {return m_Renderer;}
    private:
        MenuPause(){}
        static MenuPause* s_Instance;
        bool m_IsRunning;
        SDL_Renderer* m_Renderer;
        Button* m_Resume;
        Button* m_Restart;
        Button* m_Exit;
};

#endif // MENUPAUSE_H

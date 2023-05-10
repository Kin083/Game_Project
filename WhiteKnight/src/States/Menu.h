#ifndef MENU_H
#define MENU_H

#include "Engine.h"
#include "Button.h"
#include "Play.h"

class Menu
{
    public:
        static Menu* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu();
        }
        bool Init();
        void Clean();

        void Render();

        inline bool IsRunning() {return m_IsRunning;}
        inline SDL_Renderer* GetRenderer() {return m_Renderer;}
    private:
        Menu(){}
        static Menu* s_Instance;
        bool m_IsRunning;
        SDL_Renderer* m_Renderer;
        Button* m_Starte;
        Button* m_Exit;
        Button* Pause;
};

#endif // MENU_H

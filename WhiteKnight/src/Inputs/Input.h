#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <Vector2D.h>

enum Axis {HORIZONTAL, VERTICAL};
class Input
{
    public:
        static Input* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
        }
        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        bool GetMouseButtonDown();

        int GetAxisKey(Axis axis);
        int GetAxisKey2(Axis axis);

        Vector2D GetMousePosition();

    private:
        Input();
        void KeyUp();
        void KeyDown();
        bool m_ButtonDown = false;
        const Uint8* m_KeyStates;
        static Input* s_Instance;
};

#endif // INPUT_H

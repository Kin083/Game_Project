#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <string>
#include <vector>
#include "Input.h"
#include "GameObject.h"
#include "Warrior.h"

class Button : public GameObject
{
    public:
        Button(Properties* props) : GameObject(props)
        {
            m_Shape = {props->X, props->Y, props->Width, props->Height};
            m_TextureID = props->TextureID;
            m_IsPressed = false;
        }

        virtual void Draw();
        virtual void Update(double dt);
        virtual void Clean();

        bool GetIsPressed(){return m_IsPressed;}

    private:
        SDL_Rect m_Shape;
        bool m_IsReleased = false;
        bool m_IsPressed = false;
        double m_Time = 0;
};

#endif // BUTTON_H

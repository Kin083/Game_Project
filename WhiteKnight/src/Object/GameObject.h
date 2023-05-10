#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Transform.h"
#include <SDL.h>
#include "Point.h"
#include "Collider.h"

struct Properties
{
    public:
    Properties(std::string textureID, double x, double y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        TextureID = textureID;
        X = x;
        Y = y;
        Width = width;
        Height = height;
        Flip = flip;

    }

    public:
        std::string TextureID;
        double X, Y;
        int Width, Height;
        SDL_RendererFlip Flip;
};

class GameObject
{
    public:
        GameObject(Properties* props) {
            m_TextureID = props->TextureID;
            m_Width = props->Width;
            m_Height= props->Height;
            m_Flip = props->Flip;
            m_Transform = new Transform(props->X, props->Y);
            double px = props->X + props->Width / 2;
            double py = props->Y + props->Height / 2;
            m_Origin = new Point(px, py);
        }

        inline Point* GetOrigin() {return m_Origin;}

        virtual void Draw() = 0;
        virtual void Update(double dt) = 0;
        virtual void Clean() = 0;
    protected:
        Point* m_Origin;
        Transform* m_Transform;
        int m_Width, m_Height;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;

};

#endif // GAMEOBJECT_H

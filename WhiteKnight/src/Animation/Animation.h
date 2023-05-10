#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <SDL.h>


class Animation
{
    public:
        Animation(){}

        void Update();
        void Draw(double x, double y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

        int GetCurrentFrame() {return m_CurrentFrame;}
    private:
        int m_SpriteRow, m_CurrentFrame;
        int m_Speed, m_FrameCount;
        std::string m_TextureID;
};

#endif // ANIMATION_H

#include "Animation.h"
#include "TextureManage.h"

void Animation::Update()
{
    m_CurrentFrame = (SDL_GetTicks() / m_Speed) % m_FrameCount;
}

void Animation::Draw(double x, double y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
    TextureManage::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_CurrentFrame, flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_Speed = speed;
}

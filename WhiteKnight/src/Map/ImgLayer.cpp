#include "ImgLayer.h"
#include "TextureManage.h"
ImgLayer::ImgLayer(std::string textureID, int x, int y, double scrollRatio, double scaleX, double scaleY)
{
    m_TextureID = textureID;
    m_OffsetX = x;
    m_OffsetY = y;
    m_ScrollRatio = scrollRatio;
    m_ScaleX = scaleX;
    m_ScaleY = scaleY;
    QueryImage(m_TextureID);
}


void ImgLayer::Render()
{
    TextureManage::GetInstance()->Draw(m_TextureID, m_OffsetX, m_OffsetY, m_ImgWidth, m_ImgHeight, m_ScaleX, m_ScaleY,m_ScrollRatio, m_Flip);
}

void ImgLayer::Update()
{

}

void ImgLayer::QueryImage(std::string textureID)
{
    SDL_Texture* texture = TextureManage::GetInstance()->GetTexture(m_TextureID);
    SDL_QueryTexture(texture, NULL, NULL, &m_ImgWidth, &m_ImgHeight);
}


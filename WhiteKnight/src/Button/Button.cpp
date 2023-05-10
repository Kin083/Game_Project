#include "Button.h"
#include "Vector2D.h"
#include "TextureManage.h"
#include "SoundMgr.h"
#include "Timer.h"

void Button::Update(double dt)
{
    Vector2D mPos = Input::GetInstance()->GetMousePosition();
    SDL_Point point = {mPos.X, mPos.Y};
    if (SDL_PointInRect(&point, &m_Shape))
    {
        if (!Input::GetInstance()->GetMouseButtonDown())
        {
            if (m_IsReleased == false)
                SoundMgr::GetInstance()->PlayEffect("hover");
            m_IsReleased = true;
            m_IsPressed = false;
        }
        else if (Input::GetInstance()->GetMouseButtonDown())
        {
            if (Timer::GetInstance()->Wait(200, m_Time))
            {
                m_IsReleased = false;
                m_IsPressed = true;
                SoundMgr::GetInstance()->PlayEffect("click");
            }
        }
    }
    else
    {
        m_IsPressed = false;
        m_IsReleased = false;
    }
}

void Button::Clean()
{
    TextureManage::GetInstance()->Drop(m_TextureID);
}


void Button::Draw()
{
    if (m_IsReleased)
        TextureManage::GetInstance()->Draw(m_TextureID, m_Transform->X - m_Width * 0.1, m_Transform->Y - m_Height * 0.1, m_Width, m_Height, 1.2, 1.2);
    else TextureManage::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height);

}

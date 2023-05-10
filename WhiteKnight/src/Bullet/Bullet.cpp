#include "Bullet.h"
#include "TextureManage.h"


Bullet::Bullet(Properties* props) : GameObject(props)
{
    m_TextureID = props->TextureID;
    m_Box = {props->X, props->Y, props->Width, props->Height};
}


void Bullet::Draw()
{
    TextureManage::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Bullet::Update(double dt)
{
    m_Transform->X --;
}

void Bullet::Clean()
{
    TextureManage::GetInstance()->Drop(m_TextureID);
}

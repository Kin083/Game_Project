#include "Enemy.h"
#include "TextureManage.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "Warrior.h"
#include "SoundMgr.h"

Enemy::Enemy(Properties* props) : Character(props)
{
    m_Flip = SDL_FLIP_HORIZONTAL;
    m_AttackTime = B_ATTACK_TIME;
    m_HurtTime = B_HURT_TIME;

    m_IsRunning = false;
    m_IsAttacking = false;
    m_IsDied = false;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-90, -100, 180, 120);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(5.5f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 3, 120);
    m_w = 256, m_h = 256;
    m_HP = 270;
    m_Center = m_Transform->X;

}

void Enemy::Update(double dt)
{
    int speed = 1;
    m_IsRunning = false;
    m_Flip = SDL_FLIP_NONE;

    m_RigidBody->UnSetForce();
    if (m_IsGrounded && m_IsRunning)
    {
        m_RigidBody->ApplyForceX(m_SpeedWalk);
    }

    if (m_IsAttacking && m_AttackTime > 0)
        m_AttackTime -= dt;
    else
    {
        m_IsAttacking = false;
        m_AttackTime = B_ATTACK_TIME;
    }
    if (m_IsAttacking) speed = 0;

    if (m_IsHurt && m_HurtTime > 0)
        m_HurtTime -= dt;
    else
    {
        m_IsHurt = false;
        m_HurtTime = B_HURT_TIME;
    }
    if (m_IsHurt)
        m_IsAttacking = false;
    if (m_IsHurt && !m_IsDied)
    {
        if (m_AnimaState == 0) {
            if (m_Flip == SDL_FLIP_NONE) m_RigidBody->ApplyForceX(0.5);
            else m_RigidBody->ApplyForceX(0.5);
        }
        else m_RigidBody->ApplyForceX(-m_SpeedWalk * 4 / 5);
    }

    m_Origin->X = m_Transform->X + m_Width / 2;
    int tmp = m_Origin->X / SCREEN_WIDTH / 2;
    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X + m_SpeedWalk * speed;
    m_Collider->Set(m_Transform->X, m_Transform->Y, m_w, m_h);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    if (m_AnimaState == 1 && !m_IsDied)
    {
        if (m_Transform->X - m_Center < -RANGE)
        {
            m_SpeedWalk = -m_SpeedWalk;
            m_Transform->X = m_Center - RANGE + 100;
        }
        if (m_Transform->X - m_Center > RANGE)
        {
            m_SpeedWalk = -m_SpeedWalk;
            m_Transform->X = m_Center + RANGE - 100;
        }
        if (m_SpeedWalk > 0) m_Flip = SDL_FLIP_HORIZONTAL;
            else m_Flip = SDL_FLIP_NONE;

        if (m_SpeedWalk != 0) m_IsRunning = true;
    }
    if (m_IsAttacking) m_IsRunning = false;

    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, m_w, m_h);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else
    {
        m_IsGrounded = false;
    }

    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;

    if (m_AnimaState == 0) AnimationState();
    else if (m_AnimaState == 1) AnimationState_1();
    m_Animation->Update();
}

void Enemy::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    TextureManage::GetInstance()->Draw("HP_0", m_Origin->X - 39 - cam.X - 25 * m_SpeedWalk * m_AnimaState, m_Origin->Y - 43, 270, 19, 0.3, 0.4);
    if (m_AnimaState == 1) TextureManage::GetInstance()->Draw("HP_1", m_Origin->X - 39 - cam.X - 25 * m_SpeedWalk * m_AnimaState, m_Origin->Y - 43, m_HP / 2, 19, 0.3, 0.4);
    else TextureManage::GetInstance()->Draw("HP_1", m_Origin->X - 39 - cam.X, m_Origin->Y - 43, m_HP, 19, 0.3, 0.4);
    TextureManage::GetInstance()->Draw("HP_2", m_Origin->X - 40 - cam.X - 25 * m_SpeedWalk * m_AnimaState, m_Origin->Y - 46, 280, 31, 0.3, 0.42);
    //SDL_RenderDrawRect(Play::GetInstance()->GetRenderer(), &box);
}

void Enemy::AnimationState()
{
    // idling
    m_Animation->SetProps("cnv_plant", 1, 3, 130);

    // running
    if (m_IsRunning)
        m_Animation->SetProps("cnv_plant", 1, 3, 200);

    // attacking
    if (m_IsAttacking)
        m_Animation->SetProps("cnv_plant_attack", 1, 3, 200);
    if (m_IsDied)
        m_Animation->SetProps("cnv_plant_died", 1, 3, 200);

}

void Enemy::AnimationState_1()
{
    // idling
    m_Animation->SetProps("bod_idle", 1, 8, 150);

    // running
    if (m_IsRunning)
        m_Animation->SetProps("bod_walk", 1, 8, 120);

    // attacking
    if (m_IsAttacking)
        m_Animation->SetProps("bod_attack", 1, 9, 90);

    if (m_IsHurt)
        m_Animation->SetProps("bod_hurt", 1, 3, 120);
    if (m_IsDied)
        m_Animation->SetProps("bod_died", 1, 11, 120);

}

Collider* Enemy::GetColliderAttacking()
{
    Collider* ColliderAttacking = new Collider();
    int right = 1, left = 0;
    if (!m_Flip)
    {
        left = 1;
        right = 0;
    }
    ColliderAttacking->Set(m_Collider->Get().x - 100 * left, m_Collider->Get().y, m_Collider->Get().w + 120 ,m_Collider->Get().h);
    return ColliderAttacking;
}

void Enemy::SetDied()
{
    if(m_IsDied == false)
    {
        if (m_AnimaState == 0) SoundMgr::GetInstance()->PlayEffect("plant_died");
        else SoundMgr::GetInstance()->PlayEffect("B_Died");
    }
    m_IsDied = true;
}

void Enemy::Clean()
{
    delete m_Collider;
    delete m_Animation;
    delete m_RigidBody;
    TextureManage::GetInstance()->Drop(m_TextureID);
}


#include "Warrior.h"
#include "TextureManage.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "SoundMgr.h"

Warrior::Warrior(Properties* props) : Character(props)
{
    m_IsRunning = false;
    m_IsAttacking = false;
    m_IsDefend = false;
    m_IsFalling = false;
    m_IsJumping = false;
    m_IsGrounded = false;

    m_Flip = SDL_FLIP_NONE;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_HP = 270;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-95, -115, 190, 136);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(5.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 4, 120);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    //SDL_RenderDrawRect(Play::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(double dt)
{
    m_IsRunning = false;

    m_RigidBody->UnSetForce();

    // Run forward
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }
    // Run backward
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }
    // Attack
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J))
    {
        m_RigidBody->UnSetForce();
        if (m_IsAttacking == false) SoundMgr::GetInstance()->PlayEffect("attack");
        m_IsAttacking = true;
    }
    // Jump
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        SoundMgr::GetInstance()->PlayEffect("jump");
    }
    if (m_IsJumping == true && m_IsGrounded == false && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        if (m_JumpTime > 0)
        {
            m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
        }
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // Fall
    if (m_RigidBody->Velocity().Y > 1 && !m_IsGrounded)
        m_IsFalling = true;
    else
        m_IsFalling = false;

    // Defend

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_U) && m_IsGrounded)
    {
        m_RigidBody->UnSetForce();
        m_IsDefend = true;
        m_IsAttacking = false;
    }
    else
    {
        m_IsDefend = false;
    }


    // Attack time
    if (m_IsAttacking && m_AttackTime > 0)
        m_AttackTime -= dt;
    else
    {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    if (m_IsHurt && m_HurtTime > 0)
        m_HurtTime -= dt;
    else
    {
        m_IsHurt = false;
        m_HurtTime = HURT_TIME;
    }

    if (m_IsHurt)
        m_IsAttacking = false;
    if (m_IsHurt)
    {
        if (m_Flip == SDL_FLIP_NONE) m_RigidBody->ApplyForceX(-0.2);
        else m_RigidBody->ApplyForceX(0.2);
    }

    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;

    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 240, 240);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }
    if (CollisionHandler::GetInstance()->ScreenCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 240, 240);

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

    AnimationState();
    m_Animation->Update();

}

void Warrior::AnimationState()
{
    // idling
    m_Animation->SetProps("player_idle", 1, 4, 120);

    // running
    if (m_IsRunning)
        m_Animation->SetProps("player_run", 1, 7, 85);

    // jumping
    if (m_IsJumping)
        m_Animation->SetProps("player_jump", 1, 1, 500);

    // falling
    if (m_IsFalling)
        m_Animation->SetProps("player_fall", 1, 1, 500);

    // attacking
    if (m_IsAttacking)
        m_Animation->SetProps("player_attack", 1, 4, 100);
    if (m_IsDefend)
        m_Animation->SetProps("player_defend", 1, 5, 100);
    if (m_IsHurt)
        m_Animation->SetProps("player_hurt", 1, 1, 80);
}

Collider* Warrior::GetColliderAttacking()
{
    Collider* ColliderAttacking = new Collider();
    int right = 1, left = 0;
    if (m_Flip)
    {
        left = 1;
        right = 0;
    }
    ColliderAttacking->Set(m_Collider->Get().x - 200 * left, m_Collider->Get().y, m_Collider->Get().w + 100 * right + 100 * left,m_Collider->Get().h);
    return ColliderAttacking;
}

void Warrior::Clean()
{
    delete m_Collider;
    delete m_Animation;
    delete m_RigidBody;
    TextureManage::GetInstance()->Drop(m_TextureID);
}





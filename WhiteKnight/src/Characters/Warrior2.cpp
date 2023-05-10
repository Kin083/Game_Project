#include "Warrior2.h"
#include "TextureManage.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Camera.h"

Warrior2::Warrior2(Properties* props) : Character(props)
{
    m_IsRunning = false;
    m_IsAttacking = false;
    m_IsFalling = false;
    m_IsJumping = false;
    m_IsGrounded = false;

    m_Flip = SDL_FLIP_NONE;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-67, -76, 135, 82);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(5.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 4, 120);
}

void Warrior2::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    //SDL_RenderDrawRect(Play::GetInstance()->GetRenderer(), &box);
}

void Warrior2::Update(double dt)
{
    m_IsRunning = false;

    m_RigidBody->UnSetForce();

    // Run forward
    if (Input::GetInstance()->GetAxisKey2(HORIZONTAL) == FORWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }
    // Run backward
    if (Input::GetInstance()->GetAxisKey2(HORIZONTAL) == BACKWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }
    // Attack
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_KP_1))
    {
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
    }
    // Jump
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
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

    // Attack time
    if (m_IsAttacking && m_AttackTime > 0)
        m_AttackTime -= dt;
    else
    {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    int tmp = Camera::GetInstance()->GetPosition().X / SCREEN_WIDTH / 2;
    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 160, 160);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get(), tmp) )
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 160, 160);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get(), tmp))
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

void Warrior2::AnimationState()
{
    // idling
    m_Animation->SetProps("player2_idle", 1, 4, 120);

    // running
    if (m_IsRunning)
        m_Animation->SetProps("player2_run", 1, 7, 100);

    // jumping
    if (m_IsJumping)
        m_Animation->SetProps("player2_jump", 1, 1, 500);

    // falling
    if (m_IsFalling)
        m_Animation->SetProps("player2_fall", 1, 1, 500);

    // attacking
    if (m_IsAttacking)
        m_Animation->SetProps("player2_attack", 1, 5, 90);
}

Collider* Warrior2::GetColliderAttacking()
{
    Collider* ColliderAttacking = new Collider();
    int right = 1, left = 0;
    if (m_Flip)
    {
        left = 1;
        right = 0;
    }
    ColliderAttacking->Set(m_Collider->Get().x - 64 * left, m_Collider->Get().y, m_Collider->Get().w + 64 * right,m_Collider->Get().h);
    return ColliderAttacking;
}

void Warrior2::Clean()
{
    delete m_Collider;
    delete m_Animation;
    delete m_RigidBody;
    TextureManage::GetInstance()->Drop(m_TextureID);
}





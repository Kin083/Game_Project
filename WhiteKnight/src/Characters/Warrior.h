#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_TIME 19.0f
#define JUMP_FORCE 11.0f

#define RUN_FORCE 5.0f
#define ATTACK_TIME 20.0f
#define HURT_TIME 20.0f

class Warrior : public Character
{
    public:
        Warrior(Properties* props);

        virtual void Draw();
        virtual void Update(double dt);
        virtual void Clean();
        bool GetIsAttacking() {return m_IsAttacking;}
        bool GetIsDefend() {return m_IsDefend;}
        void SetIsHurt(bool ishurt) {m_IsHurt = ishurt;}
        Collider* GetCollider() {return m_Collider;}
        Collider* GetColliderAttacking();
        int GetCurrentFrame() {return m_Animation->GetCurrentFrame();}
        double Time_Attack = 0;

    private:
        void AnimationState();

    private:
        bool m_IsJumping;
        bool m_IsGrounded;
        bool m_IsRunning;
        bool m_IsFalling;
        bool m_IsAttacking;
        bool m_IsDefend;
        bool m_IsHurt;

        double m_JumpTime;
        double m_JumpForce;
        double m_AttackTime;
        double m_HurtTime;

        Collider* m_Collider;

        Animation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;

};

#endif // WARRIOR_H

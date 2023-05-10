#ifndef Warrior2_H
#define Warrior2_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_TIME 19.0f
#define JUMP_FORCE 11.0f

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f
#define WALK_TIME 10.0f

class Warrior2 : public Character
{
    public:
        Warrior2(Properties* props);

        virtual void Draw();
        virtual void Update(double dt);
        virtual void Clean();
        bool GetIsAttacking() {return m_IsAttacking;}
        Collider* GetCollider() {return m_Collider;}
        Collider* GetColliderAttacking();
    private:
        void AnimationState();

    private:
        bool m_IsJumping;
        bool m_IsGrounded;
        bool m_IsRunning;
        bool m_IsFalling;
        bool m_IsAttacking;

        double m_JumpTime;
        double m_JumpForce;
        double m_AttackTime;

        Collider* m_Collider;

        Animation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;

};

#endif // Warrior2_H

#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "vector"

#define B_ATTACK_TIME 20.0f
#define B_HURT_TIME 80.0f
#define RANGE 200.0f

class Enemy : public Character
{
   public:
        Enemy(Properties* props);

        virtual void Draw();
        virtual void Update(double dt);
        virtual void Clean();
        bool GetIsAttacking() {return m_IsAttacking;}
        bool GetIsHurt() {return m_IsHurt;}
        bool GetIsDied() {return m_IsDied;}
        Collider* GetCollider() {return m_Collider;}
        Collider* GetColliderAttacking();

        void SetCollider(int w, int h) {m_w = w; m_h = h;}
        void SetBuffer(int x, int y, int w, int h) {m_Collider->SetBuffer(x, y, w, h);}

        void SetAttack(bool attack) {m_IsAttacking = attack;}
        void SetHurt(bool hurt) {m_IsHurt = hurt;}
        void SetDied();
        double m_DiedTime = 0;
        double Time_Attack = 0;
        void SetAnimaState(int number) {m_AnimaState = number;}
        int GetAnimaState() {return m_AnimaState;}
        void SetSpeedWalk(int speed) {m_SpeedWalk = speed;}
        int GetCurrentFrame() {return m_Animation->GetCurrentFrame();}

    private:
        void AnimationState();
        void AnimationState_1();

    private:
        bool m_IsGrounded;
        bool m_IsRunning;
        bool m_IsAttacking;
        bool m_IsHurt;
        bool m_IsDied;
        int m_w = 0, m_h = 0;
        double m_Center = m_Transform->X;
        double m_AttackTime;
        double m_HurtTime;
        int m_SpeedWalk = 0;

        Collider* m_Collider;

        Animation* m_Animation;
        RigidBody* m_RigidBody;
        int m_AnimaState = 0;

        Vector2D m_LastSafePosition;


};

#endif // ENEMY_H

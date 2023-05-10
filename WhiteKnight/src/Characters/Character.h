#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include <string>


class Character : public GameObject
{
    public:
        Character(Properties* props) : GameObject(props) {}

        virtual void Draw() = 0;
        virtual void Update(double dt) = 0;
        virtual void Clean() = 0;
        virtual Collider* GetCollider() = 0;
        virtual void SetHP(int hp) {m_HP = hp;}
        virtual void MinusHP(int Minus) {m_HP -= Minus;}
        virtual int GetHP() {return m_HP;}
    protected:
        std::string m_Name;
        int m_HP;

};

#endif // CHARACTER_H

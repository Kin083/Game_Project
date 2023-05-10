#ifndef IOBJECT_H
#define IOBJECT_H
#include "Collider.h"

class IObject
{
    public:
        virtual void Draw() = 0;
        virtual void Update(double dt) = 0;
        virtual void Clean() = 0;
        //virtual Collider* GetCollider() = 0;
};

#endif // IOBJECT_H

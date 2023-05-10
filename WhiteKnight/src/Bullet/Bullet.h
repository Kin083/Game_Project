#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include <vector>
#include <GameObject.h>

class Bullet : public GameObject
{
    public:
        Bullet(Properties* props);
        virtual void Draw();
        virtual void Update(double dt);
        virtual void Clean();

        SDL_Rect GetRect() {return m_Box;}
    private:
        SDL_Rect m_Box;

};
#endif // BULLET_H

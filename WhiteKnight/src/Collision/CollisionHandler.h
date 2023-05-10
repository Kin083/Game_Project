#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <SDL.h>
#include "Vector2D.h"
#include "TileLayer.h"
#include "GameMap.h"
#include "Engine.h"
#include <vector>

class CollisionHandler
{
    public:
        inline static CollisionHandler* GetInstance() {return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler();}

        bool MapCollision(SDL_Rect a);
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
        bool ScreenCollision(SDL_Rect a);

    private:
        CollisionHandler();
        static CollisionHandler* s_Instance;
};

#endif // COLLISIONHANDLER_H

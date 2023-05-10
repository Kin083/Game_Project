#include "CollisionHandler.h"
#include "Play.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{

}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    bool y_overlaps = (a.y + a.h >= SCREEN_HEIGHT - 194);
    return y_overlaps;
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::ScreenCollision(SDL_Rect a)
{
    bool x_overlaps = (a.x <= 0) || (a.x + a.w >= 3 * 2 * SCREEN_WIDTH);
    bool y_overlaps = (a.y <= 0) || (a.y + a.h >= SCREEN_HEIGHT);
    return (x_overlaps || y_overlaps);
}



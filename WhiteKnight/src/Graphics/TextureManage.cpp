#include "TextureManage.h"
#include "Camera.h"

TextureManage* TextureManage::s_Instance = nullptr;

bool TextureManage::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Failed to load texture: %s, %s\n", filename.c_str(), SDL_GetError());
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s\n", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

void TextureManage::Draw(std::string id, int x, int y, int width, int height, double scaleX, double scaleY, double scrollRatio, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};

    Vector2D cam = Camera::GetInstance()->GetPosition() * scrollRatio;
    SDL_Rect dstRect = {x - cam.X, y - cam.Y, width * scaleX, height * scaleY};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManage::DrawBG(std::string id, int x, int y, int width, int height, double scaleX, double scaleY, double scrollRatio, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition() * scrollRatio;

    int tmp = x - cam.X;
    if (tmp < 0) tmp = -tmp;
    tmp = tmp / width;
    SDL_Rect dstRect1 = {x - cam.X + width * tmp, y - cam.Y, width * scaleX, height * scaleY};
    SDL_Rect dstRect2 = {x - cam.X + width * (tmp + 1), y - cam.Y, width * scaleX, height * scaleY};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect1, 0, nullptr, flip);
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect2, 0, nullptr, flip);
}

void TextureManage::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {x - cam.X, y - cam.Y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, flip);
}
void TextureManage::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width * frame, height * (row - 1), width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {x - cam.X, y - cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManage::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManage::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();

    SDL_Log("texture map cleaned\n");
}

void TextureManage::DrawBG2(std::string id, int &x, int y, int width, int height, double scaleX, double scaleY, double scrollRatio, int velocity, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    x -= velocity;
    Vector2D cam = Camera::GetInstance()->GetPosition() * scrollRatio;

    int tmp = x - cam.X;
    if (tmp < 0) tmp = -tmp;
    tmp = tmp / width;
    SDL_Rect dstRect1 = {x - cam.X + width * tmp, y - cam.Y, width * scaleX, height * scaleY};
    SDL_Rect dstRect2 = {x - cam.X + width * (tmp + 1), y - cam.Y, width * scaleX, height * scaleY};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect1, 0, nullptr, flip);
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect2, 0, nullptr, flip);
}



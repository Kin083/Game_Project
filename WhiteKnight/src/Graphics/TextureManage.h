#ifndef TEXTUREMANAGE_H
#define TEXTUREMANAGE_H

#include <string>
#include <SDL.h>
#include <map>
#include "Play.h"


class TextureManage
{
    public:
        static TextureManage* GetInstance() {return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManage();}
        bool Load(std::string id, std::string filename);
        void Drop(std::string id);
        void Clean();

        void Draw(std::string id, int x, int y, int width, int height, double scaleX = 1, double scaleY = 1, double scrollRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawBG(std::string id, int x, int y, int width, int height, double scaleX = 1, double scaleY = 1, double scrollRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawBG2(std::string id, int &x, int y, int width, int height, double scaleX = 1, double scaleY = 1, double scrollRatio = 0, int velocity = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

        SDL_Texture* GetTexture(std::string id) {return m_TextureMap[id];}
    private:
        TextureManage(){}
        std::map<std::string, SDL_Texture*> m_TextureMap;
        static TextureManage* s_Instance;

};

#endif // TEXTUREMANAGE_H

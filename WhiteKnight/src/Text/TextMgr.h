#ifndef TEXTMGR_H
#define TEXTMGR_H

#include <string>
#include <iostream>
#include <SDL_ttf.h>

class TextMgr
{
    public:
        void RenderText(std::string text, int x, int y);
        inline static TextMgr* GetInstance(){return s_Instance = (s_Instance != NULL) ? s_Instance : new TextMgr;}
    private:
        TextMgr();
        static TextMgr* s_Instance;
        TTF_Font* m_Font = nullptr;
        SDL_Texture* m_Texture;
        SDL_Renderer* m_Renderer;
};

#endif // TEXTMGR_H

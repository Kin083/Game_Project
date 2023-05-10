#ifndef IMGLAYER_H
#define IMGLAYER_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Layer.h"

class ImgLayer : public Layer
{
    public:
        ImgLayer(std::string textureID, int x, int y, double scrollRatio = 1.0f, double scaleX = 1.0f, double scaleY = 1.0f);
        void SetScrollRatio(double scrollRatio) {m_ScrollRatio = scrollRatio;}
        void SetOffset(int x, int y) {m_OffsetX = x; m_OffsetY = y;}
        void SetRepeated(bool repeated) {m_Repeated = repeated;}
        void QueryImage(std::string textureID);

        virtual void Render();
        virtual void Update();

    private:
        bool m_Repeated;
        double m_ScrollRatio;
        std::string m_TextureID;
        double m_ScaleX, m_ScaleY;
        int m_OffsetX, m_OffsetY;
        int m_ImgWidth, m_ImgHeight;
        SDL_RendererFlip m_Flip;
};

#endif // IMGLAYER_H

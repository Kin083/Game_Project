#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

class GameMap
{
    public:
        void Render(int number)
        {
            for (unsigned int i = 0; i < m_MapLayers.size(); i++)
                m_MapLayers[i]->Render(number);
        }
        void Update()
        {
            for (unsigned int i = 0; i < m_MapLayers.size(); i++)
                m_MapLayers[i]->Update();
        }
        void Clean()
        {
            m_MapLayers.clear();
        }

        std::vector<Layer*> GetLayers() {return m_MapLayers;}

    private:
        friend class MapParser;
        std::vector<Layer*> m_MapLayers;

};

#endif // GAMEMAP_H

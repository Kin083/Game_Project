#include "TileLayer.h"
#include "TextureManage.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets):
m_TileSize(tilesize), m_ColCount(colcount), m_RowCount(rowcount), m_Tilemap(tilemap), m_Tilesets(tilesets)
{

    for(unsigned int i = 0; i < m_Tilesets.size(); i++)
    {
        TextureManage::GetInstance()->Load(m_Tilesets[i].Name, "assets/Maps/" + m_Tilesets[i].Source);
    }

}

void TileLayer::Render(int number)
{
    for(unsigned int i = 0; i < m_RowCount; i++)
        for(unsigned int j = 0; j < m_ColCount; j++)
        {
            int tileID = m_Tilemap[i][j];

            if (tileID == 0)
                continue;

            int index = 0;
            if (m_Tilesets.size() > 1)
            {
                for(unsigned int k = 1; k < m_Tilesets.size(); k++)
                {
                    if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID)
                    {
                        tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                        index = k;
                        break;
                    }
                }
            }
            Tileset ts = m_Tilesets[index];
            int tileRow = tileID / ts.ColCount;
            int tileCol = tileID - ts.ColCount * tileRow - 1;

            // if this tile is on the last column
            if (tileID % ts.ColCount == 0)
            {
                tileRow--;
                tileCol = ts.ColCount - 1;
            }

            TextureManage::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize + ts.TileSize * m_ColCount * number, i * ts.TileSize, tileRow, tileCol);
        }
}

void TileLayer::Update()
{

}

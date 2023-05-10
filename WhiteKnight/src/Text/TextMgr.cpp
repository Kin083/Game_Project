#include "TextMgr.h"
#include "Engine.h"

TextMgr* TextMgr::s_Instance = nullptr;

TextMgr::TextMgr()
{
    if( TTF_Init() == -1 )
    {
        std::cerr << TTF_GetError() << std::endl;
    }
    m_Font = TTF_OpenFont( "assets/Font/AM____11.TTF", 30 );
	if( m_Font == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
}

void TextMgr::RenderText(std::string textureText, int x, int y)
{
    m_Renderer = Engine::GetInstance()->GetRenderer();
    SDL_Color textColor = {0,0,0};
    SDL_Surface* textSurface = TTF_RenderText_Solid( m_Font, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        std::cerr << TTF_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixels
        m_Texture = SDL_CreateTextureFromSurface( m_Renderer, textSurface );
        if( m_Texture == NULL )
        {
            std::cerr << SDL_GetError() << std::endl;
        }
    }
    SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h};
	//Render to screen
	SDL_RenderCopyEx( m_Renderer, m_Texture, NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE );

}

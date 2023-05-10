#ifndef SOUNDMGR_H
#define SOUNDMGR_H

#include <map>
#include <string>
#include <iostream>
#include <SDL_mixer.h>

#define FREQ 44100
#define CHUNK_SIZE 2048

using EffectMap = std::map<std::string, Mix_Chunk*>;
using MusicMap = std::map<std::string, Mix_Music*>;

class SoundMgr
{
    public:
        void Clean();

        void PlayMusic(std::string id);
        void LoadMusic(std::string id, std::string source);

        void PlayEffect(std::string id);
        void LoadEffect(std::string id, std::string source);
        Mix_Music* GetMusic(std::string id) {return m_MusicMap[id];}

        void SetOnSounds() {if (m_OnSounds == true) m_OnSounds = false; else m_OnSounds = true;}
        bool GetOnSound() {return m_OnSounds;}
        inline static SoundMgr* GetInstance(){return s_Instance = (s_Instance != NULL) ? s_Instance : new SoundMgr();}

    private:
        SoundMgr();
        MusicMap m_MusicMap;
        EffectMap m_EffectMap;
        static SoundMgr* s_Instance;
        bool m_OnSounds = true;
};

#endif // SOUNDMGR_H

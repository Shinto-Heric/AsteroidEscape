#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>

namespace asteroidescape
{
    class SoundManager
    {
    public:
        static SoundManager* GetInstance();

        void LoadSound(const std::string& name, const std::string& filename);
        void PlaySound(const std::string& name);
        void LoadMusic(const std::string& filename);
        void PlayMusic(bool loop = false);
        void StopMusic();

    protected:
        static SoundManager* instance;

    private:

        std::map<std::string, sf::SoundBuffer> _soundBuffers; // To store sound buffers
        std::map<std::string, sf::Sound> _sounds;             // To manage sound playback
        sf::Music _backgroundMusic;                           // Background music object

        SoundManager();     // Private constructor for singleton
        //------------------------- Delete copy constructor and assignment operator to prevent copying-------------------------------//   
        SoundManager(const SoundManager&) = delete;
        SoundManager& operator=(const SoundManager&) = delete;
        //---------------------------------------------------------------------------------------------------------------------------//

        void InitialiseGameSounds();
    };
}




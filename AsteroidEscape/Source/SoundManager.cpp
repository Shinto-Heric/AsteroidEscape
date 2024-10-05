#include "SoundManager.h"
#include <iostream>

namespace asteroidescape
{
    SoundManager* SoundManager::instance = NULL; // Static variable initialisation

    SoundManager::SoundManager()
    {
        InitialiseGameSounds();
    }

    void SoundManager::InitialiseGameSounds()
    {
        LoadSound("shoot", "shoot.mp3");
        LoadSound("explosion", "explosion.mp3");
        LoadSound("gameover", "game_over.mp3");
        LoadMusic("background_music.mp3");
        PlayMusic(true);
    }

    // Static method to get the singleton instance
    SoundManager* SoundManager::GetInstance()
    {
        if (instance == NULL)
            instance = new SoundManager();
        return instance;
    }

    // Load a sound file into the sound buffer
    void SoundManager::LoadSound(const std::string& name, const std::string& filename)
    {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("../Assets/Sounds/" + filename))
        {
            std::cerr << "Error loading sound: " << filename << std::endl;
            return;
        }
        _soundBuffers[name] = buffer;
        _sounds[name].setBuffer(_soundBuffers[name]);
    }

    // Play a loaded sound
    void SoundManager::PlaySound(const std::string& name)
    {
        if (_sounds.find(name) != _sounds.end())
        {
            _sounds[name].play();
        }
    }

    // Load background music file
    void SoundManager::LoadMusic(const std::string& filename)
    {
        if (!_backgroundMusic.openFromFile("../Assets/Sounds/" + filename))
        {
            std::cerr << "Error loading music: " << filename << std::endl;
        }
    }

    // Play the background music, with an option to loop it
    void SoundManager::PlayMusic(bool loop)
    {
        _backgroundMusic.setLoop(loop);
        _backgroundMusic.play();
    }

    // Stop the background music
    void SoundManager::StopMusic()
    {
        _backgroundMusic.stop();
    }

}
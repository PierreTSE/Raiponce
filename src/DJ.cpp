#include"DJ.hpp"
#include <filesystem>
#include "RessourceLoader.hpp"
#include "Utilities.hpp"
#include <iostream>

DJ::DJ()
{
    std::filesystem::path dirPath = RessourceLoader::getPath("audio");

    if(!std::filesystem::is_directory(dirPath))
        throw std::runtime_error("Not a directory" + dirPath.u8string());

    for(auto& file : std::filesystem::directory_iterator(dirPath))
    {
        if(file.path().extension() == ".wav")
        {
            /*
            if(!soundBuffers_.back().loadFromFile(file.path().string()))
                std::cerr << file.path().u8string() << std::endl;
            */

            sounds_[file.path().filename().string()] = sf::Sound(RessourceLoader::getSoundBuffer(strip_root(dirPath / file.path().filename()).u8string()));
        }
        else if(file.path().extension() == ".ogg")
        {
            musics_[file.path().filename().string()] = std::make_unique<sf::Music>();
            musics_[file.path().filename().string()]->openFromFile(file.path().string());
            musics_[file.path().filename().string()]->setLoop(true);
        }
    }
}

DJ& DJ::getInstance() { 
    static DJ instance;
    return instance; }

void DJ::playSound(const std::string& name, bool forced)
{
    if(sounds_.find(name) != sounds_.end() && sounds_[name].getStatus() != sf::Sound::Status::Playing || forced)
        sounds_[name].play();    
}
                    
void DJ::playMusic(const std::string& name)
{
    if(musics_[name]->getStatus() != sf::Music::Status::Playing)
        musics_[name]->play();
}
                    
void DJ::stopMusic(const std::string& name) { musics_[name]->stop(); }

void DJ::stopAllMusic()
{
    for(auto& [k, v] : musics_)
        v->stop();
}

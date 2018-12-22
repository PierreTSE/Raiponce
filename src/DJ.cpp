#include"DJ.hpp"
#include <filesystem>
#include "RessourceLoader.hpp"
#include "Utilities.hpp"
#include <iostream>

DJ::DJ()
{
    sounds_["cri"] = sf::Sound(RessourceLoader::getSoundBuffer("audio/surprise/cri.wav"));
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

bool DJ::isSoundPlaying(const std::string & name)
{
	if (sounds_.find(name) != sounds_.end())
		return sounds_[name].getStatus() == sf::Sound::Status::Playing;
	else
		return false;
}

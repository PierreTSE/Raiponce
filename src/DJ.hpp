#ifndef DJ_HPP
#define DJ_HPP

#include <filesystem>
#include <map>
#include <SFML/Audio.hpp>
#include <string>

class DJ
{
public :
    DJ();

    static DJ& getInstance();

    void playSound(const std::string& name, bool forced = false);
    void playMusic(const std::string& name);
    void stopMusic(const std::string& name);
    void stopAllMusic();

private :
    std::map<std::string, sf::Sound>                  sounds_;
    std::map<std::string, std::unique_ptr<sf::Music>> musics_;
};

#endif //DJ_HPP

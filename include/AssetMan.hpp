#pragma once

#include <string>
#include <map>

#include <SFML/Audio.hpp>

#include "SFML/Graphics.hpp"

namespace Engine
{
    class AssetMan
    {
    public:
        AssetMan();
        ~AssetMan();

        void AddTexture(int id, std::string path);
        void AddFont(int id, std::string path);
        void AddSound(int id, std::string path);

        sf::Font &GetFont(int id);
        sf::Texture &GetTexture(int id);
        sf::SoundBuffer &GetSound(int id);

        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;
        std::map<int, std::unique_ptr<sf::SoundBuffer>> m_sounds;
    };

}
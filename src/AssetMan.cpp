#include <iostream>

#include <SFML/Audio.hpp>

#include "AssetMan.hpp"

Engine::AssetMan::AssetMan()
{
}

Engine::AssetMan::~AssetMan()
{
}

void Engine::AssetMan::AddTexture(int id, std::string path)
{
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(path))
    {
        m_textures.insert({id, std::move(texture)});
    }
    else
    {
        std::cout << "something goes wrong!\n";
    }
}

void Engine::AssetMan::AddSound(int id, std::string path)
{
    std::unique_ptr<sf::SoundBuffer> soundBuffer = std::make_unique<sf::SoundBuffer>();

    if (soundBuffer->loadFromFile(path))
    {
        m_sounds.insert({id, std::move(soundBuffer)});
    }
    else
    {
        std::cout << "something goes wrong!\n";
    }
}

void Engine::AssetMan::AddFont(int id, std::string path)
{
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    if (font->loadFromFile(path))
    {
        m_fonts.insert({id, std::move(font)});
    }
    else
    {
        std::cout << "something goes wrong!\n";
    }
}

sf::Font &Engine::AssetMan::GetFont(int id)
{
    return *(m_fonts.at(id).get());
}

sf::Texture &Engine::AssetMan::GetTexture(int id)
{
    return *(m_textures.at(id).get());
}

sf::SoundBuffer &Engine::AssetMan::GetSound(int id)
{
    return *(m_sounds.at(id).get());
}
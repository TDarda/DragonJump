#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "AssetMan.hpp"
#include "StateMan.hpp"
#include <SFML/Audio.hpp>

enum Assets_id
{
    BACKGROUND,
    MAIN_FONT,
    GAME_BACKGROUND,
    WALLPAPER,
    DEAD1,
    DEAD2,
    DEAD3,
    DEAD4,
    DEAD5,
    DEAD6,
    DEAD7,
    DEAD8,
    POOP,
    MENU_POINTER,
    SWITCH_SOUND,
    START_SOUND,
    END_GAME_SOUND,
    JUMP_SOUND

};

struct Aspect
{
    std::unique_ptr<Engine::StateMan> m_states;
    std::unique_ptr<Engine::AssetMan> m_assets;
    std::unique_ptr<sf::RenderWindow> m_window;

    Aspect()
    {
        m_states = std::make_unique<Engine::StateMan>();
        m_assets = std::make_unique<Engine::AssetMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
private:
    const sf::Time m_FPS = sf::seconds(1.f / 800.f);

public:
    Game();
    ~Game();

    std::shared_ptr<Aspect> m_aspect;

    void Run();
};
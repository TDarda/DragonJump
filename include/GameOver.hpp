#pragma once
#include "State.hpp"
#include <memory>
#include "Game.hpp"
#include "GamePlay.hpp"
#include <SFML/Audio.hpp>

class GameOver : public Engine::State
{
private:
    std::shared_ptr<Aspect> m_aspect;

    int m_deadCount = DEAD1;

    bool m_restartSelected;
    bool m_exitSelected;
    bool m_startAgame;

    sf::Text m_restart;
    sf::Text m_exit;
    sf::Text m_header;

    sf::Sprite m_background;
    sf::Sprite m_dragonDie;
    sf::Sprite m_menuPointer;

    sf::Sound m_switchSound;
    sf::Sound m_goSound;

    sf::Clock m_dragonClock;

public:
    GameOver(std::shared_ptr<Aspect> &aspect);
    ~GameOver();

    void DragonDie(sf::Time fps);

    void Init() override;
    void InputProcess() override;
    void Update() override;
    void Draw() override;
};
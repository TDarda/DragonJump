#pragma once

#include <memory>

#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "GamePlay.hpp"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Aspect> m_aspect;

    bool m_startSelected;
    bool m_exitSelected;
    bool m_startAgame;

    sf::Text m_start;
    sf::Text m_exit;
    sf::Text m_header;

    sf::Sprite m_background;
    sf::Sprite m_menuPointer;

    sf::Sound m_switchSound;
    sf::Sound m_goSound;

public:
    MainMenu(std::shared_ptr<Aspect> &aspect);
    ~MainMenu();

    void Init() override;
    void InputProcess() override;
    void Update() override;
    void Draw() override;
};
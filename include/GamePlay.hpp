#pragma once
#include <memory>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Dragon.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Aspect> m_aspect;

    float m_backGroundCount = 0.0;
    float m_extraBackGroundCount = 1895.0;
    float m_poopCount = 640.0;
    int m_scoreCount = 0;

    bool m_isJumping;
    bool m_isGameOver = false;
    bool m_isPause = false;

    sf::Text m_pause;
    sf::Text m_score;

    sf::Clock m_backGroundClock;
    sf::Clock m_scoreClock;

    sf::Sprite m_extraBackground;
    sf::Sprite m_background;
    sf::Sprite m_poop;
    sf::Sprite m_wallpaper;

    sf::Sound m_endSound;
    sf::Sound m_jumpSound;
    sf::Music music;

    Dragon m_dragon;

public:
    GamePlay(std::shared_ptr<Aspect> aspect);
    ~GamePlay();

    void BackgroundMovment(sf::Time fps);
    void ScoreCount(sf::Time fps);

    void Init() override;
    void InputProcess() override;
    void Update() override;
    void Draw() override;
};
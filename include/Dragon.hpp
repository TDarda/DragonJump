#pragma once

#include <iostream>
#include <deque>
#include <memory>

#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"

class Dragon : public sf::Drawable
{
private:
    int m_dragonRunCount = 0;
    float m_dragonJumpCount = 0;
    float m_jumpDiff = 460.0;

    sf::Clock m_dragonClock;

    sf::Sprite m_dragon;

public:
    Dragon();
    ~Dragon();

    std::deque<std::unique_ptr<sf::Texture>> m_runAnimation;
    std::deque<std::unique_ptr<sf::Texture>> m_jumpAnimation;

    sf::Texture &GetAnimation(const std::deque<std::unique_ptr<sf::Texture>> &animation, int val);
    void AddTexture(std::string path, std::deque<std::unique_ptr<sf::Texture>> &deq);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void Init();
    bool Collision(const sf::Sprite &poop);
    void DragonRun(sf::Time fps);
    void DragonJump(sf::Time fps, bool &isJumping);
};
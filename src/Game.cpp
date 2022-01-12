#include <iostream>
#include <string>

#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "MainMenu.hpp"

Game::Game() : m_aspect(std::make_shared<Aspect>())
{
    m_aspect->m_window->create(sf::VideoMode(640, 696), "DRAGON JUMP", sf::Style::Close);
    m_aspect->m_states->AddState(std::make_unique<MainMenu>(m_aspect));
}

Game::~Game()
{
}

void Game::Run()
{
    while (m_aspect->m_window->isOpen())
    {
        m_aspect->m_states->StateChange();
        m_aspect->m_states->CurrentState()->InputProcess();
        m_aspect->m_states->CurrentState()->Update();
        m_aspect->m_states->CurrentState()->Draw();
    }
}
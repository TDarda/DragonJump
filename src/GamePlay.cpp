#include <iostream>

#include <SFML/Audio.hpp>

#include "GamePlay.hpp"
#include "GameOver.hpp"

GamePlay::GamePlay(std::shared_ptr<Aspect> aspect) : m_aspect(aspect)
{
    m_backGroundClock.restart();
    m_scoreClock.restart();
    if (!music.openFromFile("assets/sound/musicGamePlay.wav"))
    {
        std::cout << "something go's wrong!" << std::endl;
    }
    music.setVolume(8);
    music.play();
    music.setLoop(true);
}

GamePlay::~GamePlay()
{
}

void GamePlay::BackgroundMovment(sf::Time fps)
{
    if (m_backGroundClock.getElapsedTime() > fps)
    {
        m_backGroundClock.restart();

        m_backGroundCount -= 1;
        m_extraBackGroundCount -= 1;
        m_poopCount -= 1;

        m_background.setPosition(m_backGroundCount, 520);
        m_extraBackground.setPosition(m_extraBackGroundCount, 520);
        m_poop.setPosition(m_poopCount, 485);

        if (m_backGroundCount < -1895)
        {
            m_backGroundCount = 1895;
        }
        if (m_extraBackGroundCount < -1895)
        {
            m_extraBackGroundCount = 1895;
        }
        if (m_poopCount < -350)
        {
            m_poopCount = 640;
        }
    }
}

void GamePlay::ScoreCount(sf::Time fps)
{
    if (m_scoreClock.getElapsedTime() > fps)
    {
        m_scoreClock.restart();
        m_score.setString("Score: " + std::to_string(++m_scoreCount));
    }
}

void GamePlay::Init()
{
    m_dragon.Init();

    m_pause.setFont(m_aspect->m_assets->GetFont(MAIN_FONT));
    m_pause.setPosition(m_aspect->m_window->getPosition().x / 2, m_aspect->m_window->getPosition().y / 2 + 200);
    m_pause.setFillColor(sf::Color::Red);
    m_pause.setScale(2, 2);
    m_pause.setString("Pauza");

    m_score.setFont(m_aspect->m_assets->GetFont(MAIN_FONT));
    m_score.setFillColor(sf::Color::Green);
    m_score.setString("Score: " + std::to_string(m_scoreCount));
    m_score.setPosition(25, 25);

    m_aspect->m_assets->AddTexture(POOP, "assets/textures/shit.png");
    m_poop.setTexture(m_aspect->m_assets->GetTexture(POOP));
    m_poop.setPosition(400, 485);
    m_poop.setScale(0.25, 0.25);

    m_aspect->m_assets->AddTexture(GAME_BACKGROUND, "assets/textures/soilGround.png");
    m_background.setTexture(m_aspect->m_assets->GetTexture(GAME_BACKGROUND));
    m_background.setPosition(0, 460);

    m_extraBackground.setTexture(m_aspect->m_assets->GetTexture(GAME_BACKGROUND));
    m_extraBackground.setPosition(1895, 520);

    m_aspect->m_assets->AddTexture(WALLPAPER, "assets/textures/moon2.jpg");
    m_wallpaper.setTexture(m_aspect->m_assets->GetTexture(WALLPAPER));
    m_wallpaper.setPosition(-350, 0);
    m_wallpaper.setScale(0.5, 0.5);

    m_aspect->m_assets->AddSound(END_GAME_SOUND, "assets/sound/gameOver.wav");
    m_endSound.setBuffer(m_aspect->m_assets->GetSound(END_GAME_SOUND));

    m_aspect->m_assets->AddSound(JUMP_SOUND, "assets/sound/jump.wav");
    m_jumpSound.setBuffer(m_aspect->m_assets->GetSound(JUMP_SOUND));
}
void GamePlay::InputProcess()
{
    sf::Event event;
    while (m_aspect->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_aspect->m_window->close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:

                m_jumpSound.play();
                m_isJumping = true;

                break;

            case sf::Keyboard::Escape:
                if (!m_isPause)
                {
                    m_isPause = true;
                }
                else
                {
                    m_isPause = false;
                }
                break;

            default:

                break;
            }
        }
    }
}

void GamePlay::Update()
{
    if (!m_isPause)
    {
        GamePlay::BackgroundMovment(sf::seconds(1.f / 1000.f));

        if (m_isJumping)
        {
            m_dragon.DragonJump(sf::seconds(1.f / 40.f), m_isJumping);
        }
        else
        {
            m_dragon.DragonRun(sf::seconds(1.f / 22.f));
        }
        if (m_dragon.Collision(m_poop))
        {
            music.stop();
            m_endSound.play();
            m_aspect->m_states->AddState(std::make_unique<GameOver>(m_aspect));
        }

        ScoreCount(sf::seconds(1.f / 6.f));
    }
}

void GamePlay::Draw()
{
    m_aspect->m_window->clear(sf::Color::Black);

    m_aspect->m_window->draw(m_wallpaper);
    m_aspect->m_window->draw(m_background);
    m_aspect->m_window->draw(m_extraBackground);
    m_aspect->m_window->draw(m_dragon);
    m_aspect->m_window->draw(m_poop);
    m_aspect->m_window->draw(m_score);

    if (m_isPause)
    {
        m_aspect->m_window->draw(m_pause);
    }

    m_aspect->m_window->display();
}
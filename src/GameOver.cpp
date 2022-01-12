#include "GameOver.hpp"
#include "GamePlay.hpp"
#include <SFML/Audio.hpp>

GameOver::GameOver(std::shared_ptr<Aspect> &aspect) : m_aspect(aspect),
                                                      m_restartSelected(true),
                                                      m_exitSelected(false),
                                                      m_startAgame(false)
{
    m_dragonClock.restart();
}

GameOver::~GameOver()
{
}

void GameOver::DragonDie(sf::Time fps)
{
    m_aspect->m_assets->AddTexture(DEAD1, "assets/dragon_textures/Dead (1).png");
    m_aspect->m_assets->AddTexture(DEAD2, "assets/dragon_textures/Dead (2).png");
    m_aspect->m_assets->AddTexture(DEAD3, "assets/dragon_textures/Dead (3).png");
    m_aspect->m_assets->AddTexture(DEAD4, "assets/dragon_textures/Dead (4).png");
    m_aspect->m_assets->AddTexture(DEAD5, "assets/dragon_textures/Dead (5).png");
    m_aspect->m_assets->AddTexture(DEAD6, "assets/dragon_textures/Dead (6).png");
    m_aspect->m_assets->AddTexture(DEAD7, "assets/dragon_textures/Dead (7).png");
    m_aspect->m_assets->AddTexture(DEAD8, "assets/dragon_textures/Dead (8).png");

    m_dragonDie.setTexture(m_aspect->m_assets->GetTexture(DEAD1));
    m_dragonDie.setScale(0.75, 0.75);
    m_dragonDie.setPosition(50, 200);

    while (m_deadCount <= DEAD8)
    {
        if (m_dragonClock.getElapsedTime() > fps)
        {
            m_dragonClock.restart();

            m_dragonDie.setTexture(m_aspect->m_assets->GetTexture(m_deadCount++));
            m_aspect->m_window->clear(sf::Color::Black);
            m_aspect->m_window->draw(m_dragonDie);
            m_aspect->m_window->display();
        }
    }
}

void GameOver::Init()
{
    DragonDie(sf::seconds(1.f / 6.f));

    m_aspect->m_assets->AddTexture(BACKGROUND, "assets/textures/menuDragon.jpg");
    m_aspect->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pushster-Regular.ttf");

    m_background.setTexture(m_aspect->m_assets->GetTexture(BACKGROUND));
    m_background.setPosition(-200, 0);

    m_header.setFont(m_aspect->m_assets->GetFont(MAIN_FONT));
    m_header.setString("GAME OVER");
    m_header.setFillColor(sf::Color::White);
    m_header.setScale(1.5, 1.5);
    m_header.setPosition(m_aspect->m_window->getSize().x / 2 - 120, m_aspect->m_window->getSize().y / 2 - 200);

    m_restart.setFont(m_aspect->m_assets->GetFont(MAIN_FONT));
    m_restart.setString("Restart");
    m_restart.setFillColor(sf::Color::Green);
    m_restart.setOrigin(m_restart.getLocalBounds().width / 2,
                        m_restart.getLocalBounds().height / 2);
    m_restart.setPosition(m_aspect->m_window->getSize().x / 2, m_aspect->m_window->getSize().y / 2 - 30);

    m_exit.setFont(m_aspect->m_assets->GetFont(MAIN_FONT));
    m_exit.setString("Exit");
    m_exit.setFillColor(sf::Color::White);
    m_exit.setOrigin(m_exit.getLocalBounds().width / 2,
                     m_exit.getLocalBounds().height / 2);
    m_exit.setPosition(m_aspect->m_window->getSize().x / 2, m_aspect->m_window->getSize().y / 2 + 30);

    m_menuPointer.setTexture(m_aspect->m_assets->GetTexture(MENU_POINTER));
    m_menuPointer.setScale(0.12, 0.12);
    m_menuPointer.setPosition(m_aspect->m_window->getSize().x / 2 - 100, m_restart.getPosition().y - 20);

    m_aspect->m_assets->AddSound(SWITCH_SOUND, "assets/sound/switch.wav");
    m_aspect->m_assets->AddSound(START_SOUND, "assets/sound/go.wav");

    m_goSound.setBuffer(m_aspect->m_assets->GetSound(START_SOUND));
    m_switchSound.setBuffer(m_aspect->m_assets->GetSound(SWITCH_SOUND));
}
void GameOver::InputProcess()
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

                m_switchSound.play();
                m_exitSelected = false;
                m_restartSelected = true;

                break;
            case sf::Keyboard::Down:

                m_switchSound.play();
                m_exitSelected = true;
                m_restartSelected = false;

                break;

            case sf::Keyboard::Enter:

                if (m_exitSelected)
                {
                    m_aspect->m_window->close();
                }

                if (m_restartSelected)
                {
                    m_goSound.play();
                    m_startAgame = true;
                }

                break;
            case sf::Keyboard::Escape:
                m_aspect->m_window->close();
                break;

            default:
                break;
            }
        }
    }
}

void GameOver::Update()
{
    if (m_exitSelected)
    {
        m_restart.setFillColor(sf::Color::White);
        m_exit.setFillColor(sf::Color::Green);
        m_menuPointer.setPosition(m_menuPointer.getPosition().x, m_exit.getPosition().y - 20);
    }
    if (m_restartSelected)
    {
        m_restart.setFillColor(sf::Color::Green);
        m_exit.setFillColor(sf::Color::White);
        m_menuPointer.setPosition(m_menuPointer.getPosition().x, m_restart.getPosition().y - 20);
    }
    if (m_startAgame)
    {
        m_aspect->m_states->AddState(std::make_unique<GamePlay>(m_aspect));
    }
}

void GameOver::Draw()
{

    m_aspect->m_window->clear();
    m_aspect->m_window->draw(m_background);
    m_aspect->m_window->draw(m_restart);
    m_aspect->m_window->draw(m_exit);
    m_aspect->m_window->draw(m_header);
    m_aspect->m_window->draw(m_menuPointer);

    m_aspect->m_window->display();
}
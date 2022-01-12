#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include <SFML/Audio.hpp>

MainMenu::MainMenu(std::shared_ptr<Aspect> &aspect) : m_aspect(aspect),
                                                      m_startSelected(true),
                                                      m_exitSelected(false),
                                                      m_startAgame(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    m_aspect->m_assets->AddTexture(BACKGROUND, "assets/textures/menuDragon.jpg");
    m_aspect->m_assets->AddTexture(MENU_POINTER, "assets//textures/menuPointer.png");

    m_aspect->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pushster-Regular.ttf");

    m_aspect->m_assets->AddSound(SWITCH_SOUND, "assets/sound/switch.wav");
    m_aspect->m_assets->AddSound(START_SOUND, "assets/sound/go.wav");

    m_goSound.setBuffer(m_aspect->m_assets->GetSound(START_SOUND));
    m_switchSound.setBuffer(m_aspect->m_assets->GetSound(SWITCH_SOUND));

    m_background.setTexture(m_aspect->m_assets->GetTexture(BACKGROUND));
    m_background.setPosition(-200, 0);

    m_start.setFont(m_aspect->m_assets->GetFont(MAIN_FONT));
    m_start.setString("Start");
    m_start.setFillColor(sf::Color::Green);
    m_start.setOrigin(m_start.getLocalBounds().width / 2,
                      m_start.getLocalBounds().height / 2);
    m_start.setPosition(m_aspect->m_window->getSize().x / 2, m_aspect->m_window->getSize().y / 2 - 30);

    m_header.setFont(m_aspect->m_assets->GetFont(MAIN_FONT));
    m_header.setString("DRAGON JUMP");
    m_header.setFillColor(sf::Color::White);
    m_header.setScale(1.5, 1.5);
    m_header.setPosition(m_aspect->m_window->getSize().x / 2 - 150, m_aspect->m_window->getSize().y / 2 - 200);

    m_menuPointer.setTexture(m_aspect->m_assets->GetTexture(MENU_POINTER));
    m_menuPointer.setScale(0.12, 0.12);
    m_menuPointer.setPosition(m_aspect->m_window->getSize().x / 2 - 100, m_start.getPosition().y - 20);

    m_exit.setFont(m_aspect->m_assets->GetFont(MAIN_FONT));
    m_exit.setString("Exit");
    m_exit.setFillColor(sf::Color::White);
    m_exit.setOrigin(m_exit.getLocalBounds().width / 2,
                     m_exit.getLocalBounds().height / 2);
    m_exit.setPosition(m_aspect->m_window->getSize().x / 2, m_aspect->m_window->getSize().y / 2 + 30);
}
void MainMenu::InputProcess()
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
                m_startSelected = true;

                break;
            case sf::Keyboard::Down:

                m_switchSound.play();
                m_exitSelected = true;
                m_startSelected = false;

                break;

            case sf::Keyboard::Enter:

                if (m_exitSelected)
                {

                    // m_switchSound.~Sound();
                    // m_goSound.~Sound();
                    // m_aspect->m_assets->GetSound(START_SOUND).~SoundBuffer();
                    // m_aspect->m_assets->GetSound(SWITCH_SOUND).~SoundBuffer();

                    m_aspect->m_window->close();
                }

                if (m_startSelected)
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

void MainMenu::Update()
{
    if (m_exitSelected)
    {
        m_start.setFillColor(sf::Color::White);
        m_exit.setFillColor(sf::Color::Green);
        m_menuPointer.setPosition(m_menuPointer.getPosition().x, m_exit.getPosition().y - 20);
    }
    if (m_startSelected)
    {
        m_start.setFillColor(sf::Color::Green);
        m_exit.setFillColor(sf::Color::White);
        m_menuPointer.setPosition(m_menuPointer.getPosition().x, m_start.getPosition().y - 20);
    }
    if (m_startAgame)
    {
        m_aspect->m_states->AddState(std::make_unique<GamePlay>(m_aspect));
    }
}

void MainMenu::Draw()
{
    m_aspect->m_window->clear();
    m_aspect->m_window->draw(m_background);
    m_aspect->m_window->draw(m_start);
    m_aspect->m_window->draw(m_exit);
    m_aspect->m_window->draw(m_header);
    m_aspect->m_window->draw(m_menuPointer);

    m_aspect->m_window->display();
}
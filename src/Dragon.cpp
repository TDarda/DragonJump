#include "Dragon.hpp"

Dragon::Dragon()
{
    m_dragonClock.restart();
}

Dragon::~Dragon()
{
}

void Dragon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_dragon);
    (void)states;
};

void Dragon::AddTexture(std::string path, std::deque<std::unique_ptr<sf::Texture>> &deq)
{
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(path))
    {
        deq.emplace_back(std::move(texture));
    }
    else
    {
        std::cout << "something goes wrong!\n";
    }
}

sf::Texture &Dragon::GetAnimation(const std::deque<std::unique_ptr<sf::Texture>> &animation, int val)
{
    return *(animation.at(val).get());
}

void Dragon::Init()
{
    m_dragonClock.restart(); // sprawdz to
    AddTexture("assets/dragon_textures/Run (1).png", m_runAnimation);
    AddTexture("assets/dragon_textures/Run (2).png", m_runAnimation);
    AddTexture("assets/dragon_textures/Run (3).png", m_runAnimation);
    AddTexture("assets/dragon_textures/Run (4).png", m_runAnimation);
    AddTexture("assets/dragon_textures/Run (5).png", m_runAnimation);
    AddTexture("assets/dragon_textures/Run (6).png", m_runAnimation);
    AddTexture("assets/dragon_textures/Run (7).png", m_runAnimation);
    AddTexture("assets/dragon_textures/Run (8).png", m_runAnimation);

    AddTexture("assets/dragon_textures/Jump (1).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (1).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (2).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (2).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (3).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (3).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (4).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (4).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (5).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (5).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (6).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (6).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (7).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (7).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (8).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (8).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (9).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (9).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (10).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (10).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (11).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (11).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (12).png", m_jumpAnimation);
    AddTexture("assets/dragon_textures/Jump (12).png", m_jumpAnimation);

    m_dragon.setTexture(GetAnimation(m_runAnimation, 1));
    m_dragon.setScale(0.25, 0.25);
    m_dragon.setPosition(100, 520);
}

void Dragon::DragonRun(sf::Time fps)
{
    if (m_dragonClock.getElapsedTime() > fps)
    {

        m_dragonClock.restart();
        m_dragon.setPosition(100, 460);
        m_dragon.setTexture(GetAnimation(m_runAnimation, m_dragonRunCount++));

        if (m_dragonRunCount > 7)
        {
            m_dragonRunCount = 0;
        }
    }
}

void Dragon::DragonJump(sf::Time fps, bool &isJumping)
{
    if (m_dragonClock.getElapsedTime() > fps)
    {
        m_dragonClock.restart();

        m_dragon.setPosition(100, m_jumpDiff);
        m_dragon.setTexture(GetAnimation(m_jumpAnimation, m_dragonJumpCount));

        if (m_dragonJumpCount >= 12)
        {
            m_jumpDiff += 15;
        }
        else
        {
            m_jumpDiff -= 15;
        }

        ++m_dragonJumpCount;
        if (m_dragonJumpCount > 23)
        {
            isJumping = false;
            m_dragonJumpCount = 0;
        }
    }
}

bool Dragon::Collision(const sf::Sprite &poop)
{
    float dragonBack = m_dragon.getPosition().x + 30;
    float dragonFront = m_dragon.getPosition().x + 40;
    float dragonBottom = m_dragon.getPosition().y + m_dragon.getGlobalBounds().height - 20;

    if ((dragonBottom > poop.getPosition().y) &&
        (dragonFront > poop.getPosition().x - 30) &&
        dragonBack < poop.getPosition().x + poop.getGlobalBounds().width)
    {
        return true;
    }

    return false;
}
#include "MainMenu.h"

MainMenu::MainMenu()
{
    //if (!m_backgroundTexture.loadFromFile("Resources/MainMenuBackgroundTexture.png"))
    //{

    //}
    m_backgroundSprite.setTexture(ResourceHolder::getTexture("MainMenuBackgroundTexture.png"));

    if (!m_font.loadFromFile("Resources/arial.ttf"))
    {

    }

    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color(27, 241, 231));

    text.move(100, 230);

    for (auto& item : { "Play", "Settings", "About", "Exit"})
    {
        text.setString(item);
        m_items.push_back(sf::Text(text));
        text.move(0, 60);
    } 
    
    selectItem(0);
}

void MainMenu::selectItem(int itemIdx)
{   
    // Set color for a new selected menu item
    m_items.at(itemIdx).setFillColor(sf::Color::White);

    if (itemIdx != m_selectedItemIdx)
    {
        m_items[m_selectedItemIdx].setFillColor(sf::Color(27, 241, 231));
        m_selectedItemIdx = itemIdx;
    }
}

void MainMenu::moveUp()
{
    if (m_selectedItemIdx > 0)
    {
        selectItem(m_selectedItemIdx - 1);
    }
}

void MainMenu::moveDown()
{
    if (m_selectedItemIdx < m_items.size()-1)
    {
        selectItem(m_selectedItemIdx + 1);
    }
}

void MainMenu::show()
{
    state = State::Shown;
}

void MainMenu::hide()
{
    state = State::Hidden;
}

void MainMenu::toggle()
{
    state = (state == State::Hidden) ? State::Shown : State::Hidden;
}

MainMenu::State MainMenu::getState()
{
    return state;
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (state == State::Hidden)
        return;

    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    //states.texture = &m_tileset;

    // draw the objects
    target.draw(m_backgroundSprite, states);

    for (auto& item : m_items)
    {
        target.draw(item);
    }
}

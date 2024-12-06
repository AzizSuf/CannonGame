#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include <vector>


class MainMenu : public sf::Drawable, public sf::Transformable
{
public:
    enum class State
    {
        Hidden,
        Shown
    };

public:
    MainMenu();
    
    void selectItem(int itemIdx);
    void moveUp();
    void moveDown();

    void show();
    void hide();
    void toggle();

    // Accessors 
    State getState();


private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;



private:
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;

    sf::Font m_font;

    std::vector<sf::Text> m_items;
    int m_selectedItemIdx = 0;


    State state = State::Hidden;

};

